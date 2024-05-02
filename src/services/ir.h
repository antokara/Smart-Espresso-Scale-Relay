#ifndef IR
#define IR
#include <Arduino.h>

/**
 * @brief Infrared Receiver OUT pin
 * D0-D28 which equates to GP0-GP28.
 */
#define IR_RECEIVE_PIN D16

/**
 * @brief milliseconds to debounce received messages
 *
 */
#define IR_RECEIVE_DEBOUNCE_TIME 3000

class Ir
{
public:
    // methods
    static void setup();
    static void loop();
    static void onReceive(uint8_t address, uint8_t command, bool repeat, bool parityFailed);

    static unsigned long lastReceivedTime;
};

#endif // IR
