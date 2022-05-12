#include <ch.h>
#include <hal.h>

#include <dance.h>
#include <flag_detection.h>
#include <obstacle_detection.h>
#include <selector.h>
#include <leds.h>
#include <state.h>

// 10 seconds in milliseconds
#define FLAG_DETECTION_DURATION 10000   

static State ROBOT_STATE = WAIT; 

// This thread needs a lot of memory
static THD_WORKING_AREA(waManageStates, 4096);  
static THD_FUNCTION(ManageStates, arg)
{
    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    // Type Flag defined in process_image.h
	static Flag country = UNDEFINED_FLAG;
    int last_selector = get_selector();

    while(1)
    {
        if ( obstacle_detected() )
        {
            ROBOT_STATE = PAUSE;
        }
        else
        {
            ROBOT_STATE = WAIT;
            if ( get_selector() != last_selector )
            {
                stop_dancing();
                last_selector = get_selector();
                ROBOT_STATE = FLAG_DETECTION;
            }
            if ( ROBOT_STATE == FLAG_DETECTION )
            {
                set_body_led(1);

                systime_t start_time = chVTGetSystemTime();

                while ( (chVTGetSystemTime() < start_time + FLAG_DETECTION_DURATION) 
                        & (country == UNDEFINED_FLAG) )
                {
                    country = get_flag();
                }
                
                ROBOT_STATE = (country == UNDEFINED_FLAG) ? WAIT : DANCE;
                // Prevent double detection of flag if selector turned more than one step
                last_selector = get_selector();
                set_body_led(0);
            }
            if ( ROBOT_STATE == DANCE )
            {
                restart_dance(country);
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
