#include <Arduino.h>
#include "common/config.h"
#include "common/relay.h"
#include "sensor/heat_humid.h"
#include "sensor/soil_moisture.h"

Relay pumpRelay;
Relay valveRelay;
Relay lightRelay;
HeatHumid heatHumid;
SoilMoisture soilMoisture;

void setup()
{
    strncpy(pumpRelay.relayName, "Pump", sizeof(pumpRelay.relayName));
    pumpRelay.signalPin = PUMP;

    strncpy(pumpRelay.relayName, "Valve", sizeof(pumpRelay.relayName));
    valveRelay.signalPin = VALVE;

    strncpy(pumpRelay.relayName, "Light", sizeof(pumpRelay.relayName));
    lightRelay.signalPin = LIGHT;

    // relay pin mode
    pinMode(pumpRelay.signalPin, OUTPUT);
    pinMode(valveRelay.signalPin, OUTPUT);
    pinMode(lightRelay.signalPin, OUTPUT);

    // RGB pin mode
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);

    // sensor pin mode
    pinMode(SOILMOISTUREPIN, OUTPUT);
    pinMode(DHTPIN, OUTPUT);
}

void loop()
{
}
