#include <ch.h>
#include <hal.h>
#include <memory_protection.h>

#include <flag_detection.h>
#include <dance.h>
#include <obstacle_detection.h>
#include <state.h>

int main(void)
{
    halInit();
    chSysInit();
    mpu_init();

    // Initiate camera for flag detection
    init_camera();

    // Initiate the sensors for obstacle detection
    init_obstacle_detection();

    // Start the thread for dance
    start_dance();

    // Start the thread for update state
    start_state();

    while (1) 
    {
        chThdSleepMilliseconds(1000);
    }
}

#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}
