#include <Arduino.h>
#include <ArduinoJson.h>

#include "common/config.h"
#include "common/relay.h"
#include "common/status_manager.h"
#include "sensor/heat_humid.h"
#include "sensor/soil_moisture.h"
#include "sensor/water_detection.h"
#include "common/light.h"

unsigned long previousMillis = 0;
const long waitWater = 60000; // 1 phút
bool pumpActive = false;
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

// Tạo một đối tượng của lớp StatusManager
StatusManager statusManager;

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

    // Khởi tạo pin sensor kiểm tra nước
    waterDetection = WaterDetection(WATER_DETECTION_PIN);

    
}

void loop()
{
    // light.setColor(255,255,255);
    // delay(1000);
    // light.setColor(255,0,255);
    // delay(1000);
    unsigned long currentMillis = millis();

    if (pumpActive) {
        if (previousMillis == 0)
        {   
            previousMillis = millis();
        }
        if (currentMillis - previousMillis >= waitWater) {
            if (!waterDetection.isWaterDetected()) {
                pumpRelay.openRelay(); // Tắt máy bơm nếu không có nước
                pumpActive = false; // Cập nhật trạng thái máy bơm
            }
            previousMillis = 0; // Reset lại thời gian chờ
        }
    } 

    if (currentMillis - lastCheckTime >= checkInterval){
        
        // Thu thập dữ liệu từ các cảm biến và relay
        String jsonData = statusManager.collectData();
        // Gửi dữ liệu đã thu thập được qua Serial
        statusManager.sendDataOverSerial(jsonData);

        lastCheckTime = currentMillis;
    }
    
}

