#include "hal.h"
#include <chprintf.h>
#include <usbcfg.h>

#include <main.h>
#include <dance.h>
#include <process_image.h>
#include <button.h>

static enum {WAIT, FLAG_DETECTION, DANCE} ROBOT_STATE;

static THD_WORKING_AREA(waManageStates, 256);
static THD_FUNCTION(ManageStates, arg)
{
    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    ROBOT_STATE = WAIT;

    while(1)
    {
    	flag country = UNDEFINED;

        if (button_is_pressed())
        {
            ROBOT_STATE = FLAG_DETECTION;
        	chprintf((BaseSequentialStream *)&SDU1, "Bouton! <3\n");
        }
        if (ROBOT_STATE == FLAG_DETECTION)
        {
        	country = get_flag();
        	ROBOT_STATE = (country == UNDEFINED) ? WAIT : DANCE;
        }
        if (ROBOT_STATE == DANCE)
        {
        	dance(country);
        	ROBOT_STATE = WAIT;
        }
    }
}

void start_state (void)
{
    chThdCreateStatic(waManageStates, sizeof(waManageStates), NORMALPRIO, ManageStates, NULL);
}
