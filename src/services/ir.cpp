#include "services/ir.h"
#include "services/device.h"
#include "services/pump.h"
#include "TinyIRReceiver.hpp"
#include "TinyIRSender.hpp"

/**
 * @author Antonios Karagiannis (antokarag@gmail.com)
 * @brief Ifrared
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */
unsigned long Ir::lastReceivedTime = 0;
uint8_t Ir::sendAddress = 0x02;
uint8_t Ir::sendCommand = 0x34;
uint8_t Ir::sendRepeats = 3;

/**
 * @brief should be called once, from the main setup() function
 *
 */
void Ir::setup()
{
    // Enables the interrupt generation on change of IR input signal
    if (!initPCIInterruptForTinyReceiver())
    {
#ifdef SERIAL_DEBUG
        Serial.println("No interrupt available for IR RX pin");
#endif
    }
}

/**
 * @brief should be called on every iteration of the main loop() function
 *
 */
void Ir::loop()
{

    if (TinyIRReceiverData.justWritten)
    {
        TinyIRReceiverData.justWritten = false;
        if (millis() - Ir::lastReceivedTime > IR_RECEIVE_DEBOUNCE_TIME)
        {
            Ir::lastReceivedTime = millis();
            Ir::onReceive(TinyIRReceiverData.Address, TinyIRReceiverData.Command, TinyIRReceiverData.Flags == IRDATA_FLAGS_IS_REPEAT, TinyIRReceiverData.Flags == IRDATA_FLAGS_PARITY_FAILED);
        }
    }
}

void Ir::onReceive(uint8_t address, uint8_t command, bool repeat, bool parityFailed)
{
#ifdef SERIAL_DEBUG
    Serial.print("onReceive address: ");
    Serial.print(address, HEX);
    Serial.print(" command: ");
    Serial.print(command, HEX);
    Serial.print(" repeat: ");
    Serial.print(repeat);
    Serial.print(" parityFailed: ");
    Serial.println(parityFailed);
#endif
    if (!parityFailed)
    {
        Pump::toggle();
    }
}

void Ir::send()
{
    sendNEC(IR_SEND_PIN, Ir::sendAddress, Ir::sendCommand, Ir::sendRepeats);
}
