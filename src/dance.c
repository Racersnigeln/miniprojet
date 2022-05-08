#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include <usbcfg.h>

#include <time.h>

#include <main.h>
#include <motors.h>
#include <audio/audio_thread.h>
#include <flag_detection.h>
#include <state.h>
#include <audio/play_melody.h>
#include <music.h>

#include <dance.h>

#define NUMBER_OF_SONG 1

// Speed of movement in cm/s when dancing
#define DANCE_SPEED 4
#define SPEED_TO_STEPS 1000/13


static uint16_t music_position = 0;
static Music current_song;
static bool is_dancing = false;


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

void stop_motors(void)
{
    left_motor_set_speed(0);
    right_motor_set_speed(0);
}

void stop_dancing(void)
{
    is_dancing = false;
    music_position = 0;
    stop_motors();
    // Stop playing sound
    dac_stop();
    
}

void change_figure(void)
{
    uint8_t r = rand() % 4;
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

Music LUT_flag_to_music (Flag country) 
{
    if (country == UNDEFINED_FLAG)
    {
        return NO_MUSIC();
    }
    else if (country == FRANCE)
    {
        return MARSEILLAISE();
    }
    else if (country == ITALY)
    {
        return BELLA_CIAO();
    }
}

void restart_dance(Flag country)
{
    music_position = 0;
    current_song = LUT_flag_to_music(country); 
    is_dancing = true;
}

static THD_WORKING_AREA(waDance, 2048);
static THD_FUNCTION(Dance, arg)
{
    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    systime_t time;

    // Small offset time to separate notes
    systime_t note_offset = 20 ;    

    while(1)
    {
        if ( (is_dancing) & (get_robot_state() == WAIT) )
        {
            time = chVTGetSystemTime();

            if (current_song.notes[music_position] != 0)
            {
                // Play next tone and do new dance step
                dac_play(current_song.notes[music_position]);
                change_figure();
            } 
            else 
            {
                // Stop singing and dancing
                dac_stop();
                stop_motors();
            }

            if (current_song.rythm[music_position] > note_offset)
            {
                chThdSleepUntilWindowed(time, 
                    time + current_song.rythm[music_position] - note_offset);
                dac_stop();
                chThdSleep(note_offset);
            }

            music_position++;

            if (music_position >= MUSIC_SIZE)
            {
                stop_dancing();
            }
        } 
        else 
        {
            chThdSleep(100);
        }
    }
}

void start_dance(void)
{
	chThdCreateStatic(waDance, sizeof(waDance), NORMALPRIO, Dance, NULL);
}
