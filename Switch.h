#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"  


bool volatile IMUinit     = false;   // if flase Sensor data will not be transmitter; if true sensor data will be transmitter               
bool volatile BMPinit     = false;   // if flase Sensor data will not be transmitter; if true sensor data will be transmitter
bool volatile INAinit     = false;   // if flase Sensor data will not be transmitter; if true sensor data will be transmitter
bool volatile ACSinit     = false;   // if flase Sensor data will not be transmitter; if true sensor data will be transmitter
bool volatile RTDinit     = false;   // if flase Sensor data will not be transmitter; if true sensor data will be transmitter

int volatile SwitchState    = 0 ;

void InitializeSwitch()
{
  gpio_init(BNO_PIN);    // gpio 16 is switch for IMU
  gpio_init(BMP_PIN);    // gpio 17 is switch for BMP
  gpio_init(INA_PIN);    // gpio 18 is switch for INA 
  gpio_init(DS18_PIN);   // gpio 19 is switch for RTD
  gpio_init(ACS_PIN);    // gpio 20 is switch for Current sensor
}

void ReadSwitch()
{  
  IMUinit     = (bool) gpio_get(BNO_PIN);  //gpio_get() will give the level of a particular gpio pin 
  BMPinit     = (bool) gpio_get(BMP_PIN);  //gpio_get() will give the level of a particular gpio pin 
  INAinit     = (bool) gpio_get(INA_PIN);  //gpio_get() will give the level of a particular gpio pin 
  ACSinit     = (bool) gpio_get(ACS_PIN);  //gpio_get() will give the level of a particular gpio pin 
  RTDinit     = (bool) gpio_get(DS18_PIN); //gpio_get() will give the level of a particular gpio pin  
  SwitchState =( ( IMUinit * 10000 ) + ( BMPinit * 1000 ) + ( INAinit * 100 ) + ( ACSinit * 10 ) + ( RTDinit * 1 ) ) ;
}