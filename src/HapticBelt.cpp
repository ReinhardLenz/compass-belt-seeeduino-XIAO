#include "HapticBelt.h"

HapticBelt::HapticBelt(MCP23S17& bank)
    : _bank(bank)
{
}

void HapticBelt::begin() {
    _bank.pinMode(0, OUTPUT);
    _bank.pinMode(1, OUTPUT);
}

void HapticBelt::on() {
    _bank.digitalWrite(0, HIGH);
    _bank.digitalWrite(1, LOW);
}

void HapticBelt::off() {
    _bank.digitalWrite(0, LOW);
    _bank.digitalWrite(1, HIGH);
}
