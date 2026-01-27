#ifndef COMPASSBELT_H
#define COMPASSBELT_H

#include <Arduino.h>
#include <SPI.h>
#include <MCP23S17.h>
#include "HapticBelt.h"

class CompassBelt {
public:
    CompassBelt(unsigned long vibrationDuration,
                unsigned long vibrationInterval,
                uint8_t chipSelect = 0);
    void update(double heading, int degree_shift);
    void begin();
//    void update_old(float heading, int degree_shift = 0);
    void setNextVibrationInterval(); 
    void lampTest();
    void off();
    bool isAlwaysOn();
    void setAlwaysOn(bool alwaysOn);
    void setupPins(); 
private:
    HapticBelt* belt_;
    unsigned long _vibrationDuration;
    unsigned long _vibrationInterval;
    unsigned long onDuration_;
    unsigned long lastOn_;
    uint8_t _chipSelect;
    MCP23S17 _bank;
    HapticBelt _haptic;
    static const long vibrationIntervalChoices[];
    unsigned long vibrationInterval_;
    bool alwaysOn_ = false;
    bool shouldStopVibrating();
    bool shouldStartVibrating();
    double lastDirection_;
};


#endif
