// These define's must be placed at the beginning before #include "TimerInterrupt_Generic.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.

/*
>>>>>>>>>>>>>>>>>>>>>>>>> MACROS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/
#define INTERVAL_1US    1
#define INTERVAL_1MS    1e3       // counting in ms
#define INTERVAL_1SEC   1e6       // counting in us

#define TIMER_INTERRUPT_DEBUG         1
#define _TIMERINTERRUPT_LOGLEVEL_     4

#define BNO_PIN  16
#define BMP_PIN  17
#define INA_PIN  18
#define DS18_PIN 15
#define ACS_PIN  19

#define GREEN_LED  0
#define RED_LED    1

#define SDA_PIN   12
#define SCL_PIN   13
#define I2C_CLOCK 1000000

#define ACTIVATE_SERIAL 0   // set it to 1 if Serial communication is required

#define DUMMY_VAL -99
/*
>>>>>>>>>>>>>>>>>>>>>>> END OF MACROS <<<<<<<<<<<<<<<<<<<<<<<
*/


#include <stdio.h>
#include "SensorStruct.h"

Sensor SensorData={0};

#include <Wire.h>
#include <WiFi.h>
#include <WiFiUDP.h>

#include "hardware/timer.h"
#include "RPi_Pico_TimerInterrupt.h"
#include "pico/multicore.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h" 
#include "pico/stdlib.h"


#include "BMPSetup.h"
#include "ComSetup.h"
#include "BNOSetup.h"
#include "WifiSetup.h"
#include "ClkSetup.h"
#include "Switch.h"
#include "Profiler.h"
#include "Led.h"
#include "INASetup.h"
#include "DS18B20Setup.h"
#include "CurrentSensor.h"



RPI_PICO_Timer ITimer1(1);        //Timer for updating sensor data periodically
RPI_PICO_Timer ITimer2(2);        //Timer to check wifi connectivity periodically
RPI_PICO_Timer ITimer3(2);        //Timer for sending sensor data over the air


uint32_t free_hits =  0;

IPAddress ip(192,168,137,1);      //reciever ip addrs

WiFiUDP Udp;                      // creating an object of type WiFiUDP for sending data

int counter =0;
bool SensorSetup=false;           // a flag to check if all sensors have been initialized 

bool SendUDPData(struct repeating_timer *rt){
      
      if( WiFi.status() == WL_CONNECTED)
  {
      Udp.beginPacket(ip, 2198); 
      Udp.write((char*)&SensorData,sizeof(SensorData));
      Udp.endPacket();
  }

    return true;
}

// function to update sensor data regularly if the user has not selected 
// a particular sensor -99 will be transmitted.

bool UpdateSensorData(struct repeating_timer *rt){
  
  ReadSwitch();

  if(BMPinit) 
  {
    UpdateBmpData();
  }
  else
  { 
    SensorData.Pressure =  DUMMY_VAL * 100000;
    SensorData.Temperature =  DUMMY_VAL * 10   ;
  }

  if(IMUinit)
  {
     UpdateBNOData(); 
     CalibrateBNO();
  }
  else
  {
   SensorData.AccX  = DUMMY_VAL * 100;
   SensorData.AccY  = DUMMY_VAL * 100;
   SensorData.AccZ  = DUMMY_VAL * 100;
   SensorData.GyroX = DUMMY_VAL * 100;
   SensorData.GyroY = DUMMY_VAL * 100;
   SensorData.GyroZ = DUMMY_VAL * 100;
   SensorData.MagX = DUMMY_VAL * 10;
   SensorData.MagY = DUMMY_VAL * 10;
   SensorData.MagZ = DUMMY_VAL * 10;
   SensorData.OrientationX = DUMMY_VAL * 10;
   SensorData.OrientationY = DUMMY_VAL * 10;
   SensorData.OrientationZ = DUMMY_VAL * 10;
   SensorData.AccCalib = DUMMY_VAL;
   SensorData.GyroCalib = DUMMY_VAL;
   SensorData.MagCalib = DUMMY_VAL;
   SensorData.SysCalib = DUMMY_VAL;
  }

  if(INAinit)
     UpdateINAData();
  else
  {
   SensorData.BusVoltage = DUMMY_VAL * 100;
   SensorData.ShuntVoltage= DUMMY_VAL * 100;
  }
     
  if(ACSinit)
  {
   UpdateCurrent();
  }
  else
  {
   SensorData.Current = DUMMY_VAL * 100000;
  }

  if(RTDinit)
  {
  UpdateRTD();
  }
  else
  {
   SensorData.RTDTemp =DUMMY_VAL * 10  ;
  }

  SensorData.Time = getTimeStamp();
  
  if( WiFi.status() == WL_CONNECTED && digitalRead(RedLed) )
  {
    digitalWrite( RedLed   , LOW  );
    digitalWrite( GreenLed , HIGH );
  }
  SensorData.Counter= counter;
  if(counter == 10)
     counter=0;
  counter++;
      
 
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
 
  InitializeCOM();        
  InitializeSwitch();     //initializing switch
  ReadSwitch();      //reading switch position
  InitializeLED();

  InitializeBMP();
  InitializeINA();
  InitializeRTD();  
  InitializeCurrent();
  InitializeBNO();
  
  SensorSetup=true;
  ITimer3.attachInterruptInterval(INTERVAL_1MS  * 1  , SendUDPData);     //called after  1 milli sec

}

void setup1()
{   // wait till all sensors have been initialized
  while(!SensorSetup)
  {
    //Serial.println("Setting up sensors");
  }
  InitializeWifi();
  
  ITimer1.attachInterruptInterval(INTERVAL_1MS  * 1  , UpdateSensorData ); // called after 1 milli sec
  
  ITimer2.attachInterruptInterval(INTERVAL_1SEC * 15 , WifiStatusCheck );  //called after 15 seconds
     
}
void loop() {

    free_hits++;  
}
