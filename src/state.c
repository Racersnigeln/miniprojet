#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include <usbcfg.h>

#include <main.h>
#include <dance.h>
#include <flag_detection.h>
#include <obstacle.h>
#include <button.h>
#include <selector.h>
#include <leds.h>

#include <state.h>

static State ROBOT_STATE = WAIT; 

static THD_WORKING_AREA(waManageStates, 4096);
static THD_FUNCTION(ManageStates, arg)
{
    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    // Type Flag defined in process_image.h
	static Flag country = UNDEFINED_FLAG;
    int selector = get_selector();

    while(1)
    {
        if ( obstacle_detected() )
        {
            ROBOT_STATE = PAUSE;
        }
        else
        {
            ROBOT_STATE = WAIT;
            if ( get_selector() != selector )
            {
                stop_dancing();
                selector = get_selector();
                ROBOT_STATE = FLAG_DETECTION;
            }
            if ( ROBOT_STATE == FLAG_DETECTION )
            {
                set_body_led(1);
                systime_t start_time = chVTGetSystemTime();
                while ( (chVTGetSystemTime() < start_time + 10000) 
                        & (country == UNDEFINED_FLAG) )
                {
                    country = get_flag();
                }
                ROBOT_STATE = (country == UNDEFINED_FLAG) ? WAIT : DANCE;
                set_body_led(0);
            }
            if ( ROBOT_STATE == DANCE )
            {
                restart_dance(JAPAN);
                country = UNDEFINED_FLAG;
            }
        }
        chThdSleep(100);
    }
}

void start_state (void)
{
    chThdCreateStatic(waManageStates, sizeof(waManageStates), NORMALPRIO+1, ManageStates, NULL);
}

State get_robot_state () 
{
    return ROBOT_STATE;
}
