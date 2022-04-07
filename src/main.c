#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ch.h"
#include "hal.h"
#include "memory_protection.h"
#include <usbcfg.h>
#include <main.h>
#include <motors.h>
#include <camera/po8030.h>
#include <chprintf.h>

#include <process_image.h>
#include <music.h>
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

int main(void)
{

    halInit();
    chSysInit();
    mpu_init();

    //start the serial communication
    serial_start();
    //start the USB communication
    usb_start();
    //start the camera
    dcmi_start();
	po8030_start();
	//init the motors
	motors_init();

	//stars the thread for the processing of the image
	process_image_start();
	start_state();

    /* Infinite loop. */
    while (1) {
    	//waits 1 second
//    	chprintf((BaseSequentialStream *)&SDU1, "Bouton! <3\n");
        chThdSleepMilliseconds(1000);
    }
}

#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}
