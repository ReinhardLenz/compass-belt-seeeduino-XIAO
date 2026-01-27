#include "HapticBelt.h"

HapticBelt::HapticBelt(MCP23S17& bank)
    : _bank(bank)
{
}

void HapticBelt::begin() {
  for (int i = 0; i < 16; i++){
    _bank.pinMode(i, OUTPUT);
    _bank.digitalWrite(i, HIGH);//changed to HIGH
  }
  //Serial.println(" HapticBelt::begin completed");
}

/* Method to check if the direction is valid (used inside  HapticBelt and off)
// VALIDATION
//The direction must be greater than or equal to 0.
//The direction must be less than 360.
//The direction must be a multiple of 22.5.
// Valid directions:
*/
bool HapticBelt::isDirectionValid(double direction)
{
  double check_direction = direction *2;
  return check_direction >= 0 && check_direction < 720 && (int)check_direction % 45 == 0;
}

/*  Method used in CompassBelt like this: belt_->on(direction, 255);
CHOSEN DIRECTION "ON"*/

void HapticBelt::on(double direction)
{
  if (!isDirectionValid(direction)) {

    return;
  }
  double position = (direction / 22.5);
//  Serial.print("position: ");
//  Serial.println(position);
  uint8_t pos_int = static_cast<uint8_t>(position);
  //It seems that position is from 0 to 15
  _bank.digitalWrite(pos_int, LOW);//changed to LOW
  Serial.println(pos_int);
}

/* Used in CompassBelt like this: belt_->off(direction);
chosen direction "OFF" */
void HapticBelt::off(double direction)
{
  if (!isDirectionValid(direction)) {
    return;
  }
    double position = (int)(direction / 22.5);
     uint8_t pos_int = static_cast<uint8_t>(position);

    _bank.digitalWrite(pos_int, HIGH);//cha hihg

}

void HapticBelt::off()
{
  for (int i = 0; i < 16; i++) {
  _bank.digitalWrite(i, HIGH);//chang High
//  Serial.println(" HapticBelt::off - All Motors OFF");
  }
}