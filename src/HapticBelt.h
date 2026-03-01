#ifndef HAPTICBELT_H
#define HAPTICBELT_H

#include <Arduino.h>
#include <SPI.h>
#include <MCP23S17.h>
#include <math.h>

class HapticBelt
{
public:
  explicit HapticBelt(MCP23S17& bank);

  void begin();

  // Minimum spacing between SPI writes (µs)
  void setRateLimitUs(uint32_t us);

  void on(double direction);
  void off(double direction);
  void off();

  int8_t activeIndex() const { return _activeIndex; }
  bool   isOn() const        { return _isOn; }

private:
  MCP23S17& _bank;

  int8_t   _activeIndex;   // -1 if none
  bool     _isOn;          // current on/off state
  uint32_t _minIntervalUs; // µs
  uint32_t _lastWriteUs;   // micros() timestamp

  bool    isDirectionValid(double direction);
  uint8_t dirToIndex(double direction) const;

  bool writePin(uint8_t pin, uint8_t level);
};

#endif