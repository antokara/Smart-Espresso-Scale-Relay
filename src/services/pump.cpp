#include "services/pump.h"
#include "services/device.h"

/**
 * @author Antonios Karagiannis (antokarag@gmail.com)
 * @brief (water) Pump Management
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief milliseconds since the last toggle action
 *
 */
unsigned long Pump::toggleTime = 0;

/**
 * @brief if true, the relay is currently active
 */
bool Pump::isToggleActive = false;

/**
 * @brief toggles the pump relay (if it's not currently active)
 */
void Pump::toggle()
{
    // only if the relay is not currently active
    if (!Pump::isToggleActive)
    {
        Pump::toggleTime = millis();
        Pump::isToggleActive = true;
        digitalWrite(PUMP_RELAY_PIN, HIGH);
    }
}

/**
 * @brief checks if the toggle is active and needs to be turned off
 * must be called from within the loop
 */
void Pump::checkToggle()
{
    if (Pump::isToggleActive && millis() - Pump::toggleTime >= PUMP_RELAY_DURATION_MILLIS)
    {
        Pump::isToggleActive = false;
        digitalWrite(PUMP_RELAY_PIN, LOW);
    }
}

/**
 * @brief should be called once, from the main setup() function
 *
 */
void Pump::setup()
{
    pinMode(PUMP_RELAY_PIN, OUTPUT);
    digitalWrite(PUMP_RELAY_PIN, LOW);
}

/**
 * @brief should be called on every iteration of the main loop() function
 *
 */
void Pump::loop()
{
    Pump::checkToggle();
}
