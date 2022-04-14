#include "hal.h"
#include <chprintf.h>
#include <usbcfg.h>

#include <main.h>
#include <dance.h>
#include <process_image.h>
#include <button.h>
#include <selector.h>

static enum {WAIT, FLAG_DETECTION, DANCE} ROBOT_STATE;

static THD_WORKING_AREA(waManageStates, 256);
static THD_FUNCTION(ManageStates, arg)
{
    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    ROBOT_STATE = WAIT;

	static Flag country = UNDEFINED;

    while(1)
    {
        if (get_selector() == 0)
        {
            ROBOT_STATE = FLAG_DETECTION;
        }
        if (ROBOT_STATE == FLAG_DETECTION)
        {
        	country = get_flag();
        	ROBOT_STATE = (country == UNDEFINED) ? WAIT : DANCE;
        }
        if (ROBOT_STATE == DANCE)
        {
            restart_dance(country);
        	ROBOT_STATE = WAIT;
        }
        chThdSleep(100);     //(ms) a changer ?
    }
}

void start_state (void)
{
    chThdCreateStatic(waManageStates, sizeof(waManageStates), NORMALPRIO, ManageStates, NULL);
}
