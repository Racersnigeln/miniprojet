#ifndef DANCE_H
#define DANCE_H

#include <flag_detection.h> // For Flag type
#include <music.h>          // For Music type

Music LUT_flag_to_music (Flag country);

void restart_dance(Flag country);

void change_figure(void);

void start_dance(void);

void stop_dancing(void);


#endif /* DANCE_H */
