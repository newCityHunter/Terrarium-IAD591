#include <Arduino.h>
#include "common/relay.h"

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
        float humid;
        if (condition.humidThreshold < humid)
            closeRelay();
        else
            openRelay();
        break;
    case WATER:
        float moistrue;
        if (condition.moistureThreshold < moistrue)
            closeRelay();
        else
            openRelay();
        break;
    case TEMPERATURE:
        float temperature;
        if (condition.temperatureThreshold > temperature)
            closeRelay();
        else
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
    digitalWrite(signalPin, HIGH);
    Serial.print("Relay ");
    Serial.print(relayName);
    Serial.println(" activated");
}

void Relay::openRelay()
{
    digitalWrite(signalPin, LOW);
    Serial.print("Relay ");
    Serial.print(relayName);
    Serial.println(" deactivated");
}