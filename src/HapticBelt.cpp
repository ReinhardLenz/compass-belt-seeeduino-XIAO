#include "HapticBelt.h"

HapticBelt::HapticBelt(MCP23S17& bank)
: _bank(bank),
  _activeIndex(-1),
  _isOn(false),
  _minIntervalUs(800),
  _lastWriteUs(0)
{
}

void HapticBelt::begin() {
  for (int i = 0; i < 16; i++) {
    _bank.pinMode(i, OUTPUT);
    _bank.digitalWrite(i, LOW);
  }
  _activeIndex = -1;
  _isOn = false;
}

void HapticBelt::setRateLimitUs(uint32_t us) {
  _minIntervalUs = us;
}

bool HapticBelt::isDirectionValid(double direction) {
  double d2 = direction * 2.0;
  return d2 >= 0.0 && d2 < 720.0 && (((int)d2) % 45 == 0);
}

uint8_t HapticBelt::dirToIndex(double direction) const {
  return static_cast<uint8_t>(direction / 22.5);
}

bool HapticBelt::writePin(uint8_t pin, uint8_t level) {
  uint32_t now = micros();
  if ((now - _lastWriteUs) < _minIntervalUs) {
    return false;                       // too soon; try next loop
  }
  _bank.digitalWrite(pin, level);
  _lastWriteUs = now;


  
  return true;
}

void HapticBelt::on(double direction) {
  if (!isDirectionValid(direction)) return;

  const uint8_t idx = dirToIndex(direction);

  // If we believe we're already ON at this index, nothing to do
  if (_isOn && _activeIndex == static_cast<int8_t>(idx)) {
    return;
  }

  // If ON at a different index, turn that one OFF first
  if (_isOn && _activeIndex >= 0 && _activeIndex != static_cast<int8_t>(idx)) {
    if (!writePin(static_cast<uint8_t>(_activeIndex), LOW)) {
      return;  // couldn't write yet; try again next loop
    }
    _isOn = false;             // now it's really off
    _activeIndex = -1;
  }

  // Turn the requested index ON
  if (writePin(idx, HIGH)) {
    _activeIndex = idx;
    _isOn = true;              // only set true if we actually toggled the pin
  }
}

void HapticBelt::off(double direction) {
  if (!isDirectionValid(direction)) return;

  const uint8_t idx = dirToIndex(direction);

  if (_isOn && _activeIndex == static_cast<int8_t>(idx)) {
    if (writePin(idx, LOW)) {
      _isOn = false;
      _activeIndex = -1;
    }
  }
}

void HapticBelt::off() {
  if (_isOn && _activeIndex >= 0) {
    if (writePin(static_cast<uint8_t>(_activeIndex), LOW)) {
      _isOn = false;
      _activeIndex = -1;
    }
  }
}
