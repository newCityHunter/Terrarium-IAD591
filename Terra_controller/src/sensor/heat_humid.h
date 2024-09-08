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

    /**
     * @brief Initializes the DHT sensor with the specified type.
     *
     * This function sets up the DHT sensor by initializing it with the
     * appropriate type based on the `dht11` parameter. It should be called
     * once at the beginning to prepare the sensor for reading temperature and
     * humidity data.
     *
     * @param dht11 Specifies the type of DHT sensor being used.
     *              - `true` if using a DHT11 sensor.
     *              - `false` if using a DHT22 sensor.
     *
     * This function initializes the sensor and sets the pin and type
     * accordingly. The `begin` function should be called before attempting to
     * read data from the sensor.
     *
     * @return void
     * The function does not return a value.
     */
    void begin(bool dht11);

    /*!
     * @brief Reads data from a DHT sensor (temperature and humidity).
     *
     * This function reads temperature and humidity data from a DHT sensor and
     * updates the `temperature` and `humidity` member variables.
     *
     * @return void
     * The function does not return a value.
     */
    void readHeatHumid();

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