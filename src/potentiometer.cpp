#include "potentiometer.h"
#include <Arduino.h>

void sensorValueToDegree(int &degree_shift) {
  int sensorValue = analogRead(A3);
  degree_shift = int(sensorValue / 2.86666);
  if (degree_shift > 360) {
    degree_shift = 360;
  }
}
