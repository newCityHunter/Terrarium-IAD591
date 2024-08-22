#ifndef HEAT_HUMID_H
#define HEAT_HUMID_H

/*!
 * @struct HeatHumid
 * @brief Represents a sensor for reading and displaying temperature and humidity.
 *
 * This `struct` provides methods to read data from a DHT sensor and display
 * the current temperature and humidity readings.
 */
struct HeatHumid
{
    float temperature; ///< The current temperature reading from the sensor.
    float humidity;    ///< The current humidity reading from the sensor.

    /*!
     * @brief Reads data from a DHT sensor (temperature and humidity).
     *
     * This function reads temperature and humidity data from a DHT sensor and
     * updates the `temperature` and `humidity` member variables.
     *
     * @param dht11 Specifies the type of DHT sensor being used.
     *              `true` for DHT11, `false` for DHT22.
     *
     * @return void
     * The function does not return a value.
     */
    void readHeatHumid(bool dht11);

    /*!
     * @brief Prints temperature and humidity values.
     *
     * This function displays the current temperature and humidity readings on
     * the console or a connected display.
     *
     * @return void
     * The function does not return a value.
     */
    void displayHeatHumid();
};

#endif // HEAT_HUMID_H