// These define's must be placed at the beginning before #include "TimerInterrupt_Generic.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.


#define TIMER_INTERRUPT_DEBUG         1
#define _TIMERINTERRUPT_LOGLEVEL_     4

#include <Wire.h>
#include <stdio.h>
#include "BMPSetup.h"
#include "ComSetup.h"
#include "ImuSetup.h"
#include "WifiSetup.h"
#include "pico/stdlib.h"
#include "ClkSetup.h"
#include "Switch.h"
#include "Profiler.h"
#include "Led.h"
#include "hardware/timer.h"
#include "RPi_Pico_TimerInterrupt.h"

#define INTERVAL_1US    1
#define INTERVAL_1MS    1e3       // counting in us
#define INTERVAL_1SEC   1e6       // counting in us


RPI_PICO_Timer ITimer1(1);        //Timer for updating sensor data periodically
RPI_PICO_Timer ITimer2(2);        //Timer to check wifi connectivity periodically
RPI_PICO_Timer ITimer3(2);        //Timer for sending sensor data over the air


uint32_t free_hits =  0;


String dataString  = String("");


//function to send sensor data thrugh UDP

bool SendUDPData(struct repeating_timer *rt){
    if( WiFi.status() == WL_CONNECTED)
   {  
    dataString += String( (float) TimeStamp.CurrentTime,3);

    if(IMUinit)
    {
        dataString += String("|");
        dataString += String(imu_data.acc_x,2);
        dataString += String("|");
        dataString += String(imu_data.acc_y,2);
        dataString += String("|");
        dataString += String(imu_data.acc_z,2);
        dataString += String("|");
        dataString += String(imu_data.gyro_x,2);
        dataString += String("|");
        dataString += String(imu_data.gyro_y,2);
        dataString += String("|");
        dataString += String(imu_data.gyro_z,2);
    } 
    
    if(BMPinit)
    {
        dataString += String("|");
        dataString += String((int) bmp_data.pressure);
        dataString += String("|");
        dataString += String(bmp_data.temp,1);
    }

      udp.broadcastTo(dataString.c_str(),2312);   
    
   }
  
    dataString = String(""); 
    ITimer3.restartTimer();

    return true;
}

// function to update sensor data regularly

bool UpdateSensorData(struct repeating_timer *rt){

  if(BMPinit) 
      UpdateBmpData();

  if(IMUinit)
      UpdateImuData();

  TimeStamp.CurrentTime = getTimeStamp();
  
  if( WiFi.status() == WL_CONNECTED && digitalRead(RedLed) )
  {
    digitalWrite( RedLed   , LOW  );
    digitalWrite( GreenLed , HIGH );
  }

  ITimer1.restartTimer();
  

  return true;

}

//function to  check for wifi connectivity and to reconnect to wifi if disconnected while running

bool WifiStatusCheck( struct repeating_timer *rt){
  
  if( WiFi.status() != WL_CONNECTED)
  {
    ReconnectWifi();
  }

   return true;
}



void setup() {

  SetupSwitch();     //initializing switch
  ReadSwitch();      //reading switch position

  SetupCOM();
   if( IMUinit )
  {
    SetupIMU();
  }

  if( BMPinit )         
  {
    SetupBMP();
  }
  
  SetupLed();

  SetupWifi();

  // attaching functions which are to be called after specified amoount of time


  ITimer1.attachInterruptInterval(INTERVAL_1MS  * 1   , UpdateSensorData ); // called after 1 milli sec
  
  ITimer3.attachInterruptInterval(INTERVAL_1US  * 900   , SendUDPData);       //called after  5 milli sec
  
  ITimer2.attachInterruptInterval(INTERVAL_1SEC * 15  , WifiStatusCheck );  //called after 15 seconds
  
}

void loop() {

    free_hits++;    
    
}
