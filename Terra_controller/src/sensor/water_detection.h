#ifndef WATER_DETECTION_H
#define WATER_DETECTION_H

class WaterDetection {
public:
    // Constructor
    WaterDetection(int pin);

    // Destructor
    ~WaterDetection();

    // Method to read data from the sensor
    bool isWaterDetected();

private:
    int sensorPin; // Pin connected to the water detection sensor
};

#endif // WATER_DETECTION_H
