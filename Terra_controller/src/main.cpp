#include <Arduino.h>
#include <ArduinoJson.h>

#include "common/config.h"
#include "common/relay.h"
#include "sensor/heat_humid.h"
#include "sensor/soil_moisture.h"
#include "sensor/water_detection.h"
#include "common/light.h"
#include "common/status_manager.h"

unsigned long previousMillis = 0;
const long waitWater = 60000; // 1 phút

unsigned long checkInterval = 30000; // Thời gian chờ trước khi kiểm tra (30 giây)
unsigned long lastCheckTime = 0;     // Thời gian lần cuối cùng kiểm tra

Relay pumpRelay;
Relay valveRelay;
Relay lightRelay;
Relay peltierRelay;

HeatHumid heatHumid;
SoilMoisture soilMoisture;
WaterDetection waterDetection;

Light light;

void setup()
{
    setupRelay();
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

    Serial.begin(9600);
}

void loop()
{
    unsigned long currentMillis = millis();

    if (currentMillis - lastCheckTime >= checkInterval)
    {

        heatHumid.readHeatHumid();
        soilMoisture.readSoilMoisture();
        waterDetection.readWaterDetection();

        pumpRelay.relayControl();
        valveRelay.relayControl();
        lightRelay.relayControl();
        peltierRelay.relayControl();

        // Thu thập dữ liệu từ các cảm biến và relay
        String jsonData = collectData();
        // Gửi dữ liệu đã thu thập được qua Serial
        sendDataOverSerial(jsonData);

        lastCheckTime = currentMillis;
    }

    String requestFromEsp = Serial.readString();
    if (requestFromEsp != NULL && requestFromEsp != "")
    {
        handleRequest(requestFromEsp);
    }
}
