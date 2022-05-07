#include "ch.h"
#include "hal.h"
#include <usbcfg.h>

#include "camera/dcmi_camera.h"
#include <camera/po8030.h>
#include <flag_detection.h>

#include <chprintf.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>


//constant for the function get_color
#define RED_THRESHOLD   0
#define GREEN_THRESHOLD 0
#define BLUE_THRESHOLD  0

//constant for the function extract_color_bands
#define MIN_GROUP_SIZE 20
#define MIN_COLOR_BAND_WIDTH 100

void init_camera(void)
{
	dcmi_start();
	po8030_start();
	
	//Takes pixels 0 to IMAGE_BUFFER_SIZE of the line 10 + 11 (minimum 2 lines because reasons)
	po8030_advanced_config(FORMAT_RGB565, 0, 11, IMAGE_BUFFER_SIZE, 2, SUBSAMPLING_X1, SUBSAMPLING_X1);
	dcmi_enable_double_buffering();
	dcmi_set_capture_mode(CAPTURE_ONE_SHOT);
	dcmi_prepare();
}

void capture_image(uint8_t* img_buff_ptr)
{
	dcmi_capture_start();
	wait_image_ready();    
	img_buff_ptr = dcmi_get_last_image_ptr();
}

Color get_color(uint16_t pixel)
{
	uint8_t red   = (pixel & 0xF800) >> 11;
	uint8_t green = (pixel & 0x07E0) >> 5;
	uint8_t blue  = (pixel & 0x001F) >> 0;

	Color color = UNDEFINED_COLOR;
	char* color_name = "Undefined";

	if ( (red > RED_THRESHOLD) & (blue > BLUE_THRESHOLD) & (green > GREEN_THRESHOLD) )
	{
		color = WHITE;
		// chprintf((BaseSequentialStream *)&SD3, "Color: White\n");
	}
	else if ( (red > RED_THRESHOLD) & (blue <= BLUE_THRESHOLD) & (green <= GREEN_THRESHOLD) )
	{
		color = RED;
		// chprintf((BaseSequentialStream *)&SD3, "Color: Red\n");
	}
	else if ( (red <= RED_THRESHOLD) & (blue > BLUE_THRESHOLD) & (green <= GREEN_THRESHOLD) )
	{
		color = BLUE;
		// chprintf((BaseSequentialStream *)&SD3, "Color: Blue\n");
	}
	else if ( (red <= RED_THRESHOLD) & (blue <= BLUE_THRESHOLD) & (green > GREEN_THRESHOLD) )
	{
		color = GREEN;
		// chprintf((BaseSequentialStream *)&SD3, "Color: Green\n");
	}
	else
	{
		chprintf((BaseSequentialStream *)&SD3, "Color: Undefined\n");
	}

	return color;
}

void extract_color_bands(Color* color_bands, uint8_t color_line [MAX_NUM_COLOR_BANDS])
{
	//note: ajouter (uint16_t) devant colors_bands quand on l utilise comme dans page 2 corrige tp4 <- ça marche pas...

	//step 1: split the color_line into 2 vectors that give the groups of colors and the size of each group
	Color color_groups [IMAGE_BUFFER_SIZE] = {UNDEFINED_COLOR};
	uint16_t size_of_groups [IMAGE_BUFFER_SIZE] = {0};

	uint16_t ptr_color_groups = 0;
	Color current_color = color_line[0];
	uint16_t current_group_size = 1;

	for (uint16_t i = 1; i < IMAGE_BUFFER_SIZE; i++)
	{
		if ( color_line[i] != current_color )
		{
			color_groups[ptr_color_groups] = current_color;
			size_of_groups[ptr_color_groups] = current_group_size;
			ptr_color_groups++;
			current_color = color_line[i];
			current_group_size = 1;
		}
		else
		{
			current_group_size++;
		}

		//we want to update the last group anyway
		if (i == IMAGE_BUFFER_SIZE-1)
		{
			color_groups[ptr_color_groups] = current_color;
			size_of_groups[ptr_color_groups] = current_group_size;
			ptr_color_groups++;
		}

	}

	//step 2: clean the 2 vectors by moving the big groups to the beginning of the vectors and erasing the small groups
	uint16_t number_of_groups = ptr_color_groups;
	ptr_color_groups = 0;

	for (uint16_t i = 0; i < number_of_groups; i++)
	{
		if (size_of_groups[i] >= MIN_GROUP_SIZE)
		{
			color_groups[ptr_color_groups] = color_groups[i];
			size_of_groups[ptr_color_groups] = size_of_groups[i];
			ptr_color_groups++;
		}
	}

	//step 3: fusion the groups of the same consecutive color together
	number_of_groups = ptr_color_groups;
	ptr_color_groups = 0;
	current_color = color_groups[0];
	current_group_size = size_of_groups [0];

	for (uint16_t i = 1; i < number_of_groups; i++)
	{
		if ( color_groups[i] != current_color )
		{
			color_groups[ptr_color_groups] = current_color;
			size_of_groups [ptr_color_groups] = current_group_size;
			ptr_color_groups++;
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
			color_groups[ptr_color_groups] = current_color;
			size_of_groups [ptr_color_groups] = current_group_size;
			ptr_color_groups++;
		}
	}

	//step 4: replace the fusion groups that are smaller than MIN_COLOR_BAND_WIDTH (and thus cannot be consider as a band for the flag) by UNDEFINED_COLOR
	number_of_groups = ptr_color_groups;

	for (uint16_t i = 0; i < number_of_groups; i++)
	{
		if ( size_of_groups[i] < MIN_COLOR_BAND_WIDTH)
		{
			color_groups[i] = UNDEFINED_COLOR;
		}
	}

	//step 5: fusion the consecutive UNDEFINED_COLOR and return the color_bands
	ptr_color_groups = 0;
	current_color = color_groups[0];

	for (uint16_t i = 1; i < number_of_groups; i++)
	{
		if ( color_groups[i] != current_color )
		{
			color_bands[ptr_color_groups] = current_color;
			ptr_color_groups++;
			current_color = color_groups[i];
		}

		//we want to update the last group anyway
		if ( i == number_of_groups-1 )
		{
			color_bands[ptr_color_groups] = current_color;
		}
	}
}

Flag extract_flag (Color color_bands [MAX_NUM_COLOR_BANDS])
{
	//check if flag=France
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

	//check if flag=Italy
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

	return UNDEFINED_FLAG;
}

Flag get_flag(void)
{
    // Capture a line and store it into img_buff_ptr
    uint8_t *img_buff_ptr;
    capture_image(img_buff_ptr);

    // Convert img_buff_ptr into a 640x16 bit array
    uint16_t pixel_line [IMAGE_BUFFER_SIZE] = {0};
    for (uint16_t i = 0; i < IMAGE_BUFFER_SIZE; i++)
    {
        pixel_line [i] |= img_buff_ptr [2*i] << 8;
        pixel_line [i] |= img_buff_ptr [2*i+1];
    }
    
	// Detect the colors of the pixel line
	Color color_line [IMAGE_BUFFER_SIZE] = {UNDEFINED_COLOR};
	// for (uint16_t i; i < IMAGE_BUFFER_SIZE; i++)
	// {
	// 	color_line [i] = get_color(pixel_line [i]);
	// }
	color_line [300] = get_color(pixel_line [300]);
	
	// Extract general band of colours from color_line
	Color color_bands [MAX_NUM_COLOR_BANDS] = {UNDEFINED_COLOR};
	extract_color_bands (color_bands, color_line);
	
	return extract_flag (color_bands) ;
}
