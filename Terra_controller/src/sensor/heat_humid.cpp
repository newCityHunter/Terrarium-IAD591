#include "DHT.h"
#include "common/config.h"
#include "sensor/heat_humid.h"

DHT dht(DHT_SENSOR_PIN, DHT11);

void HeatHumid::readHeatHumid(bool dht11)
{
    if(dht11 == false)
        dht = DHT(DHT_SENSOR_PIN,DHT22);
    
    dht.begin();
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    
    // Handle the error: set default values, report error.
    if (isnan(temperature) || isnan(humidity)) {
        Serial.write("Failed to read from DHT sensor!\n");
        temperature = 0.0;
        humidity = 0.0;
    }
    else
        displayHeatHumid();
}

void HeatHumid::displayHeatHumid()
{
    Serial.write("Tempurature: %f*C\n",temperature);
    Serial.write("Humidity: %f%\n",humidity);
}