#pragma once

#include <stdio.h>

typedef struct{
    uint32_t Time ;
    int32_t  AccX ;
    int32_t  AccY ;
    int32_t  AccZ ;
    int32_t  GyroX;
    int32_t  GyroY;
    int32_t  GyroZ;
    int32_t  Pressure ;
    int32_t  Temperature     ;
    int32_t  RTDTemp  ;
    int32_t  MagX;
    int32_t  MagY;
    int32_t  MagZ;
    int32_t  OrientationX;
    int32_t  OrientationY;
    int32_t  OrientationZ;
    int32_t  Current;
    int32_t  BusVoltage;
    int32_t  ShuntVoltage;
    uint8_t  AccCalib;
    uint8_t  GyroCalib;
    uint8_t  MagCalib;
    uint8_t  SysCalib;
    uint32_t Counter;


}Sensor;
