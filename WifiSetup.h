#pragma once

#ifndef ARDUINO_RASPBERRY_PI_PICO_W
 #define ARDUINO_RASPBERRY_PI_PICO_W
#endif

#include <WiFi.h>
#include <Arduino.h>
#include <AsyncUDP_RP2040W.h>
#include "Led.h"

int wifi_status       = WL_IDLE_STATUS;

long int  WifiTicks   = 0 ;    // when this variable reaches a multiple of 2000 it means that approx 10 secs have passed 

char ssid[]   = "test";           // user id for the hotspot
char pass[]   = "password";       // password for the hotspot

AsyncUDP udp;

void InitializeWifi()
{
    digitalWrite( RedLed , HIGH );
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid , pass);
    while ( WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    WifiTicks++;
    if(WifiTicks == 20)
    {
      //WiFi.mode(WIFI_STA);
      WiFi.begin(ssid , pass);
    }
    // Connect to WPA/WPA2 network
    
  }

  digitalWrite( RedLed , LOW );
  digitalWrite( GreenLed , HIGH );

}
 void ReconnectWifi()
 {
    digitalWrite( GreenLed , LOW); 
    digitalWrite( RedLed , HIGH );
    //WiFi.mode(WIFI_STA);
    WiFi.begin(ssid , pass);
 }
