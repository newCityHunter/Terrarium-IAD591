#include "connection.h"

#include <map>
#include "strings.h"

// config mqtt
const char *mqtt_server = RABBIT_SERVER;
const char *mqtt_username = RABBIT_USERNAME;
const char *mqtt_password = RABBIT_PASSWORD;
const int mqtt_port = RABBIT_PORT;
const int mqtt_buffer_size = RABBIT_BUFFER_SIZE;

// Topic to send messages
const String exchange_send = "gateway.";
const String device_name = "device_name";

unsigned int correlationIndex;
char *deviceID;
String correlationIds[CORRELATION_ID_MAX_SIZE];

// Topic to receive from server
const String exchange_received = "server.*";

std::map<std::string, int> methodMap = {{"PostDevice", 1}};

void setupMqtt()
{
    client.setServer(mqtt_server, mqtt_port);
    client.setBufferSize(mqtt_buffer_size);
    client.setCallback(callback);

    while (!client.connected())
    {
        String client_id = "esp32-client-";
        Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
        if (client.connect(getDeviceName().c_str(), mqtt_username, mqtt_password))
        {
            Serial.println("Connected to RabbitMQ");
        }
        else
        {
            Serial.printf("Connection failed, rc= %d\n", client.state());
            delay(2000);
        }
    }
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.println("-----------------------");
    Serial.printf("Message arrived in topic: %s\n", topic);
    Serial.print("Message: ");
    String receiveMessage = "";
    for (int i = 0; i < length; i++)
    {
        receiveMessage.concat((char)payload[i]);
    }
    Serial.println(receiveMessage);
    handleMessageReceived(topic, receiveMessage.c_str());
}

String getSendTopic(String functionName)
{
    return exchange_send + device_name + functionName;
}

String getReceiveTopic()
{
    return exchange_received;
}

String getDeviceName()
{
    return device_name;
}

String getResponseMethod(String response)
{
    return strtok((char *)response.c_str(), "-");
}

void handleMessageReceived(String topic, const char *receiveMessage)
{
    Serial.printf("Handle message with topic is %s\n", topic.c_str());
    if ((String)topic == "server/+")
    {
        String responseMethod;
        for (String correlationId : correlationIds)
        {
            String currCorrelation = strtok((char *)correlationId.c_str(), "-");
            String topicService = strtok((char *)correlationId.c_str(), "/");
            Serial.printf("Response is %s\n", currCorrelation.c_str());
            Serial.printf("Response is %s\n", topicService.c_str());

            if (currCorrelation == topicService)
            {
                Serial.println("OK");
                responseMethod = currCorrelation;
                removeMatchedCorrelationId(correlationId);
                break;
            }
        }
        // check response from server with my correlationId correctly
        // Serial.printf("Response is %s\n", correlationId);

        Serial.printf("Response is %s\n", responseMethod.c_str());
        if (methodMap.find(responseMethod.c_str()) != methodMap.end())
        {
            int command = methodMap[responseMethod.c_str()];
            switch (command)
            {
            case 1:
                Serial.println("Handle POST device");
                if (deviceID == nullptr)
                {
                    jparse_ctx_t jctx;
                    // 37 is size of uuid
                    char id[37 + 1];

                    Serial.printf("receiveMessage: %s \n", receiveMessage);
                    int ret = json_parse_start(&jctx, receiveMessage, strlen(receiveMessage));
                    if (ret != OS_SUCCESS)
                    {
                        Serial.println("Body is not json");
                        return;
                    }
                    if (json_obj_get_object(&jctx, "data") == OS_SUCCESS)
                    {
                        if (json_obj_get_string(&jctx, "Id", id, sizeof(id)) == OS_SUCCESS)
                        {
                            deviceID = id;
                            Serial.printf("ID is: %s \n", deviceID);
                        }
                    }
                    json_parse_end(&jctx);
                }
                break;
            }
        }
        else
        {
            // Send to Nano
            Serial2.print(receiveMessage);
        }
    }
}

String generateCorrelation(String prefix)
{
    if (correlationIndex >= CORRELATION_ID_MAX_SIZE)
    {
        delay(1000);
        return "";
    }
    String correlationId = "";
    UUID uuid;

    uuid.setVariant4Mode();
    uuid.generate();

    correlationId += prefix;
    correlationId += "-";
    correlationId += uuid.toCharArray();
    correlationIds[correlationIndex++] = correlationId;

    return correlationId;
}

void removeMatchedCorrelationId(String correlationId)
{
    int isFounded = 0;
    for (int i = 0; i <= correlationIndex; i++)
    {
        if (strcmp(correlationId.c_str(), correlationIds[i].c_str()) == 0)
        {
            isFounded = 1;
        }

        if (isFounded)
        {
            if (i == correlationIndex && correlationIndex == CORRELATION_ID_MAX_SIZE - 1)
            {
                correlationIds[i] = "";
            }
            else
            {
                correlationIds[i] = correlationIds[i + 1];
            }
        }
    }
    --correlationIndex;
}

char *getDeviceID()
{
    return deviceID;
}
