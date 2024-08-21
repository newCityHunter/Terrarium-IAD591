#include <Arduino.h>
#include "common/relay.h"

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