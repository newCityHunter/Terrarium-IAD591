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
StatusManager statusManager;


void setup()
{
    pumpRelay.setRelayName("Pump");
    pumpRelay.signalPin = RELAY_PUMP_PIN;
    pumpRelay.condition.initMoistureCondition(0.7,0.15);

    valveRelay.setRelayName("Valve");
    valveRelay.signalPin = RELAY_VALVE_PIN;
    valveRelay.condition.initMoistureCondition(0.7,0.15);

    lightRelay.setRelayName("Light");
    lightRelay.signalPin = RELAY_LIGHT_PIN;
    lightRelay.condition.initTimeBasedCondition(14400, 18000); // 4 tiếng từ 5h sáng

    peltierRelay.setRelayName("Peltier");
    peltierRelay.signalPin = RELAY_PELTIER_PIN;
    peltierRelay.condition.initTemperatureCondition(40,27);

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
    // light.setColor(255,255,255);
    // delay(1000);
    // light.setColor(255,0,255);
    // delay(1000);
    unsigned long currentMillis = millis();

    if (currentMillis - lastCheckTime >= checkInterval){
        
        // Thu thập dữ liệu từ các cảm biến và relay
        String jsonData = collectData();
        // Gửi dữ liệu đã thu thập được qua Serial
        sendDataOverSerial(&jsonData);

        lastCheckTime = currentMillis;
    }
    
}

