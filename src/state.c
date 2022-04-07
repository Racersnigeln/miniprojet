#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include <usbcfg.h>

#include <main.h>
#include <button.h>

static enum {WAIT, FLAG_DETECTION} ROBOT_STATE;

static THD_WORKING_AREA(waManageStates, 256);
static THD_FUNCTION(ManageState, arg) 
{
    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    ROBOT_STATE = WAIT;

    while(1)
    {
    	chprintf((BaseSequentialStream *)&SDU1, "Bouton! <3\n");
        if (button_is_pressed())
        {
            ROBOT_STATE = FLAG_DETECTION;

        }
    }
}

void start_state (void)
{
    chThdCreateStatic(waManageStates, sizeof(waManageStates), NORMALPRIO, ManageState, NULL);
}
