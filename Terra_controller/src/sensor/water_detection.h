#include "sensor.h"
#ifndef WATER_DETECTION_H
#define WATER_DETECTION_H

/*!
 * @struct WaterDetection
 * @brief Represents a sensor for detecting the presence of water.
 *
 * This `struct` provides methods to read water detection data from a sensor and display
 * the current detection status.
 */
struct WaterDetection : public Sensor
{
    /*!
     * @brief Reads data from the water detection sensor.
     *
     * This function reads the water detection status from the sensor and updates the
     * `waterDetected` member variable with the current status.
     *
     * @return void
     * The function does not return a value.
     */
    void readWaterDetection();

    /*!
     * @brief Prints the water detection status.
     *
     * This function displays the current water detection status on the console.
     *
     * @return void
     * The function does not return a value.
     */
    void displayWaterDetection();
};

#endif // WATER_DETECTION_H
