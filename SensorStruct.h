#pragma once

#include <stdio.h>

typedef struct{
         uint32_t Time    ;
    uint32_t  AccX    ;
    uint32_t  AccY    ;
    uint32_t  AccZ    ;
    uint32_t  GyroX   ;
    uint32_t  GyroY   ;
    uint32_t  GyroZ   ;
    uint32_t  Pressure ;
    uint32_t  Temperature     ;
    uint32_t  RTDTemp  ;
    uint32_t  MagX;
    uint32_t  MagY;
    uint32_t  MagZ;
    uint32_t  OrientationX;
    uint32_t  OrientationY;
    uint32_t  OrientationZ;
    uint32_t  LinearAccX;
    uint32_t  LinearAccY;
    uint32_t  LinearAccZ;
    uint32_t  current;
    uint32_t  BusVoltage;
    uint32_t  ShuntVoltage;
    uint8_t  AccCalib;
    uint8_t  GyroCalib;
    uint8_t  MagCalib;
    uint8_t  SysCalib;
    uint32_t Counter;


}Sensor;
