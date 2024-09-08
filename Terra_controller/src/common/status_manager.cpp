#include "status_manager.h"
#include "common/config.h"
#include <ArduinoJson.h>
#include "./sensor/heat_humid.h"
#include "./sensor/soil_moisture.h"
#include "./sensor/water_detection.h"
#include "./relay.h"
#include "./light.h"
#include <Arduino.h>


// Hàm thu thập dữ liệu từ các cảm biến và relay
String collectData() {
    extern Relay pumpRelay;
    extern Relay valveRelay;
    extern Relay lightRelay;
    extern Relay peltierRelay;
    extern HeatHumid heatHumid;
    extern SoilMoisture soilMoisture;
    extern WaterDetection waterDetection;
    extern Light light;

    StaticJsonDocument<1024> doc;

    // Tạo mảng JSON để chứa dữ liệu của tất cả các thiết bị và cảm biến
    JsonArray dataArray = doc.to<JsonArray>();

    // Dữ liệu từ cảm biến nhiệt độ và độ ẩm (DHT)
    StaticJsonDocument<200> dhtData;
    dhtData["data"]["temp"] = heatHumid.temperature;
    dhtData["data"]["humid"] = heatHumid.humidity;
    dhtData["sensor_name"] = "dht";
    dhtData["sensor_type"] = "DHT";
    dataArray.add(dhtData);

    // Dữ liệu từ Relay của máy bơm
    StaticJsonDocument<200> pumpData;
    pumpData["data"]["isActive"] = pumpRelay.state;
    strcpy(pumpData["sensor_name"], pumpRelay.relayName);
    pumpData["sensor_type"] = "Pump";
    dataArray.add(pumpData);

    // Dữ liệu từ Relay của van
    StaticJsonDocument<200> valveData;
    valveData["data"]["isActive"] = digitalRead(valveRelay.state);
    strcpy(valveData["sensor_name"], valveRelay.relayName);
    valveData["sensor_type"] = "Valve";
    dataArray.add(valveData);

    // Dữ liệu từ Relay của hệ thống làm mát (Cooler)
    StaticJsonDocument<200> coolerData;
    coolerData["data"]["isActive"] = peltierRelay.state;
    strcpy(coolerData["sensor_name"], peltierRelay.relayName);
    coolerData["sensor_type"] = "Cooler";
    dataArray.add(coolerData);

    // Dữ liệu từ Relay của đèn
    StaticJsonDocument<200> lightRelayData;
    lightRelayData["data"]["isActive"] = lightRelay.state;
    strcpy(lightRelayData["sensor_name"], lightRelay.relayName);
    lightRelayData["sensor_type"] = "Light";
    // Tạo mảng JSON cho màu sắc
    JsonArray colorArray = lightRelayData["data"].createNestedArray("color");
    colorArray.add(light.red);
    colorArray.add(light.green);
    colorArray.add(light.blue);
    
    dataArray.add(lightRelayData);

    // Dữ liệu từ cảm biến độ ẩm đất (Soil Moisture)
    StaticJsonDocument<200> moistureData;
    moistureData["data"]["Moisture"] = soilMoisture.moisture;
    moistureData["sensor_name"] = "Moisture";
    moistureData["sensor_type"] = "SoilMoisture";
    dataArray.add(moistureData);

    // Chuyển đổi dữ liệu JSON thành chuỗi và trả về
    String output;
    serializeJson(doc, output);
    return output;
}