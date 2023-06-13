#pragma once
#include "one_wire.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"

rom_address_t address{};
One_wire one_wire(28); 

void InitializeRTD()
{ 
 one_wire.init();
 one_wire.single_device_read_rom(address);     
}
void UpdateRTD() 
{             
 one_wire.convert_temperature(address, false, false); 
 SensorData.RTDTemp = one_wire.temperature(address) *10 ;
}
    
