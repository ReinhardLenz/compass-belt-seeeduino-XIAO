#ifndef COMPASSBELT_H
#define COMPASSBELT_H

#include <Arduino.h>
#include <SPI.h>
#include <MCP23S17.h>
#include "HapticBelt.h"

class Compassbelt {
public:
    Compassbelt(unsigned long vibrationDuration,
                unsigned long vibrationInterval,
                uint8_t chipSelect = 0);

    void begin();
    void update(float heading, int degree_shift = 0);

private:
    unsigned long _vibrationDuration;
    unsigned long _vibrationInterval;

    uint8_t _chipSelect;
    MCP23S17 _bank;
    HapticBelt _haptic;
};


#endif
