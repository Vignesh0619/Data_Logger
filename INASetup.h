#pragma once

#include "INA226.h"

INA226 INA(0x40);

void SetupINA()
{
  while (!INA.begin() );
}

// -0.0018325 0.99579 -0.19757
//  X^2         X       1

void UpdateINAData()
{
    SensorData.BusVoltage   = INA.getBusVoltage() * 100;
    SensorData.ShuntVoltage = INA.getShuntVoltage_mV() *100;
}

