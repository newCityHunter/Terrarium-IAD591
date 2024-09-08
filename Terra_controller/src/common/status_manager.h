#ifndef STATUS_MANAGER_H
#define STATUS_MANAGER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "./sensor/heat_humid.h"
#include "./sensor/soil_moisture.h"
#include "./sensor/water_detection.h"
#include "./relay.h"
#include "./light.h"

/*!
 * @struct StatusManager
 * @brief Manages the collection and transmission of sensor data and control variables.
 *
 * The `StatusManager` struct is responsible for collecting data from various sensors
 * and relays, sending the data as JSON over Serial, and managing control variables
 * like temperature and humidity thresholds.
 */
typedef struct {

} StatusManager;


/*!
 * @brief Collects data from the provided sensors and relays.
 *
 * This function collects data from various sensors (temperature, humidity, soil moisture, etc.)
 * and relays (pump, valve, cooler, light), and compiles the data into a JSON object.
 *
\
 * @return A JSON string containing the collected sensor and relay data.
 */
String collectData();

/*!
 * @brief Sends data over Serial.
 *
 * This function sends the provided JSON string over Serial for communication.
 *
 * @param jsonData A pointer to the JSON string to be sent.
 * @return void
 */
void sendDataOverSerial(const String* jsonData);

#endif // STATUS_MANAGER_H
