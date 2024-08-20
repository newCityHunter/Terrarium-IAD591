#include "sensor/heat_humid.h"
#include "DHT.h"

#define DHTPIN 2
DHT dht(DHTPIN, DHT11);

void HeatHumid::readHeatHumid(bool dht11)
{
    if(dht11 == false)
        dht = DHT(DHTPIN,DHT22);
    
    dht.begin();
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        // Handle the error: set default values, report error, etc.
        Serial.write("Failed to read from DHT sensor!\n");
        temperature = 0.0;
        humidity = 0.0;
    }
}

void HeatHumid::displayHeatHumid()
{
    Serial.write("Tempurature: %f*C\n",temperature);
    Serial.write("Humidity: %f%\n",humidity);
}