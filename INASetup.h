#pragma once

#include "INA226.h"

INA226 INA(0x40);

void SetupINA()
{
  while (!INA.begin() );
}

// -0.0018325 0.99579 -0.19757
//  c(1)         c(2)      c(3)

void UpdateINAData()
{
    SensorData.BusVoltage   = (INA.getBusVoltage() * (-0.00016672 + 0.95586 ) -0.015364 )* 100;
    SensorData.ShuntVoltage = INA.getShuntVoltage_mV() *100;
}

