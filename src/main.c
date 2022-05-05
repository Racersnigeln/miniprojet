// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>

#include "ch.h"
#include "hal.h"
#include "memory_protection.h"
// #include <messagebus.h>
#include <usbcfg.h>
#include <main.h>
#include <motors.h>
#include <camera/po8030.h>
#include <chprintf.h>
#include <sensors/proximity.h>
#include <audio/audio_thread.h>

#include <flag_detection.h>
#include <dance.h>
#include <obstacle.h>
#include <state.h>

static void serial_start(void)
{
	static SerialConfig ser_cfg = {
	    115200,
	    0,
	    0,
	    0,
	};

	sdStart(&SD3, &ser_cfg); // UART3.
}

messagebus_t bus;
MUTEX_DECL(bus_lock);
CONDVAR_DECL(bus_condvar);

int main(void)
{
    // Init bus for IR-sensors
    messagebus_init(&bus, &bus_lock, &bus_condvar);

    halInit();
    chSysInit();
    mpu_init();

    //start the serial communication
    serial_start();

    //start the USB communication
    usb_start();

    init_camera();

	motors_init();

    //inti sound
    dac_start();

    // init the proximity sensors
    proximity_start();
    calibrate_ir();

    // start the thread for dance
    start_dance();

    // start the thread for update state
    start_state();

    
    /* Infinite loop. */
    while (1) {
    	//waits 1 second
        chThdSleepMilliseconds(1000);

    }
}

#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}
