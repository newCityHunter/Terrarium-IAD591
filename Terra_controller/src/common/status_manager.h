#ifndef STATUS_MANAGER_H
#define STATUS_MANAGER_H

#include <Arduino.h>
#include <ArduinoJson.h>

class StatusManager {
public:
    // Constructor
    StatusManager();
    
    // Thu thập dữ liệu từ các cảm biến và relay
    String collectData();
    
    // Gửi dữ liệu JSON qua Serial
    void sendDataOverSerial(const String& jsonData);

private:
    // Đọc dữ liệu từ cảm biến nhiệt độ và độ ẩm
    float readTemperature();
    float readHumidity();
    
    // Đọc dữ liệu từ cảm biến độ ẩm đất
    int readSoilMoisture();
    
    // Kiểm tra trạng thái phát hiện nước
    bool readWaterDetection();

    // Kiểm tra trạng thái relay
    bool readRelayStatus(int relayPin);
    
    // Đọc giá trị màu sắc từ đèn LED RGB
    void readLightColor(int &red, int &green, int &blue);
};

#endif // STATUS_MANAGER_H
