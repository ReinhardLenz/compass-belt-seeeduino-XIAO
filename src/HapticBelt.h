#ifndef HAPTICBELT_H
#define HAPTICBELT_H

#include <Arduino.h>
#include <SPI.h>
#include <MCP23S17.h>

class HapticBelt {
public:
    // Constructor takes an already-existing MCP23S17
    HapticBelt(MCP23S17& bank);

    void begin();

    void on();
    void off();

private:
    MCP23S17& _bank;
};

#endif
