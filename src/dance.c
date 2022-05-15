#include <ch.h>
#include <hal.h>

#include <stdlib.h>				// For pseudo-random numbers
#include <motors.h>             // For moving robot while dancing
#include <audio/audio_thread.h> // For playing sound
#include <flag_detection.h>     // For Flag type
#include <state.h>              // To get access to current state
#include <music.h>              // To know what to play
#include <dance.h>              


// Speed of movement in cm/s when dancing
#define CM_PER_S        4
#define SPEED_TO_STEPS  1000/13
#define DANCE_SPEED     CM_PER_S*SPEED_TO_STEPS

// Variables for the thread Dance
static uint8_t music_position = 0;
static Music current_song;
static bool is_dancing = false;

void advance(void)
{
    left_motor_set_speed(DANCE_SPEED);
    right_motor_set_speed(DANCE_SPEED);
}

void reverse(void)
{
    left_motor_set_speed(-DANCE_SPEED);
    right_motor_set_speed(-DANCE_SPEED);
}

void rotate_left(void)
{
    left_motor_set_speed(-DANCE_SPEED);
    right_motor_set_speed(DANCE_SPEED);
}

void rotate_right(void)
{
    left_motor_set_speed(DANCE_SPEED);
    right_motor_set_speed(-DANCE_SPEED);
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
    // Change to a pseudo-random dance figure
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

void restart_dance(Flag country)
{
    music_position = 0;
    current_song = LUT_flag_to_music(country); 
    is_dancing = true;
}

static THD_WORKING_AREA(waDance, 256);
static THD_FUNCTION(Dance, arg)
{
    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    systime_t time;

    // Small offset time to detach notes
    const systime_t note_offset = 20;    

    while(1)
    {
    	// The robot turns back into the WAIT state right after the dance has started
    	// and we don't want him to dance when he's in FLAG_DETECTION or PAUSE state
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
                // 2 purposes: 
                // 1) We want to not dance and not play notes when 
                //    there is a silence in the music
                // 2) If the size of the song is less than 55, 
                //    we want to stop playing and dancing before the 55th note.

                // Stop playing and dancing
                dac_stop();
                stop_motors();
            }

            // Stop playing a little before the end of the note value (to detach notes)
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
    init_songs();
    motors_init();
    dac_start();
	chThdCreateStatic(waDance, sizeof(waDance), NORMALPRIO, Dance, NULL);
}
