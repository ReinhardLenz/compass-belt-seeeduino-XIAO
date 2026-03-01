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

  void setupPins();
  void update(double heading, int degree_shift);

  void setNextVibrationInterval();
  void lampTest();
  void off();

  bool isAlwaysOn();
  void setAlwaysOn(bool alwaysOn);

  void setSpiRateLimitUs(uint32_t us);

private:
  unsigned long _vibrationDuration;
  unsigned long _vibrationInterval;
  unsigned long onDuration_;
  unsigned long lastOn_;

  uint8_t  _chipSelect;
  MCP23S17 _bank;
  HapticBelt _haptic;

  static const long vibrationIntervalChoices[];

  unsigned long vibrationInterval_;
  bool alwaysOn_ = false;
  bool isVibrating_ = false;
  double lastDirection_;

  bool shouldStopVibrating();
  bool shouldStartVibrating();
};

#endif