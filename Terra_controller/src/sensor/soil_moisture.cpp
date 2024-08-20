#include <Arduino.h>
#include "common/config.h"
#include "sensor/soil_moisture.h"

void SoilMoisture::readSoilMoisture()
{
    moisture = analogRead(SOILMOISTUREPIN);
}

void SoilMoisture::displaySoilMoisture()
{
    int moistureLevel = map(moisture, 1023, 0, 0, 100);
    Serial.write("Moisture: %f\n",moistureLevel);
}