#pragma once

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

//
// the data obtained by using the sensor lbrary will be in decimal but we will mutliply
// by 10/100 as per  the no.of decimal places we want and store that value as int
//
// Struct to access the BMP pressure and temperature data
typedef struct {         
  int pressure;
  int temp;
} BMP_DATA;

volatile BMP_DATA bmp_data = {0};

Adafruit_BMP280 bmp;        //Struct define in Adafruit bmp library
int bmp_setup_status=0;     // if 0 setup not complete; 1 setup complete

void SetupBMP() {  
  
  unsigned bmp_status;
  bmp_status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

    bmp_setup_status=1;

}

void UpdateBmpData()
{
    //
    // Since data is being sent through a struct which has all it member variables
    // int16_t or similar we will multiply the required sensor data with 10/100 etc 
    // based on the precision(i.e no of decimal places we want)
    // the plotter will then convert it into double
    //
    SensorData.pressure = bmp.readPressure();
    SensorData.temp     = bmp.readTemperature()*10;  
 
}
