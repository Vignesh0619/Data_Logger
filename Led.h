#pragma once

#include "pico/stdlib.h"

int GreenLed = 0;   //Green Led indicates that Wifi is connected
int RedLed   = 1;   //Red Led indicates that Wifi is not connected

void InitializeLED()
{
 pinMode( GreenLed , OUTPUT );
 pinMode( RedLed   , OUTPUT );
}