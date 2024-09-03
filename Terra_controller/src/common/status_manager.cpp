#include "status_manager.h"
#include "common/config.h"
#include <DHT.h>

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHT_SENSOR_PIN, DHTTYPE);

StatusManager::StatusManager() {
    dht.begin();
    pinMode(SOIL_MOISTURE_PIN, INPUT);
    pinMode(WATER_DETECTION_PIN, INPUT);

    // Pin relay mode setup
    pinMode(RELAY_PUMP_PIN, OUTPUT);
    pinMode(RELAY_VALVE_PIN, OUTPUT);
    pinMode(RELAY_LIGHT_PIN, OUTPUT);
    pinMode(RELAY_PELTIER_PIN, OUTPUT);

    // Pin RGB LED setup
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_BLUE_PIN, OUTPUT);
}

float StatusManager::readTemperature() {
    return dht.readTemperature();
}

float StatusManager::readHumidity() {
    return dht.readHumidity();
}

int StatusManager::readSoilMoisture() {
    return analogRead(SOIL_MOISTURE_PIN);
}

bool StatusManager::readWaterDetection() {
    return digitalRead(WATER_DETECTION_PIN) == HIGH;
}

bool StatusManager::readRelayStatus(int relayPin) {
    return digitalRead(relayPin) == HIGH;
}

void StatusManager::readLightColor(int &red, int &green, int &blue) {
    red = analogRead(LED_RED_PIN);
    green = analogRead(LED_GREEN_PIN);
    blue = analogRead(LED_BLUE_PIN);
}

void sendDataOverSerial(const String& jsonData) {
    Serial.println(jsonData); // Gửi dữ liệu JSON qua Serial
}

String StatusManager::collectData() {
    StaticJsonDocument<1024> doc;

    // Tạo mảng JSON để chứa dữ liệu của tất cả các thiết bị và cảm biến
    JsonArray dataArray = doc.to<JsonArray>();

    // Dữ liệu từ cảm biến DHT
    StaticJsonDocument<200> dhtData;
    dhtData["data"]["Value"]["temp"] = readTemperature();
    dhtData["data"]["Value"]["humid"] = readHumidity();
    dhtData["sensor_name"] = "dht";
    dhtData["sensor_type"] = "DHT";
    dhtData["timestamp"]["$date"]["$numberLong"] = String(millis());
    dataArray.add(dhtData);

    // Dữ liệu từ Pump Relay
    StaticJsonDocument<200> pumpData;
    pumpData["data"]["isActive"] = readRelayStatus(RELAY_PUMP_PIN);
    pumpData["sensor_name"] = "pumpRelay";
    pumpData["sensor_type"] = "Pump";
    pumpData["timestamp"]["$date"]["$numberLong"] = String(millis());
    dataArray.add(pumpData);

    // Dữ liệu từ Valve Relay
    StaticJsonDocument<200> valveData;
    valveData["data"]["isActive"] = readRelayStatus(RELAY_VALVE_PIN);
    valveData["sensor_name"] = "valveRelay";
    valveData["sensor_type"] = "Valve";
    valveData["timestamp"]["$date"]["$numberLong"] = String(millis());
    dataArray.add(valveData);

    // Dữ liệu từ Cooler Relay
    StaticJsonDocument<200> coolerData;
    coolerData["data"]["isActive"] = readRelayStatus(RELAY_PELTIER_PIN);
    coolerData["sensor_name"] = "coolerRelay";
    coolerData["sensor_type"] = "Cooler";
    coolerData["timestamp"]["$date"]["$numberLong"] = String(millis());
    dataArray.add(coolerData);

    // Dữ liệu từ Light
    StaticJsonDocument<200> lightData;
    int red, green, blue;
    readLightColor(red, green, blue);
    lightData["data"]["isActive"] = readRelayStatus(RELAY_LIGHT_PIN);
    lightData["data"]["Color"][0] = red;
    lightData["data"]["Color"][1] = green;
    lightData["data"]["Color"][2] = blue;
    lightData["sensor_name"] = "Light";
    lightData["sensor_type"] = "Light";
    lightData["timestamp"]["$date"]["$numberLong"] = String(millis());
    dataArray.add(lightData);

    // Dữ liệu từ cảm biến độ ẩm đất (Soil Moisture)
    StaticJsonDocument<200> moistureData;
    moistureData["data"]["Moisture"] = readSoilMoisture();
    moistureData["sensor_name"] = "Moisture";
    moistureData["sensor_type"] = "Moisture";
    moistureData["timestamp"]["$date"]["$numberLong"] = String(millis());
    dataArray.add(moistureData);

    // Dữ liệu từ cảm biến phát hiện nước (Water Detection)
    StaticJsonDocument<200> waterData;
    waterData["data"]["isAvailable"] = readWaterDetection();
    waterData["sensor_name"] = "Water";
    waterData["sensor_type"] = "Water";
    waterData["timestamp"]["$date"]["$numberLong"] = String(millis());
    dataArray.add(waterData);

    // Chuyển đổi đối tượng JSON thành string
    String jsonString;
    serializeJson(doc, jsonString);

    // Trả về chuỗi JSON
    return jsonString;
}
