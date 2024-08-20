#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

//sensor
const int SOILMOISTUREPIN = A0;
const int DHTPIN = 2;

//Relay control
const int LIGHT = 5;
const int PUMP = 4;
const int VALVE = 3;

//RGB LED
const int RED = 13;
const int GREEN = 12;
const int BLUE = 11;

#endif // CONFIG_H