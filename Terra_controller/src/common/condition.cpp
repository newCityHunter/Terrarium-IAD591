#include "condition.h"

// Khởi tạo điều kiện độ ẩm
void initHumidityCondition(Condition *condition, float upper, float lower) {
    condition->type = HUMIDITY;
    condition->humidThreshold[0] = upper;
    condition->humidThreshold[1] = lower;
}

// Khởi tạo điều kiện nhiệt độ
void initTemperatureCondition(Condition *condition, float upper, float lower) {
    condition->type = TEMPERATURE;
    condition->temperatureThreshold[0] = upper;
    condition->temperatureThreshold[1] = lower;
}

// Khởi tạo điều kiện độ ẩm đất
void initMoistureCondition(Condition *condition, float upper, float lower) {
    condition->type = WATER;
    condition->moistureThreshold[0] = upper;
    condition->moistureThreshold[1] = lower;
}

// Khởi tạo điều kiện dựa trên thời gian
void initTimeBasedCondition(Condition *condition, int duration, int startTime) {
    condition->type = TIME_BASED;
    condition->duration = duration;
    condition->startTime = startTime;
}


// Cập nhật ngưỡng độ ẩm
void updateHumidityThreshold(Condition *condition, float upper, float lower) {
    condition->humidThreshold[0] = upper;
    condition->humidThreshold[1] = lower;
}

// Cập nhật ngưỡng nhiệt độ
void updateTemperatureThreshold(Condition *condition, float upper, float lower) {
    condition->temperatureThreshold[0] = upper;
    condition->temperatureThreshold[1] = lower;
}

// Cập nhật ngưỡng độ ẩm đất
void updateMoistureThreshold(Condition *condition, float upper, float lower) {
    condition->moistureThreshold[0] = upper;
    condition->moistureThreshold[1] = lower;
}


