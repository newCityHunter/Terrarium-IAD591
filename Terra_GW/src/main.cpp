#include <Arduino.h>
#include "wifiConnection.h"
#include "connection.h"

const unsigned long interval = 10000; // 10 seconds (in milliseconds)
unsigned long previousMillis = 0;
unsigned long currentMillis;

const String postDevice = ".PostDevice";
const String putPerformance = ".PutDetailPerformance";

WiFiClientSecure espClient;
PubSubClient client(espClient); // Declare the PubSubClient instance
// config RX and TX serial
#define RXp2 16
#define TXp2 17

UUID uuid;

void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  setupWifi();
  setupMqtt();
  client.subscribe(getReceiveTopic().c_str());
  delay(2000);
  // Call postDeviceApi to get id
  String correlationId = generateCorrelation("PostDevice");
  String macS = WiFi.macAddress();
  String bodyFormat = "{\"header\": {\"Correlation-Id\": \"%s\"}, \"body\": {\"name\": \"%s\", \"type\": \"%s\", \"status\": \"%s\", \"firmware_ver\": %d, \"app_ver\": %d}}";

  // Get Length
  int length = snprintf(NULL, 0, bodyFormat.c_str(),
                        correlationId.c_str(), macS.c_str(), "Common", "Active", 1, 1);

  char *postPayload = (char *)malloc(length + 1);
  snprintf(postPayload, length + 1, bodyFormat.c_str(),
           correlationId.c_str(), macS.c_str(), "Common", "Active", 1, 1);
  Serial.print(postPayload);
  client.publish(
      getSendTopic(postDevice).c_str(),
      postPayload);
  free(postPayload);
}

void loop()
{
  currentMillis = millis();

  // Call api after 10 seconds
  if (currentMillis - previousMillis > interval)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      // Send message with device id and status
      String dataToRequest = Serial2.readString();
      if (dataToRequest != "")
      {
        Serial.printf("Message receive: %s \n", dataToRequest.c_str());

        String correlationId = generateCorrelation("PutDetailPerformance");

        String bodyFormat = "{\"header\": {\"Correlation-Id\": \"%s\"}, { \"param\": { \"deviceId\": \"%s\" }, \"body\": { \"document_name\": \"%s\",   \"payload\": %s }\n}";
        // Get Length
        int length = snprintf(NULL, 0, bodyFormat.c_str(), correlationId.c_str(), getDeviceID(),
                              WiFi.macAddress(), dataToRequest);
        char *payload = (char *)malloc(length + 1);
        snprintf(payload, length, bodyFormat.c_str(), correlationId.c_str(), getDeviceID(),
                 WiFi.macAddress(), dataToRequest);
        client.publish(
            getSendTopic(putPerformance).c_str(), payload);
        free(payload);
      }

      previousMillis = currentMillis;
    }
  }
  client.loop();
}
