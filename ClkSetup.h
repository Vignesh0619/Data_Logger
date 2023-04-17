#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/structs/clocks.h"

typedef struct {
 uint32_t CurrentTime  ;
 uint32_t Offset       ;
}Time;

volatile Time TimeStamp ={0};

uint32_t getTimeStamp()
{
  TimeStamp.CurrentTime =  to_ms_since_boot(get_absolute_time()); // to_ms_since_boot(get_absolute_time()) will give milli sec since boot 
  
  static int i = 0 ;
  if( !i )
  {
      TimeStamp.Offset = TimeStamp.CurrentTime ;
      i=1;
      return ((0)) ;
  }
  else 
   return ((TimeStamp.CurrentTime - TimeStamp.Offset));

}
