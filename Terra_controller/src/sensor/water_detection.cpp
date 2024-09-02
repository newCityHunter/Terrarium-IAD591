#include "water_detection.h"
#include <Arduino.h>

// Constructor: initializes the pin for the water detection sensor
WaterDetection::WaterDetection(int pin) {
    sensorPin = pin;
    pinMode(sensorPin, INPUT);
}

// Destructor: does nothing specific in this case
WaterDetection::~WaterDetection() {
    // No resources to clean up
}

// Method to check if water is detected
bool WaterDetection::isWaterDetected() {
    int sensorValue = digitalRead(sensorPin);
    return sensorValue == HIGH; // Assume HIGH means water is detected
}
