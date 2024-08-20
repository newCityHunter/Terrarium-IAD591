#ifndef HEAT_HUMID
#define HEAT_HUMID
struct HeatHumid
{
    float temperature;
    float humidity;

    /*
     * Function: readHeatHumid
     * -----------------------
     * Reads data from a DHT sensor (temperature and humidity).
     *
     * bool dht11: Specifies the type of DHT sensor being used.
     *       true for DHT11, false for DHT22
     *
     * returns: The function does not return an values (void).
     *          The temperature and humidity data are
     *          stored in global variables.
     */
    void readHeatHumid(bool dht11);

    /*
     * Function: displayHeatHumid
     * --------------------------
     * Print temperature and humidity
     *
     * returns: The function does not return any values (void)
     */
    void displayHeatHumid();
};

#endif // HEAT_HUMID
