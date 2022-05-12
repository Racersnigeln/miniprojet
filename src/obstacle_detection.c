#include <ch.h>
#include <hal.h>

#include <leds.h>               // To light up LED:s when obstacle detected
#include <motors.h>             // To stop motors when obstacle detected
#include <sensors/proximity.h>  // To get access to IR sensors
#include <msgbus/messagebus.h>  // To get access to IR sensors

#define OBSTACLE_THRESHOLD 100

// Create bus for IR-sensors
messagebus_t bus;
MUTEX_DECL(bus_lock);
CONDVAR_DECL(bus_condvar);

void init_obstacle_detection(void)
{
    // Init bus for IR-sensors
    messagebus_init(&bus, &bus_lock, &bus_condvar);

    // Init the proximity sensors
    proximity_start();
    calibrate_ir();
}

void panic(void)
{
    // What to do when obstacle is detected
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
    // What to do when obstacle is not detected
    clear_leds();
    set_front_led(0);
}

bool obstacle_detected(void)
{
    int max_proximity = 0;
    int proximity;

    // Use the highest proximity of sensors 1 to 8
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