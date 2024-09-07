#include <PubSubClient.h>
#include <Wire.h>
#include <json_parser.h>
#include <UUID.h>
#include <WiFi.h>
#include <string.h>

extern PubSubClient client;

void setupMqtt();
void callback(char *topic, byte *payload, unsigned int length);
void pushMsgMQTT(char *routingKey, char *body);
String getReceiveTopic();
String getSendTopic(String functionName);
String getDeviceName();
void handleMessageReceived(String topic, const char *receiveMessage);

String generateCorrelation(String prefix);
void removeMatchedCorrelationId(String correlationId);
char *getDeviceID();
