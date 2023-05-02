#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

typedef struct{
    uint16_t temperature;
}  RTD;

RTD RTD_data = {0};

void SetupRTD()
{
  adc_init();
  adc_gpio_init(26);
}

void getRTDTemp()
{
    adc_select_input(0);
    RTD_data.temperature = (int) adc_read();
}