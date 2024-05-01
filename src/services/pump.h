#ifndef PUMP
#define PUMP
#include <Arduino.h>

/**
 * @brief water pump relay control pin
 * D0-D28 which equates to GP0-GP28.
 */
#define PUMP_RELAY_PIN D16

/**
 * @brief duration in milliseconds for the pump relay
 *        to stay activated
 */
#define PUMP_RELAY_DURATION_MILLIS 250

class Pump
{
public:
    // methods
    static void setup();
    static void loop();
    static void toggle();
    static void checkToggle();

    // props
    static unsigned long toggleTime;
    static bool isToggleActive;
};

#endif // PUMP