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
float Volts;
int i=0;
void SetupCurrent()
{
  Serial.begin(9600);
  adc_init();
  adc_gpio_init(26);
  adc_select_input(0);
  for(i=0;i<50;i++)
  {
     RawValue = ((int) adc_read());
     Sum=Sum+RawValue;
  }
  Offset=Sum/50;
  Serial.println(Offset);
  delay(5000);
}

void UpdateCurrent()
{
    i++;
    Current = ((int) adc_read())- Offset;
    //SensorData.Current=(((Current*0.0097) *(0.71305)) + 0.031746) * 100000;
    SensorData.Current=Current* 0.002442 * 100000;
  //   if(i>=100)
  //   {
  //     Current= (RawSum/100)*0.0097;
  //     RawSum=0;
  //     i=0;
  //     SensorData.Current=Current;// *(0.0050+0.71305) - 0.31746)*10;
  //  }
}