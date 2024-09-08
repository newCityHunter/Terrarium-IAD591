#include <Arduino.h>
#include "common/relay.h"
#include "sensor/heat_humid.h"
#include "sensor/soil_moisture.h"

void Relay::setRelayName(const char name[10])
{
    strncpy(relayName, name, sizeof(relayName) - 1);
    relayName[sizeof(relayName) - 1] = '\0'; // Ensure null-termination
}

void Relay::relayControl()
{
    switch (this->condition.type)
    {
    case HUMIDITY:
        
        if (condition.humidThreshold[1] < heathumid.humidity)
            closeRelay();
        else if (condition.humidThreshold[0] > heathumid.humidity)
            openRelay();
        break;
    case WATER:
        
        if (condition.moistureThreshold[1] < soilMoisture.moisture)
            closeRelay();
        else if (condition.moistureThreshold[0] > soilMoisture.moisture)
            openRelay();
        break;
    case TEMPERATURE:
        
        if (condition.temperatureThreshold[1] > heathumid.temperature)
            closeRelay();
        else if (condition.temperatureThreshold[0] < heathumid.temperature)
            openRelay();
        break;
    case TIME_BASED:
        unsigned long currentTime = millis() / 60000;

        if (currentTime < condition.startTime || currentTime > (condition.startTime + condition.duration))
            closeRelay();
        else
            openRelay();
        break;
    default:
        openRelay();
        break;
    }
}

void Relay::closeRelay()
{
    state = false;
    digitalWrite(signalPin, HIGH);
    Serial.print("Relay ");
    Serial.print(relayName);
    Serial.println(" activated");
}

void Relay::openRelay()
{
    state = true;
    digitalWrite(signalPin, LOW);
    Serial.print("Relay ");
    Serial.print(relayName);
    Serial.println(" deactivated");
}