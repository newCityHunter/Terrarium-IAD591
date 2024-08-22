#include <Arduino.h>
#include "common/relay.h"

void Relay::setRelayName(const char name[10])
{
    strncpy(relayName, name, sizeof(relayName) - 1);
    relayName[sizeof(relayName) - 1] = '\0'; // Ensure null-termination
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