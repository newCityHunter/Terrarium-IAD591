#include "config.h"
#include "common/light.h"

void Light::setColor(int redIntensity, int greenIntensity, int blueIntensity)
{
    // Lưu lại trạng thái màu sắc hiện tại
    red = redIntensity;
    green = greenIntensity;
    blue = blueIntensity;

    // Điều khiển LED
    analogWrite(LED_RED_PIN, redIntensity);
    analogWrite(LED_GREEN_PIN, greenIntensity);
    analogWrite(LED_BLUE_PIN, blueIntensity);
}

void Light::turnOff()
{
    // Lưu trạng thái tắt (0)
    red = 0;
    green = 0;
    blue = 0;

    // Tắt LED
    analogWrite(LED_RED_PIN, 0);
    analogWrite(LED_GREEN_PIN, 0);
    analogWrite(LED_BLUE_PIN, 0);
}
