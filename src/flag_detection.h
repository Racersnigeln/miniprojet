#ifndef FLAG_DETECTION_H
#define FLAG_DETECTION_H

// Not all functions are declared here, 
// only the ones that should be usable elsewhere

// Defined here and not in .c because needed in the declarations
#define MAX_NUM_COLOR_BANDS 8

// Defined here because needed in other files
typedef enum {UNDEFINED_FLAG, FRANCE, ITALY, JAPAN, SWITZERLAND} Flag;
typedef enum {UNDEFINED_COLOR, WHITE, RED, GREEN, BLUE} Color;

void init_camera(void);

Flag get_flag(void);

#endif /* FLAG_DETECTION_H */
