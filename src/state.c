#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include <usbcfg.h>

#include <main.h>
#include <dance.h>
#include <process_image.h>
#include <obstacle.h>
#include <button.h>
#include <selector.h>
#include <leds.h>

#include <state.h>

static State ROBOT_STATE = WAIT; 

static THD_WORKING_AREA(waManageStates, 256);
static THD_FUNCTION(ManageStates, arg)
{
    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    //ROBOT_STATE = WAIT;

	static Flag country = UNDEFINED;    //type Flag defined in process_image.h

    int selector = get_selector();

    while(1)
    {
        // chprintf((BaseSequentialStream *)&SD3, "ManageState\n");
        if ( obstacle_detected() )
        {
            ROBOT_STATE = PAUSE;
        }
        else
        {
            ROBOT_STATE = WAIT;
            if ( get_selector() != selector )
            {
                selector = get_selector();
                ROBOT_STATE = FLAG_DETECTION;
                change_figure();
            }
            if ( ROBOT_STATE == FLAG_DETECTION )
            {
                country = get_flag();
                ROBOT_STATE = (country == UNDEFINED) ? WAIT : DANCE;
            }
            if ( ROBOT_STATE == DANCE )
            {
                restart_dance(country);
                ROBOT_STATE = WAIT;
            }
        }
        chThdSleep(100);     //(ms) a changer ?
    }
}

void start_state (void)
{
    chThdCreateStatic(waManageStates, sizeof(waManageStates), NORMALPRIO, ManageStates, NULL);
}

State get_robot_state () 
{
    return ROBOT_STATE;
}