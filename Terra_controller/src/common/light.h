#ifndef LIGHT_H
#define LIGHT_H

/*!
 * @struct Light
 * @brief Represents a light control interface for an RGB LED.
 *
 * This `struct` provides methods to control the color and state of an RGB LED.
 */
struct Light
{
    /*!
     * @brief Holds the current intensity of the red, green, and blue channels.
     *
     * These values represent the current color state of the LED.
     */
    int red;    /*!< Current red intensity (0-255) */
    int green;  /*!< Current green intensity (0-255) */
    int blue;   /*!< Current blue intensity (0-255) */

    /*!
     * @brief Constructor to initialize the light with the LED off.
     */
    Light() : red(0), green(0), blue(0) {}

    /*!
     * @brief Sets the color of an RGB LED.
     *
     * This function controls the color of an RGB LED by setting the intensity of the red, green, and blue channels.
     *
     * @param redIntensity The intensity of the red channel (0-255).
     * @param greenIntensity The intensity of the green channel (0-255).
     * @param blueIntensity The intensity of the blue channel (0-255).
     *
     * @return void
     * The function does not return any values.
     */
    void setColor(int redIntensity, int greenIntensity, int blueIntensity);

    /*!
     * @brief Turns off the LED without cutting off the power.
     *
     * This function turns off the LED light while keeping the power supplied, allowing for a quick restart.
     *
     * @return void
     * The function does not return any values.
     */
    void turnOff();
};

#endif // LIGHT_H
