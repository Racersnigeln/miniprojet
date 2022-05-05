#ifndef DANCE_H
#define DANCE_H

// Get access to the type Flag
#include <flag_detection.h>
#include <music.h>

Music LUT_flag_to_music (Flag country);

void restart_dance(Flag country); // music_position=0, current_song <- country, is_dancing = true

void change_figure(void);

void start_dance(void);


#endif /*   DANCE_H */
