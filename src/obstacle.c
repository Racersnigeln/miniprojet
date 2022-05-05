#include "ch.h"
#include "hal.h"
#include <usbcfg.h>

#include <main.h>
#include <leds.h>
#include <motors.h>
#include <sensors/proximity.h>

#define OBSTACLE_THRESHOLD 100

void panic(void)
{
    set_led(LED1, 1);
    set_led(LED3, 1);
    set_led(LED5, 1);
    set_led(LED7, 1);

    set_front_led(1);

    left_motor_set_speed(0);
    right_motor_set_speed(0);
}

void unpanic(void)
{
    clear_leds();
    set_front_led(0);
}

bool obstacle_detected(void)
{
    int max_proximity = 0;
    int proximity;

    for (uint8_t i = 0; i <= 7; i++)
    {
        proximity = get_calibrated_prox(i);
        max_proximity = (proximity > max_proximity) ? proximity : max_proximity;
    }
    
    if (max_proximity > OBSTACLE_THRESHOLD)
    {
        panic();
        return true;
    }

    unpanic();

    return false;
}