#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include <usbcfg.h>

#include <main.h>
#include <motors.h>
#include <process_image.h>
#include <state.h>
#include <audio/play_melody.h>
#include <music.h>

#include <dance.h>


#define NUMBER_OF_SONG 1

// Speed of movement in cm/s when dancing
#define DANCE_SPEED 4
#define SPEED_TO_STEPS 1000/13


static uint16_t music_position = 0;
static Music current_song ;
static bool is_dancing = false ;


void advance(void)
{
    left_motor_set_speed(DANCE_SPEED*SPEED_TO_STEPS);
    right_motor_set_speed(DANCE_SPEED*SPEED_TO_STEPS);
}

void reverse(void)
{
    left_motor_set_speed(-DANCE_SPEED*SPEED_TO_STEPS);
    right_motor_set_speed(-DANCE_SPEED*SPEED_TO_STEPS);
}

void rotate_left(void)
{
    left_motor_set_speed(-DANCE_SPEED*SPEED_TO_STEPS);
    right_motor_set_speed(DANCE_SPEED*SPEED_TO_STEPS);
}

void rotate_right(void)
{
    left_motor_set_speed(DANCE_SPEED*SPEED_TO_STEPS);
    right_motor_set_speed(-DANCE_SPEED*SPEED_TO_STEPS);
}

void stop(void)
{
    left_motor_set_speed(0);
    right_motor_set_speed(0);
}

void change_figure(void)
{
    int r = rand() % 4;
    if (r == 0)
    {
        advance();
    }
    else if (r == 1)
    {
        reverse();
    }
    else if (r == 2)
    {
        rotate_left();
    }
    else if (r == 3)
    {
        rotate_right();
    }
}


void restart_dance(Flag country)
{
    music_position = 0;
    //current_song = LUT_flag_to_music (country); 
    current_song = TEST();
    is_dancing = TRUE;
}

static THD_WORKING_AREA(waDance, 2048);  //increase priority
static THD_FUNCTION(Dance, arg)
{
    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    systime_t time;

    //////
    current_song = TEST();
    //////

    while(1)
    {
        //if ( (is_dancing) & (get_robot_state() != PAUSE) )
        if (1)
        {
            chprintf((BaseSequentialStream *)&SD3, "DANSE");
            time = chVTGetSystemTime();
//            playNote (current_song.notes[music_position], current_song.rythm[music_position]);
//            change_figure();

            chThdSleepUntilWindowed(time, time + current_song.rythm[music_position]);
            ++music_position;

            if (music_position >= MUSIC_SIZE)
            {
                is_dancing = false;
                music_position = 0;
                // allumer des LEDS pour montrer qu on a fini ? coder une fonction finish_dance ?
            }
            // L ERREUR VIENT DE LA, A COMMENTER PUIS DEBUGGUER

        } 
        else 
        {
            chThdSleep(100);     //(ms) a changer ?
        }
    }
}

void start_dance(void)
{
	chThdCreateStatic(waDance, sizeof(waDance), NORMALPRIO + 1, Dance, NULL); //increase priority
}
