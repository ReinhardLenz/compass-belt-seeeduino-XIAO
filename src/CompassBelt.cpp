#include "CompassBelt.h"
#include <math.h>  // round(), fabs()

const long CompassBelt::vibrationIntervalChoices[] = {500, 1500, 2500, 3500};

CompassBelt::CompassBelt(unsigned long vibrationDuration,
                         unsigned long vibrationInterval,
                         uint8_t chipSelect)
: _vibrationDuration(vibrationDuration),
  _vibrationInterval(vibrationInterval),
  onDuration_(vibrationDuration),
  lastOn_(0),
  _chipSelect(chipSelect),
  _bank(&SPI, chipSelect, 0),
  _haptic(_bank),
  vibrationInterval_(vibrationInterval),
  lastDirection_(-1)
{
}

void CompassBelt::setupPins() {
  _bank.begin();
  _haptic.begin();
  for (int i = 0; i < 16; i++) {
    _bank.pinMode(i, OUTPUT);
  }
  _haptic.setRateLimitUs(1000); // 1 ms spacing (tune as needed)
}

void CompassBelt::setSpiRateLimitUs(uint32_t us) {
  _haptic.setRateLimitUs(us);
}

bool CompassBelt::isAlwaysOn() {
  return alwaysOn_;
}

void CompassBelt::setAlwaysOn(bool alwaysOn) {
  alwaysOn_ = alwaysOn;
  if (alwaysOn_) {
    // Force a re-start on next update even if lastDirection_ didn't change
    isVibrating_ = false;
  }
}

void CompassBelt::lampTest() {
  const int N = 16;
  _haptic.off();
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) _bank.digitalWrite(j, LOW);
    _bank.digitalWrite(i, HIGH);
    delay(200);
  }
  _bank.digitalWrite(N - 1, LOW);
}

bool CompassBelt::shouldStopVibrating() {
  return (!alwaysOn_) && isVibrating_ && (millis() - lastOn_ >= onDuration_);
}

bool CompassBelt::shouldStartVibrating() {
  const unsigned long dt = millis() - lastOn_;
  if (alwaysOn_) return !isVibrating_;
  return dt >= (onDuration_ + vibrationInterval_);
}

void CompassBelt::update(double heading, int /*degree_shift*/) {
  if (heading < 0.0 || heading >= 360.0) return;

  // --- NEW: wrap-aware smoothing (EMA) ---
  static bool   haveSmooth = false;
  static double smoothDeg  = 0.0;
  const double  alpha      = 0.18; // 0..1 (higher = more responsive, lower = smoother)
                                // lower alpha from 0.25 to 0.18. If it feels “sticky,” increase toward 0.35.
  if (!haveSmooth) {
    smoothDeg  = heading;
    haveSmooth = true;
  } else {
    double d = heading - smoothDeg;
    // wrap fix: bring to [-180, +180]
    if (d > 180.0)  d -= 360.0;
    if (d < -180.0) d += 360.0;
    smoothDeg = smoothDeg + alpha * d;
    // keep in [0,360)
    if (smoothDeg >= 360.0) smoothDeg -= 360.0;
    if (smoothDeg < 0.0)    smoothDeg += 360.0;
  }
  // --- END smoothing ---

const double direction_threshold = 3.0;
double direction = round(smoothDeg / 22.5) * 22.5;
if (lastDirection_ != -1 && fabs(direction - smoothDeg) > direction_threshold) {
    direction = lastDirection_;
  }

  if (direction != lastDirection_) {
    if (lastDirection_ != -1) _haptic.off(lastDirection_);
    _haptic.on(direction);
    isVibrating_ = _haptic.isOn();  
    lastOn_ = millis();
    lastDirection_ = direction;
  }

  if (shouldStartVibrating()) {
    _haptic.on(direction);   // cached -> no redundant SPI write
    isVibrating_ = _haptic.isOn();  
    lastOn_ = millis();
  } else if (shouldStopVibrating()) {
    _haptic.off(direction);  // cached -> no-op if already low
      isVibrating_ = _haptic.isOn();  
  }
}

void CompassBelt::setNextVibrationInterval() {
  static int idx = 0;
  idx = (idx + 1) % (sizeof(vibrationIntervalChoices)/sizeof(vibrationIntervalChoices[0]));
  vibrationInterval_ = vibrationIntervalChoices[idx];
}

void CompassBelt::off() {
  _haptic.off();
  isVibrating_ = false;
}
