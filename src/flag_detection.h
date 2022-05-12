#ifndef FLAG_DETECTION_H
#define FLAG_DETECTION_H

// Defined here and not in .c because needed in the declarations
#define MAX_NUM_COLOR_BANDS 10

// Defined here because needed in other files
typedef enum {UNDEFINED_FLAG, FRANCE, ITALY, JAPAN, SWITZERLAND} Flag;
typedef enum {UNDEFINED_COLOR, WHITE, RED, GREEN, BLUE} Color;

void init_camera(void);

Color get_color(uint16_t pixel);

void extract_color_bands(Color* color_bands, uint8_t color_line [MAX_NUM_COLOR_BANDS]);  

Flag extract_flag (Color color_bands [MAX_NUM_COLOR_BANDS]);

Flag get_flag(void);

#endif /* FLAG_DETECTION_H */
