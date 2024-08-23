#include "config.h"
#include "common/light.h"

void Light::setColor(int redIntensity, int greenIntensity, int blueIntensity)
{
    analogWrite(LED_RED_PIN,redIntensity);
    analogWrite(LED_GREEN_PIN,greenIntensity);
    analogWrite(LED_BLUE_PIN,blueIntensity);
}

void Light::turnOff()
{
    analogWrite(LED_RED_PIN,0);
    analogWrite(LED_GREEN_PIN,0);
    analogWrite(LED_BLUE_PIN,0);
}