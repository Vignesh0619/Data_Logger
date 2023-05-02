#pragma once

#include <stdio.h>

typedef struct{
     uint32_t time;
     int16_t  acc_x;
     int16_t  acc_y;
     int16_t  acc_z;
     int16_t  gyro_x;
     int16_t  gyro_y;
     int16_t  gyro_z;
     int16_t  pressure;
     int16_t  temp;
     int16_t  RTDTemp;
     int16_t  mag_x;
     int16_t  mag_y;
     int16_t  mag_z;
     int16_t  orient_x;
     int16_t  orient_y;
     int16_t  orient_z;
     int16_t  linear_acc_x;
     int16_t  linear_acc_y;
     int16_t  linear_acc_z;

}Sensor;
