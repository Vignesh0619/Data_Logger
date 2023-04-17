#pragma once

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>


// Struct to access the BMP pressure and temperature data

typedef struct {         
  float pressure;
  float temp;
} BMP_DATA;

volatile BMP_DATA bmp_data = {0.0};

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
    bmp_data.pressure = bmp.readPressure();
    bmp_data.temp     = bmp.readTemperature();     
}
