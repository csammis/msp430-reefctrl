#include "sensor.h"

#include <msp430.h>
#include "peripherals.h"
#include "graphics.h"

#define SENSOR_STATE_HIGH   1
#define SENSOR_STATE_LOW    0

unsigned char sensorState;

void init_sensors()
{
    sensorState = SENSOR_STATE_HIGH;
    
    P1OUT |= LVL_TANK_PIN;
    P1REN  = LVL_TANK_PIN;

    sensorState = (P1IN & LVL_TANK_PIN) ? SENSOR_STATE_HIGH : SENSOR_STATE_LOW;
}

void sensor_tank_level_high()
{
    if (sensorState != SENSOR_STATE_HIGH)
    {
        // stop pumping
    }

    graphics_flash_status(STATUS_NORMAL);
}

void sensor_tank_level_low()
{
    if (sensorState != SENSOR_STATE_LOW)
    {
        // begin pumping

        // eventing: in_ticks_do(int, (void*)());
    }

    graphics_flash_status(STATUS_EMPTY);
}

//eof

