#pragma once

#include <Wire.h>
#include <stdio.h>

int coms_setup_status=0;   // if 0 setup not complete; 1 setup complete

void InitializeCOM()
{

  Wire.setSDA(SDA_PIN);          // setting up I2C coms for RPI and MPU comms
  Wire.setSCL(SCL_PIN);
  Wire.begin();
  
  Wire.setClock(I2C_CLOCK);
  
  if(ACTIVATE_SERIAL)
  {
  Serial.begin(115200);     // not compulsory to start Serial
  while(!Serial);
  }

 
  coms_setup_status=1;
}
