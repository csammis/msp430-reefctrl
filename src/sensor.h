/*
 * reefctrl
 * MSP430-based code for a reef aquarium controller
 *
 * Copyright (c) 2011, Chris Sammis (http://csammisrun.net)
 * Source released under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 * sensor.h
 *  Methods for interfacing with level switches
 */

#ifndef __SENSOR_H__
#define __SENSOR_H__

// init_sensors
//  Initializes the connected sensors and internal state counters
void init_sensors();

// sensor_tank_level_high
//  Call this method from the main timer loop when the tank level sensor is high
void sensor_tank_level_high();

// sensor_tank_level_low
//  Call this method from the main timer loop when the tank level sensor is low
void sensor_tank_level_low();

#endif // __SENSOR_H__

//eof

