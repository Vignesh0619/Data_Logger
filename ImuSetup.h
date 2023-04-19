// Basic demo for accelerometer readings from Adafruit MPU6050
#pragma once
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "ComSetup.h"

Adafruit_MPU6050 mpu;       // a struct defined in the adafruit MPU library 

int imu_setup_status=0;     // if 0 setup not complete; 1 setup complete

sensors_event_t a, g, temp;

typedef struct {
  float acc_x;
  float acc_y;
  float acc_z;
  float gyro_x;
  float gyro_y;
  float gyro_z;
  float temp;
} IMU_DATA;                     // a struct to store Imu data and allow global access to them

volatile IMU_DATA imu_data = {0.0};

void SetupIMU(void) {

   
    if (!mpu.begin()) {
    //if we enter here then that mean mpu was not detected and program enter infinte loop
    while (1) {}
  }

  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);// change this from _8_G to _4_G etc to change rangee of measurement 
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    //Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    //Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    //Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    //Serial.println("+-16G");
    break;
  }

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);   // change to 250,500,1000,2000 as per application
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    //Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    //Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    //Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    //Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);  // change value to modify the inbuilt filter bandwidth
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    //Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    //Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    //Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    //Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    //Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    //Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    //Serial.println("5 Hz");
    break;
  }

  imu_setup_status=1;
}


void UpdateImuData() {

  /* Get new sensor events with the readings */
  mpu.getEvent(&a, &g, &temp);  // has to be called everytime to get new sensor readings
  
  imu_data.acc_x  = a.acceleration.x;
  imu_data.acc_y  = a.acceleration.y;
  imu_data.acc_z  = a.acceleration.z;
  imu_data.gyro_x = g.gyro.x;
  imu_data.gyro_y = g.gyro.y;
  imu_data.gyro_z = g.gyro.z; 
}
