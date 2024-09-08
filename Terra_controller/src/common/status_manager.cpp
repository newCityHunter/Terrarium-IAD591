#include "status_manager.h"
#include "common/config.h"
#include "./sensor/heat_humid.h"
#include "./sensor/soil_moisture.h"
#include "./sensor/water_detection.h"
#include "./relay.h"
#include "./light.h"

void sendDataOverSerial(String jsonData)
{
    Serial.println(jsonData);
}

void setupRelay()
{
    pumpRelay.setRelayName("Pump");

    pumpRelay.signalPin = RELAY_PUMP_PIN;
    pumpRelay.condition.initMoistureCondition(0.7, 0.15);
    pumpRelay.setSensor(heatHumid);

    valveRelay.setRelayName("Valve");
    valveRelay.signalPin = RELAY_VALVE_PIN;
    valveRelay.condition.initMoistureCondition(0.7, 0.15);
    pumpRelay.setSensor(soilMoisture);

    lightRelay.setRelayName("Light");
    lightRelay.signalPin = RELAY_LIGHT_PIN;
    lightRelay.condition.initTimeBasedCondition(14400, 18000); // 4 tiếng từ 5h sáng

    peltierRelay.setRelayName("Peltier");
    peltierRelay.signalPin = RELAY_PELTIER_PIN;
    peltierRelay.condition.initTemperatureCondition(40, 27);
}

// Hàm thu thập dữ liệu từ các cảm biến và relay
String collectData()
{
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
    pumpData["sensor_name"] = pumpRelay.relayName;
    pumpData["sensor_type"] = "Pump";
    dataArray.add(pumpData);

    // Dữ liệu từ Relay của van
    StaticJsonDocument<200> valveData;
    valveData["data"]["isActive"] = digitalRead(valveRelay.state);
    valveData["sensor_name"] = valveRelay.relayName;
    valveData["sensor_type"] = "Valve";
    dataArray.add(valveData);

    // Dữ liệu từ Relay của hệ thống làm mát (Cooler)
    StaticJsonDocument<200> coolerData;
    coolerData["data"]["isActive"] = peltierRelay.state;
    coolerData["sensor_name"] = peltierRelay.relayName;
    coolerData["sensor_type"] = "Cooler";
    dataArray.add(coolerData);

    // Dữ liệu từ Relay của đèn
    StaticJsonDocument<200> lightRelayData;
    lightRelayData["data"]["isActive"] = lightRelay.state;
    lightRelayData["sensor_name"] = lightRelay.relayName;
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

void handleRequest(String request)
{
    StaticJsonDocument<1024> doc;
    DeserializationError err = deserializeJson(doc, request);
    if (err.code() == DeserializationError::Ok)
    {
        JsonObject root = doc.as<JsonObject>();
        for (JsonPair kv : root)
        {
            if (kv.key() == "Pump")
            {
                JsonObject childObj = kv.value().as<JsonObject>();
                bool isActive = childObj["isActive"];
                if (isActive)
                {
                    digitalWrite(RELAY_PUMP_PIN, HIGH);
                }
                else
                {
                    digitalWrite(RELAY_PUMP_PIN, LOW);
                }
            }
            if (kv.key() == "Valve")
            {
                JsonObject childObj = kv.value().as<JsonObject>();
                bool isActive = childObj["isActive"];
                if (isActive)
                {
                    digitalWrite(RELAY_VALVE_PIN, HIGH);
                }
                else
                {
                    digitalWrite(RELAY_VALVE_PIN, LOW);
                }
            }
            if (kv.key() == "Light")
            {
                Light light;
                JsonObject childObj = kv.value().as<JsonObject>();
                bool isActive = childObj["isActive"];
                if (isActive)
                {
                    light.turnOff();
                }
                else
                {
                    const char *colorStr = childObj["Color"];
                    char *token = strtok((char *)colorStr, ",");
                    light.setColor(token[0], token[1], token[2]);
                    free((char *)colorStr);
                    free(token);
                }
            }
            if (kv.key() == "DHT")
            {
                JsonObject childObj = kv.value().as<JsonObject>();
                JsonObject thresholds = childObj["Thresholds"].as<JsonObject>();
                if (thresholds.isNull())
                {
                    break;
                }
                JsonObject aboveTemp = thresholds["Temperature"].as<JsonObject>();
                float tempValAbove;
                float tempValBelow;
                if (!aboveTemp.isNull())
                {
                    tempValAbove = aboveTemp["above"];
                }
                JsonObject belowTemp = thresholds["Temperature"].as<JsonObject>();
                if (!belowTemp.isNull())
                {
                    tempValBelow = aboveTemp["below"];
                }

                peltierRelay.condition.updateTemperatureThreshold(tempValAbove, tempValBelow);

                JsonObject moisture = childObj["Moisture"].as<JsonObject>();

                if (!moisture.isNull())
                {
                    JsonObject thresholdsMoisture = childObj["Thresholds"].as<JsonObject>();
                    if (!thresholdsMoisture.isNull())
                    {
                        float moistureAbove = thresholdsMoisture["above"];
                        float moistureBelow = thresholdsMoisture["below"];
                        valveRelay.condition.updateMoistureThreshold(moistureAbove, moistureBelow);
                        pumpRelay.condition.updateMoistureThreshold(moistureAbove, moistureBelow);
                    }
                }
            }
        }
    }
}