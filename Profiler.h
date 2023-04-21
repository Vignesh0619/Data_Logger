#pragma once

#include "hardware/timer.h"

typedef struct{
   float Ti;
   float Tf;
   float DeltaT;
}Profiler;

Profiler Profile ;

void getTi()
{
    Profile.Ti=to_us_since_boot(get_absolute_time());
}

void getTf()
{
    Profile.Tf=to_us_since_boot(get_absolute_time());
}

void getDeltaT()
{
    Profile.DeltaT = Profile.Tf - Profile.Ti;
    Serial.println(Profile.DeltaT);
}