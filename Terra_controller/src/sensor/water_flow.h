#include "sensor.h"
#ifndef WaterFlow_H
#define WaterFlow_H

/*!
 * @struct WaterFlow
 * @brief Represents a water flow sensor for measuring liquid flow rates.
 *
 * This `struct` provides methods to initialize the sensor, measure the water flow rate,
 * and check if water is currently flowing through the sensor. It stores relevant
 * sensor data, such as the pulse count and total water volume.
 */
struct WaterFlow : public Sensor
{
    /*!
     * @brief Initializes the water flow sensor.
     *
     * This function sets the pin mode for the sensor, resets the pulse count,
     * and attaches an interrupt to handle incoming pulses from the sensor.
     *
     * @return void
     * The function does not return a value.
     */
    void begin();

    /*!
     * @brief Checks if water is flowing through the sensor.
     *
     * This function checks the pulse count to determine if water is flowing.
     * If the pulse count is greater than zero, water is flowing and the `isAvailable`
     * flag is set to true.
     *
     * @return bool
     * Returns true if water is flowing, false otherwise.
     */
    bool isWaterAvailable();
};

#endif // WaterFlow_H