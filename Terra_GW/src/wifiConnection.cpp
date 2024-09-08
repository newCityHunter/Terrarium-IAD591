#include "wifiConnection.h"

const char *ssid = WIFI_NAME_SSID;
const char *password = WIFI_PASSWORD;

void setupTSL()
{
    espClient.setInsecure();
}

void setupWifi()
{
    delay(100);
    Serial.printf("\nConnecting to %s\n", ssid);

    WiFi.begin(ssid, password);
    WiFi.mode(WIFI_STA);
    setupTSL();

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.printf("\nConnected to %s\n", ssid);
}
