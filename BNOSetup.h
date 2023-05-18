#pragma once

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

sensors_event_t orientationData , angVelocityData , linearAccelData, magnetometerData, accelerometerData, gravityData;
uint8_t sys, gyro, accel, mag = 0;

Adafruit_BNO055 bno  = Adafruit_BNO055(55, 0x28, &Wire);

void SetupBNO()
{
      while(! bno.begin())
    {

    }
}
void CalibrateBNO()
{  
    bno.getCalibration(&sys, &gyro, &accel, &mag);
    SensorData.AccCalib  = accel;
    SensorData.GyroCalib = gyro ;
    SensorData.MagCalib  = mag  ;
    SensorData.SysCalib  = sys ;
}
void UpdateBNOData()
{   
 
  bno.getEvent(&orientationData  , Adafruit_BNO055::VECTOR_EULER);          // gives gyro data in degree
  bno.getEvent(&angVelocityData  , Adafruit_BNO055::VECTOR_GYROSCOPE);      // gives gyro data in deg/s
  bno.getEvent(&linearAccelData  , Adafruit_BNO055::VECTOR_LINEARACCEL);    // acc data without constant acceleration such as gravity
  bno.getEvent(&magnetometerData , Adafruit_BNO055::VECTOR_MAGNETOMETER);   // gives magentometer data in uT
  bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);  // acc data with gravity

  SensorData.AccX = accelerometerData.acceleration.x * 100;
  SensorData.AccY = accelerometerData.acceleration.y * 100;
  SensorData.AccZ = accelerometerData.acceleration.z * 100;

  SensorData.GyroX = angVelocityData.gyro.x * 100;
  SensorData.GyroY = angVelocityData.gyro.y * 100;
  SensorData.GyroZ = angVelocityData.gyro.z * 100;

  SensorData.orientationX = orientationData.orientation.x * 10;
  SensorData.orientationY = orientationData.orientation.y * 10;
  SensorData.orientationZ = orientationData.orientation.z * 10;

  SensorData.MagX = magnetometerData.magnetic.x * 100;
  SensorData.MagY = magnetometerData.magnetic.y * 100;
  SensorData.MagZ = magnetometerData.magnetic.z * 100;
}