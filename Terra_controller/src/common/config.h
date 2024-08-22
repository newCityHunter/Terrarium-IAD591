#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Sensor Pins
const int SOIL_MOISTURE_PIN = A0;
const int DHT_SENSOR_PIN = 2;

// Relay Control Pins
const int RELAY_PELTIER_PIN = 6;
const int RELAY_LIGHT_PIN = 5;
const int RELAY_PUMP_PIN = 4;
const int RELAY_VALVE_PIN = 3;

// RGB LED PWM Pins
const int LED_RED_PIN = 11;
const int LED_GREEN_PIN = 10;
const int LED_BLUE_PIN = 9;

#endif // CONFIG_H