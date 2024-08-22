#include <Arduino.h>
#include "common/config.h"
#include "common/relay.h"
#include "sensor/heat_humid.h"
#include "sensor/soil_moisture.h"

Relay pumpRelay;
Relay valveRelay;
Relay lightRelay;
Relay peltierRelay;
HeatHumid heatHumid;
SoilMoisture soilMoisture;

void setup()
{
    pumpRelay.setRelayName("Pump");
    pumpRelay.signalPin = RELAY_PUMP_PIN;

    valveRelay.setRelayName("Valve");
    valveRelay.signalPin = RELAY_VALVE_PIN;

    lightRelay.setRelayName("Light");
    lightRelay.signalPin = RELAY_LIGHT_PIN;

    peltierRelay.setRelayName("Peltier");
    peltierRelay.signalPin = RELAY_PELTIER_PIN;

    // relay pin mode
    pinMode(pumpRelay.signalPin, OUTPUT);
    pinMode(valveRelay.signalPin, OUTPUT);
    pinMode(lightRelay.signalPin, OUTPUT);
    pinMode(peltierRelay.signalPin, OUTPUT);

    // RGB pin mode
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_BLUE_PIN, OUTPUT);

    // sensor pin mode
    pinMode(SOIL_MOISTURE_PIN, INPUT);
    pinMode(DHT_SENSOR_PIN, INPUT);
}

void loop()
{
}
