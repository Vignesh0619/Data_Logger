#pragma once
int coms_setup_status=0;   // if 0 setup not complete; 1 setup complete

void SetupCOM()
{


  Wire.setSDA(0);  // setting up I2C coms for RPI and MPU comms
  Wire.setSCL(1);
  Wire.begin();
  Wire.setClock(1000000);

  Serial.begin(38400);    // not compulsory to start Serial
    
  while(!Serial);
  coms_setup_status=1;
}