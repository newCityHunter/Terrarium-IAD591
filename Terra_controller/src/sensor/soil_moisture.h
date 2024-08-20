#ifndef SOIL_MOISTURE_H
#define SOIL_MOISTURE_H

struct SoilMoisture
{
    float moisture;

    /*
     * Function: readSoilMoisture
     * --------------------------
     * Read data from soil moisture sensor
     *
     * Return: This function does not return any values (void)
     *         The soil moisture data is stored in global value
     */
    void readSoilMoisture();

    /*
     * Function: displayHeatHumid
     * --------------------------
     * Print soil moisture value
     *
     * returns: The function does not return any values (void)
     */
    void displaySoilMoisture();
};

#endif // SOIL_MOISTURE_H
