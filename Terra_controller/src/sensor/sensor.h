#ifndef SENSOR_H
#define SENSOR_H

struct Sensor
{
    float temperature; ///< The current temperature reading from the sensor.
    float humidity;    ///< The current humidity reading from the sensor.

    float moisture; ///< The current soil moisture reading from the sensor.

    bool waterDetected; ///< The current water detection status from the sensor.

    int sensorPin;           ///< The pin connected to the water flow sensor signal.
    float calibrationFactor; ///< Calibration factor to convert pulse count to flow rate (pulses per liter).
    volatile int pulseCount; ///< The number of pulses counted by the sensor.
    bool isAvailable;        ///< Flag indicating whether water is flowing (true) or not (false).
};

#endif