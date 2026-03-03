#include "potentiometer.h"
#include <Arduino.h>

void sensorValueToDegree(int &degree_shift) {
  const uint8_t pin = A2;
  // Optional: dummy read + tiny average for stability
  (void)analogRead(pin);
  uint32_t s = 0; for (int i=0;i<4;i++) s += analogRead(pin);
  int sensorValue = s / 4;

  // Calibrated endpoints from your measurements:
  const int inMin  = 0;   // sensor at 0°
  const int inMax  = 1023;   // sensor at 360°
  const int outMin = 0;
  const int outMax = 360;

  degree_shift = map(sensorValue, inMin, inMax, outMin, outMax);
  degree_shift = constrain(degree_shift, outMin, outMax);


}