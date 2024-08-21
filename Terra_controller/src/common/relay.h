#ifndef RELAY_H
#define RELAY_H

struct Relay
{
    char relayName[10];
    int signalPin;

    /*
     * Function: closeRelay
     * --------------------
     * Close circuit and activate actuator
     *
     * Return: This function does not return any values (void)
     */
    void closeRelay();

    /*
     * Function: closeRelay
     * --------------------
     * Open circuit and deactivate actuator
     *
     * Return: This function does not return any values (void)
     */
    void openRelay();
};

#endif // RELAY_H