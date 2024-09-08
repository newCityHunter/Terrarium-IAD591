#ifndef RELAY_H
#define RELAY_H

#include "common/condition.h"
#include "sensor/heat_humid.h"
#include "sensor/soil_moisture.h"
#include "sensor/water_detection.h"

/*!
 * @struct Relay
 * @brief Represents a relay with control and identification functionalities.
 *
 * This `struct` provides methods to set the relay's name and control its state
 * by opening and closing the relay circuit.
 */
union Relay
{
    Sensor sensor;

    bool state;         /// true is ON false is OFF
    char relayName[10]; ///< The name of the relay (null-terminated string with a maximum length of 9 characters).
    int signalPin;      ///< The pin number used to control the relay.
    Condition condition;
    /*!
     * @brief Sets the relay name.
     *
     * This function sets the name of the relay. The name is stored in the
     * `relayName` member variable.
     *
     * @param name A null-terminated character array containing the name of the relay.
     *             The name should be a string with a maximum length of 9 characters.
     *
     * @return void
     * This function does not return a value.
     */
    void setRelayName(const char name[10]);

    /*!
     * @brief Control the relay depending it condition
     *
     * This function control the relay circuit on condition, each relay has it
     * on condition based on condition type
     *
     * @return void
     * This function does not return a value.
     */
    void relayControl();

    /*!
     * @brief Closes the relay and activates the actuator.
     *
     * This function closes the relay circuit, allowing current to flow to the
     * connected actuator.
     *
     * @return void
     * This function does not return a value.
     */
    void closeRelay();

    /*!
     * @brief Opens the relay and deactivates the actuator.
     *
     * This function opens the relay circuit, stopping current flow to the
     * connected actuator.
     *
     * @return void
     * This function does not return a value.
     */
    void openRelay();

    void setSensor(Sensor &s);
};

#endif // RELAY_H