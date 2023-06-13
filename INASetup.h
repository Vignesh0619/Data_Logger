#pragma once

#include "INA226.h"

INA226 INA(0x40);

void InitializeINA()
{
  while (!INA.begin() );
}

void UpdateINAData()
{
 SensorData.BusVoltage   = (INA.getBusVoltage() * (-0.00016672 + 0.95586 ) -0.015364 )* 100;// mapping the values to reduce error
 SensorData.ShuntVoltage = INA.getShuntVoltage_mV() *100;
}

