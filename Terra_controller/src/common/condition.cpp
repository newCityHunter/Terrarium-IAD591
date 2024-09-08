#include "condition.h"

// Khởi tạo điều kiện độ ẩm
void Condition:: initHumidityCondition(float upper, float lower) {
    type = HUMIDITY;
    humidThreshold[0] = upper;
    humidThreshold[1] = lower;
}

// Khởi tạo điều kiện nhiệt độ
void Condition:: initTemperatureCondition(float upper, float lower) {
    type = TEMPERATURE;
    temperatureThreshold[0] = upper;
    temperatureThreshold[1] = lower;
}

// Khởi tạo điều kiện độ ẩm đất
void Condition:: initMoistureCondition(float upper, float lower) {
    type = WATER;
    moistureThreshold[0] = upper;
    moistureThreshold[1] = lower;
}

// Khởi tạo điều kiện dựa trên thời gian
void Condition:: initTimeBasedCondition(int duration, int startTime) {
    type = TIME_BASED;
    duration = duration;
    startTime = startTime;
}


// Cập nhật ngưỡng độ ẩm
void Condition:: updateHumidityThreshold(float upper, float lower) {
    humidThreshold[0] = upper;
    humidThreshold[1] = lower;
}

// Cập nhật ngưỡng nhiệt độ
void Condition:: updateTemperatureThreshold(float upper, float lower) {
    temperatureThreshold[0] = upper;
    temperatureThreshold[1] = lower;
}

// Cập nhật ngưỡng độ ẩm đất
void Condition:: updateMoistureThreshold(float upper, float lower) {
    moistureThreshold[0] = upper;
    moistureThreshold[1] = lower;
}


