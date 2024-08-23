#ifndef SOIL_MOISTURE_H
#define SOIL_MOISTURE_H

/*!
 * @struct SoilMoisture
 * @brief Represents a sensor for measuring and displaying soil moisture.
 *
 * This `struct` provides methods to read soil moisture data from a sensor and display
 * the current moisture level.
 */
struct SoilMoisture
{
    float moisture; ///< The current soil moisture reading from the sensor.

    /*!
     * @brief Reads data from the soil moisture sensor.
     *
     * This function reads the soil moisture level from the sensor and updates the 
     * `moisture` member variable with the current reading.
     *
     * @return void
     * The function does not return a value.
     */
    void readSoilMoisture();

    /*!
     * @brief Prints the soil moisture value.
     *
     * This function displays the current soil moisture reading on the console or a 
     * connected display.
     *
     * @return void
     * The function does not return a value.
     */
    void displaySoilMoisture();
};

#endif // SOIL_MOISTURE_H