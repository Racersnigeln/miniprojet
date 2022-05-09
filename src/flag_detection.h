#ifndef FLAG_DETECTION_H
#define FLAG_DETECTION_H

#define MAX_NUM_COLOR_BANDS 10
#define IMAGE_BUFFER_SIZE 640

typedef enum {UNDEFINED_FLAG, FRANCE, ITALY, JAPAN} Flag;
typedef enum {UNDEFINED_COLOR, WHITE, RED, GREEN, BLUE} Color;

void init_camera(void);

void capture_image(uint8_t* img_buff_ptr);

Color get_color(uint16_t pixel);

void extract_color_bands(Color* color_bands, uint8_t color_line [MAX_NUM_COLOR_BANDS]);  
//note: ajouter (uint_16t) devant colors_bands quand on l utilise comme dans page 2 corrige tp4

Flag extract_flag (Color color_bands [MAX_NUM_COLOR_BANDS]);

Flag get_flag(void);    //return UNDIFINED if doesnt find any flag


#endif /* FLAG_DETECTION_H */
