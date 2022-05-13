#include <ch.h>
#include <hal.h>

#include <camera/po8030.h>		// For taking photos
#include <camera/dcmi_camera.h> // For taking photos
#include <flag_detection.h>

#define IMAGE_BUFFER_SIZE 640

// Constants for the function get_color
// See figure 7 from TP4
#define RED_MASK			0xF800
#define GREEN_MASK			0x07E0
#define BLUE_MASK			0x001F
#define RED_BIT_OFFSET		11
#define GREEN_BIT_OFFSET	5
#define BLUE_BIT_OFFSET		0

// Red and blue are stored on 5 bits, green is stored on 6 bits
// therefore we want the results to be stored on a scale from 0 to 255
#define RED_CORRECTION	 	8
#define GREEN_CORRECTION 	4
#define BLUE_CORRECTION 	8

#define WHITE_THRESHOLD   	80
#define RED_MARGIN			15
#define GREEN_MARGIN		20
#define BLUE_MARGIN			20

// Constants for the function extract_color_bands
#define MIN_GROUP_SIZE 		 15
#define MIN_COLOR_BAND_WIDTH 80

void init_camera(void)
{
	dcmi_start();
	po8030_start();

	//Takes pixels 0 to IMAGE_BUFFER_SIZE-1 of the line 150 + 151 (minimum 2 lines because reasons)
	po8030_advanced_config(FORMAT_RGB565, 0, 150, IMAGE_BUFFER_SIZE, 2, SUBSAMPLING_X1, SUBSAMPLING_X1);
	dcmi_enable_double_buffering();
	dcmi_set_capture_mode(CAPTURE_ONE_SHOT);
	dcmi_prepare();
}

Color get_color(uint16_t pixel)
{
	// Isolate and set all colors to the scale 0-255
	uint8_t red   = ((pixel & RED_MASK)   >> RED_BIT_OFFSET)   * RED_CORRECTION;
	uint8_t green = ((pixel & GREEN_MASK) >> GREEN_BIT_OFFSET) * GREEN_CORRECTION;
	uint8_t blue  = ((pixel & BLUE_MASK)  >> BLUE_BIT_OFFSET)  * BLUE_CORRECTION;

	Color color = UNDEFINED_COLOR;

	// Identify color of pixel
	if ( (red > blue + RED_MARGIN) & (red > green + RED_MARGIN) )
	{
		color = RED;
	}
	else if ( (blue > red + BLUE_MARGIN) & (blue > green + BLUE_MARGIN) )
	{
		color = BLUE;
	}
	else if ( (green > red + GREEN_MARGIN) & (green > blue + GREEN_MARGIN) )
	{
		color = GREEN;
	}
	else if ( (red > WHITE_THRESHOLD) & (blue > WHITE_THRESHOLD) & (green > WHITE_THRESHOLD) )
	{
		color = WHITE;
	}

	return color;
}

void extract_color_bands(Color* color_bands, uint8_t color_line [MAX_NUM_COLOR_BANDS])
{

	// Step 1: 
	// Split the color_line into 2 vectors that give the groups 
	// of colors and the size of each group
	Color color_groups [IMAGE_BUFFER_SIZE] = {UNDEFINED_COLOR};
	uint16_t size_of_groups [IMAGE_BUFFER_SIZE] = {0};

	uint16_t color_group_index = 0;
	Color current_color = color_line[0];
	uint16_t current_group_size = 1;

	for (uint16_t i = 1; i < IMAGE_BUFFER_SIZE; i++)
	{
		if ( color_line[i] != current_color )
		{
			color_groups[color_group_index] = current_color;
			size_of_groups[color_group_index] = current_group_size;
			color_group_index++;
			current_color = color_line[i];
			current_group_size = 1;
		}
		else
		{
			current_group_size++;
		}

		// We want to update the last group anyway
		if (i == IMAGE_BUFFER_SIZE-1)
		{
			color_groups[color_group_index] = current_color;
			size_of_groups[color_group_index] = current_group_size;
			color_group_index++;
		}

	}

	// Step 2: 
	// Clean the 2 vectors by moving the big groups to the 
	// beginning of the vectors and erasing the small groups
	uint16_t number_of_groups = color_group_index;
	color_group_index = 0;

	for (uint16_t i = 0; i < number_of_groups; i++)
	{
		if (size_of_groups[i] >= MIN_GROUP_SIZE)
		{
			color_groups[color_group_index] = color_groups[i];
			size_of_groups[color_group_index] = size_of_groups[i];
			color_group_index++;
		}
	}

	// Step 3: 
	// Fusion the groups of the same consecutive color together
	number_of_groups = color_group_index;
	color_group_index = 0;
	current_color = color_groups[0];
	current_group_size = size_of_groups [0];

	for (uint16_t i = 1; i < number_of_groups; i++)
	{
		if ( color_groups[i] != current_color )
		{
			color_groups[color_group_index] = current_color;
			size_of_groups [color_group_index] = current_group_size;
			color_group_index++;
			current_color = color_groups[i];
			current_group_size = size_of_groups [i];
		}
		else
		{
			current_group_size += size_of_groups [i];
		}

		//we want to update the last group anyway
		if ( i == number_of_groups-1 )
		{
			color_groups[color_group_index] = current_color;
			size_of_groups [color_group_index] = current_group_size;
			color_group_index++;
		}
	}

	// Step 4: 
	// Replace the fusion groups that are smaller than MIN_COLOR_BAND_WIDTH 
	// (and thus cannot be consider as a band for the flag) by UNDEFINED_COLOR
	number_of_groups = color_group_index;

	for (uint16_t i = 0; i < number_of_groups; i++)
	{
		if ( size_of_groups[i] < MIN_COLOR_BAND_WIDTH)
		{
			color_groups[i] = UNDEFINED_COLOR;
		}
	}

	//step 5: 
	// Fusion the consecutive UNDEFINED_COLOR and return the color_bands
	color_group_index = 0;
	current_color = color_groups[0];

	for (uint16_t i = 1; i < number_of_groups; i++)
	{
		if ( color_groups[i] != current_color )
		{
			color_bands[color_group_index] = current_color;
			color_group_index++;
			current_color = color_groups[i];
		}

		// We want to update the last group anyway
		if ( i == number_of_groups-1 )
		{
			color_bands[color_group_index] = current_color;
		}
	}
}

Flag extract_flag (Color color_bands [MAX_NUM_COLOR_BANDS])
{
	// Check if flag = France
	for (uint8_t i = 0; i < MAX_NUM_COLOR_BANDS-2; i++)
	{
		if (color_bands[i] == BLUE)
		{
			if (color_bands[i+1] == WHITE)
			{
				if (color_bands[i+2] == RED)
				{
					return FRANCE;
				}
			}
		}
	}

	// Check if flag = Italy
	for (uint8_t i = 0; i < MAX_NUM_COLOR_BANDS-2; i++)
	{
		if (color_bands[i] == GREEN)
		{
			if (color_bands[i+1] == WHITE)
			{
				if (color_bands[i+2] == RED)
				{
					return ITALY;
				}
			}
		}
	}
	
	// Check if flag = Japan
	for (uint8_t i = 0; i < MAX_NUM_COLOR_BANDS-2; i++)
	{
		if (color_bands[i] == WHITE)
		{
			if (color_bands[i+1] == RED)
			{
				if (color_bands[i+2] == WHITE)
				{
					return JAPAN;
				}
			}
		}
	}

	// Check if flag = Switzerland
	for (uint8_t i = 0; i < MAX_NUM_COLOR_BANDS-2; i++)
	{
		if (color_bands[i] == RED)
		{
			if (color_bands[i+1] == WHITE)
			{
				if (color_bands[i+2] == RED)
				{
					return SWITZERLAND;
				}
			}
		}
	}

	return UNDEFINED_FLAG;
}

Flag get_flag(void)
{
    // Capture a line of an image and store it into img_buff_ptr
	dcmi_capture_start();
	wait_image_ready();    
	uint8_t* img_buff_ptr = dcmi_get_last_image_ptr();

    // Store the image line in a 640x16 bit array
    uint16_t pixel_line [IMAGE_BUFFER_SIZE] = {0};
    for (uint16_t i = 0; i < IMAGE_BUFFER_SIZE; i++)
    {
        pixel_line [i] |= img_buff_ptr [2*i] << 8;
        pixel_line [i] |= img_buff_ptr [2*i+1];
    }
    
	// Detect the colors of the pixel line
	Color color_line [IMAGE_BUFFER_SIZE] = {UNDEFINED_COLOR};
	for (uint16_t i = 0; i < IMAGE_BUFFER_SIZE; i++)
	{
		color_line [i] = get_color(pixel_line [i]);
	}
	
	// Extract general bands of colors from color_line
	Color color_bands [MAX_NUM_COLOR_BANDS] = {UNDEFINED_COLOR};
	extract_color_bands (color_bands, color_line);
	
	return extract_flag (color_bands);
}
