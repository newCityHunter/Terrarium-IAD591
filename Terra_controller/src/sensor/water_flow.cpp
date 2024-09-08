#include "common/config.h"
#include "sensor/water_flow.h"

// Interrupt function to increment pulse count
void pulseCounter() {
    extern WaterFlow flowSensor;
    flowSensor.pulseCount++;
}

void WaterFlow::begin() {
    pinMode(sensorPin, INPUT);          // Set the sensor pin as an input
    pulseCount = 0;                     // Reset the pulse counter
    isAvailable = false;                // Initially, set water flow as not available
    attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, RISING);  // Attach interrupt to sensor pin
}

bool WaterFlow::isWaterAvailable() {
    if (pulseCount > 0) {
        isAvailable = true;             // Water is flowing
    } else {
        isAvailable = false;            // No water flow detected
    }
    return isAvailable;
}