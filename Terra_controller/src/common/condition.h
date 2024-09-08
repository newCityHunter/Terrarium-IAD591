#ifndef CONDITION_H
#define CONDITION_H

enum ConditionType {
    HUMIDITY,
    TEMPERATURE,
    WATER,
    TIME_BASED
};

/*!
 * @struct Condition
 * @brief Represents a condition interface to control a relay.
 *
 * Each condition has specific thresholds depending on its type:
 * - HUMIDITY: Uses humidThreshold for control.
 * - TEMPERATURE: Uses temperatureThreshold for control.
 * - WATER: Uses moistureThreshold for control.
 * - TIME_BASED: Uses duration and startTime.
 */
typedef struct {
    ConditionType type;
    float humidThreshold[2];        // Ngưỡng độ ẩm (0: bật, 1: tắt)
    float temperatureThreshold[2];  // Ngưỡng nhiệt độ (0: bật, 1: tắt)
    float moistureThreshold[2];     // Ngưỡng độ ẩm đất (0: bật, 1: tắt)
    unsigned long duration;                   // Thời gian (tính bằng phút)
    unsigned long startTime;                  // Thời gian bắt đầu theo định dạng HHMM

    void initHumidityCondition(float upper, float lower);
    // Khởi tạo cấu trúc Condition cho điều kiện nhiệt độ
    void initTemperatureCondition(float upper, float lower);

    // Khởi tạo cấu trúc Condition cho điều kiện độ ẩm đất
    void initMoistureCondition(float upper, float lower);

    // Khởi tạo cấu trúc Condition cho điều kiện dựa trên thời gian
    void initTimeBasedCondition(int duration, int startTime);

    // Kiểm tra điều kiện có thỏa mãn hay không
    int isConditionMet(float currentHumidity, float currentTemperature, float currentMoisture, int currentTime);

    // Cập nhật ngưỡng độ ẩm
    void updateHumidityThreshold(float upper, float lower);

    // Cập nhật ngưỡng nhiệt độ
    void updateTemperatureThreshold(float upper, float lower);

    // Cập nhật ngưỡng độ ẩm đất
    void updateMoistureThreshold(float upper, float lower);

    // Cập nhật thời gian cho điều kiện dựa trên thời gian
    void updateTimeCondition(int duration, int startTime);
} Condition;



#endif // CONDITION_H
