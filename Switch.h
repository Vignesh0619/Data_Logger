#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"  

bool enable = true ;

bool volatile IMUinit  = false;   // if flase Sensor data will not be transmitter; if true sensor data will be transmitter               
bool volatile BMPinit  = false;   // if flase Sensor data will not be transmitter; if true sensor data will be transmitter
bool volatile INAinit  = false;   // if flase Sensor data will not be transmitter; if true sensor data will be transmitter
bool volatile Voltinit = false;   // if flase Sensor data will not be transmitter; if true sensor data will be transmitter
bool volatile RTDinit  = false;   // if flase Sensor data will not be transmitter; if true sensor data will be transmitter

void SetupSwitch()
{
  gpio_init(16);    // gpio 16 is switch for IMU
  gpio_init(17);    // gpio 17 is switch for BMP
  gpio_init(18);    // gpio 18 is switch for INA 
  gpio_init(19);    // gpio 19 is switch for Voltage sensor
  gpio_init(20);    // gpio 20 is switch for RTD

}

void ReadSwitch()
{  
   
      IMUinit  = (bool) gpio_get(16);  //gpio_get() will give the level of a particular gpio pin 
      BMPinit  = (bool) gpio_get(17);  //gpio_get() will give the level of a particular gpio pin 
      INAinit  = (bool) gpio_get(18);  //gpio_get() will give the level of a particular gpio pin 
      Voltinit = (bool) gpio_get(19);  //gpio_get() will give the level of a particular gpio pin 
      RTDinit  = (bool) gpio_get(20);  //gpio_get() will give the level of a particular gpio pin 
 
}