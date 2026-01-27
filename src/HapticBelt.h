#ifndef HAPTICBELT_H
#define HAPTICBELT_H

#include <Arduino.h>
#include <SPI.h>
#include <MCP23S17.h>
#include <Math.h>
class HapticBelt 
{
public:
    // Constructor takes an already-existing MCP23S17
    HapticBelt(MCP23S17& bank);

    void begin();
 //   void on_old();
 //   void off_old();
    void on(double direction);
    void off(double direction);
    void off();

private:
    MCP23S17& _bank;
    bool isDirectionValid(double direction);

};

#endif
