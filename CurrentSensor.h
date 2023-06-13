#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

int RawValue;
int RawSum;
int Raw;
int Sum;
int Offset;
float Current;
float MappedCurrent;
float Volts;
int i=0;
void InitializeCurrent()
{
  adc_init();
  adc_gpio_init(26);
  adc_select_input(0);
  // calculating offset
  for(i=0;i<50;i++)
  {
     RawValue = ((int) adc_read());
     Sum=Sum+RawValue;
  }
  Offset=Sum/50;
  delay(5000);
}
// the adc value is multiplied with 0.0097 to convert 0-4095 to -20A to +20A
// so sensitivity factor is 40/4095=0.0097
void UpdateCurrent()
{
    Current = ((int) adc_read()- Offset)* 0.0097;
    SensorData.Current= (Current*1.3592 - 0.10321)* 100;
}