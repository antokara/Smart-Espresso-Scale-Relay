#include <Arduino.h>
#include "services/device.h"
#include "services/pump.h"
#include "services/ir.h"

void setup()
{
#ifdef SERIAL_DEBUG
    Serial.begin(9600);
    delay(2000);
#endif
    Pump::setup();
    Ir::setup();
}

void loop()
{
    Pump::loop();
    Ir::loop();
}
