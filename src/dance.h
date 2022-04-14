#ifndef DANCE_H
#define DANCE_H

// Speed of movement in cm/s when dancing
#define DANCE_SPEED 4
#define SPEED_TO_STEPS 1000/13


void restart_dance (FLag country); // music_position=0, current_song <- country, is_dancing = true

void change_figure(void);



#endif /*   DANCE_H */
