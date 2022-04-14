#include <main.h>
#include <motors.h>
#include <process_image.h>
#include <audio/play_melody.h>


#define MUSIC_SIZE 50
#define NUMBER_OF_SONG 1

struct Music {
  uint16_t rythme [MUSIC_SIZE] ;
  uint16_t note [MUSIC_SIZE] ;
}; 

static uint16_t music_position = 0;
static Music current_song;
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


static THD_WORKING_AREA(waDance, 256);  //increase priority
static THD_FUNCTION(Dance, arg)
{
    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    systime_t time;

    while(1)
    {
        //ajouter detection obstacle -> finish dance
        if (is_dancing)
        {
            time = chVTGetSystemTime();
            Play_Note (current_song.note[music_position], current_song.rythme[music_position]);
            change_figure();
        
            chThdSleepUntilWindowed(time , time + current_song.rythme[music_position]);
            ++music_position;

            if (music_position >= MUSIC_SIZE)
            {
                is_dancing = false;
                music_position = 0;
                // allumer des LEDS pour montrer qu on a fini ? coder une fonction finish_dance ?
            }

        } else {
            chThdSleep(100);     //(ms) a changer ?
        }
    }
}

void start_dance(void)
{
	chThdCreateStatic(waDance, sizeof(waDance), NORMALPRIO + 1, Dance, NULL); //increase priority
}