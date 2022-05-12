#ifndef STATE_H
#define STATE_H

typedef enum {WAIT, PAUSE, FLAG_DETECTION, DANCE} State; 

State get_robot_state(void);

void start_state (void);


#endif /* STATE_H */