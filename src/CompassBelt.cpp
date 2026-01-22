#include "Compassbelt.h"

Compassbelt::Compassbelt(unsigned long vibrationDuration,
                         unsigned long vibrationInterval,
                         uint8_t chipSelect)
    : _vibrationDuration(vibrationDuration),
      _vibrationInterval(vibrationInterval),
      _chipSelect(chipSelect),
      _bank(&SPI, chipSelect, 0),
      _haptic(_bank)
{
}

void Compassbelt::begin() {
    _bank.begin();
    _haptic.begin();
}

void Compassbelt::update(float heading, int degree_shift) {
    if (heading < 190.0f && heading > 170.0f) {
        _haptic.on();
    } else {
        _haptic.off();
    }
}
