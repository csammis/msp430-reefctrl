#include "sensor.h"

#include <msp430.h>
#include "peripherals.h"
#include "graphics.h"

void init_sensors()
{
    P1OUT |= LVL_TANK_PIN;
    P1REN  = LVL_TANK_PIN;
}

void sensor_tank_level_high()
{
    graphics_flash_status(STATUS_NORMAL);
}

void sensor_tank_level_low()
{
    graphics_flash_status(STATUS_EMPTY);
}

//eof

