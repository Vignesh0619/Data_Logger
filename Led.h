#pragma once

#include "pico/stdlib.h"

int GreenLed = 21;   //Green Led indicates that Wifi is connected
int RedLed   = 22;   //Red Led indicates that Wifi is not connected

void SetupLed()
{
    pinMode( GreenLed , OUTPUT );
    pinMode( RedLed   , OUTPUT );
}