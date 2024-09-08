#include <Arduino.h>
#include "common/relay.h"
#include "sensor/heat_humid.h"
#include "sensor/soil_moisture.h"

void Relay::setRelayName(const char name[10])
{
    strncpy(relayName, name, sizeof(relayName) - 1);
    relayName[sizeof(relayName) - 1] = '\0'; // Ensure null-termination
}

void Relay::setSensor(Sensor &s)
{
    this->sensor = s;
}

void Relay::relayControl()
{
    switch (this->condition.type)
    {
    case HUMIDITY:
    {
        if (condition.humidThreshold[1] < sensor.humidity)
            closeRelay();
        else if (condition.humidThreshold[0] > sensor.humidity)
            openRelay();
        break;
    }
    case WATER:
    {
        if (sensor.waterDetected)
            closeRelay();
        else
            openRelay();
        break;
    }
    case TEMPERATURE:
    {
        if (condition.temperatureThreshold[1] > sensor.temperature)
            closeRelay();
        else if (condition.temperatureThreshold[0] < sensor.temperature)
            openRelay();
        break;
    }
    case TIME_BASED:
    {
        unsigned long currentTime = millis() / 60000;

        if (currentTime < condition.startTime || currentTime > (condition.startTime + condition.duration))
            closeRelay();
        else
            openRelay();
        break;
    }
    default:
    {
        openRelay();
        break;
    }
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