#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"



void SetupCurrent()
{
  adc_init();
  adc_gpio_init(26);
}

void UpdateCurrent()
{
    adc_select_input(0);
    RTD_data.temperature = (int) adc_read();
}