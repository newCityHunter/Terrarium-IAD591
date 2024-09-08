#include <Arduino.h>
#include "common/config.h"
#include "sensor/water_detection.h"

void WaterDetection::readWaterDetection()
{
    // Read the value from the water detection sensor.
    int sensorValue = digitalRead(WATER_DETECTION_PIN);
    
    // Update the waterDetected status based on sensor reading
    waterDetected = (sensorValue == HIGH); // Assuming HIGH means water is detected
}

void WaterDetection::displayWaterDetection()
{
    if (waterDetected)
    {
        Serial.println("Water Detected: Yes");
    }
    else
    {
        Serial.println("Water Detected: No");
    }
}
