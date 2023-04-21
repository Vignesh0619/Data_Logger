#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

typedef struct{
    uint16_t pin26;
    uint16_t pin27;
    uint16_t pin28;
} AnalogData;

AnalogData AnalogValue = {0} ;

void SetupADC()
{
     adc_init();
     adc_gpio_init(28);
     adc_gpio_init(27);    
     adc_gpio_init(26);
}

void getADC26()
{
    adc_select_input(0);   // corresponds to gpio 27
    AnalogValue.pin26 = (int) adc_read() -30; 
    if(AnalogValue.pin26 < 0)
    AnalogValue.pin26 =  0 ;
}
void getADC27()
{
    adc_select_input(1);   // corresponds to gpio 27
    AnalogValue.pin27 = (int) adc_read() -30; 
    if(AnalogValue.pin27 < 0)
    AnalogValue.pin27 =  0 ;    
}
void getADC28()
{
    adc_select_input(2);   // corresponds to gpio 27
    AnalogValue.pin28 = (int) adc_read() - 30; 
    if(AnalogValue.pin28 < 0)
    AnalogValue.pin28 =  0 ;
}