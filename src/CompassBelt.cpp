
#include "CompassBelt.h"

const long CompassBelt::vibrationIntervalChoices[] = {500, 1500, 2500, 3500};// The default 

CompassBelt::CompassBelt(unsigned long vibrationDuration,
                         unsigned long vibrationInterval,
                         uint8_t chipSelect)
    : _vibrationDuration(vibrationDuration),
      _vibrationInterval(vibrationInterval),
      _chipSelect(chipSelect),
      _bank(&SPI, chipSelect, 0),
      _haptic(_bank)
{
  vibrationInterval_ = vibrationInterval;
  lastDirection_ = -1;
  onDuration_ = vibrationDuration;
  vibrationInterval_ = vibrationInterval;
  lastOn_ = 0;
}

void CompassBelt::setupPins() {
    _bank.begin();
    _haptic.begin();
  for (int i = 0; i < 16; i++) {
    _bank.pinMode(i,OUTPUT);
  }
}

/******************************************************************************************************************
  // When alwaysOn_ is true, shouldStartVibrating will always return true,
  // meaning the belt will continuously start vibrating in the update method as
  // the setReports loop iterates.
  // Concurrently, shouldStopVibrating will always return false, ensuring the
  belt remains in a vibrating state during consistent head readings.
*/

void CompassBelt::setAlwaysOn(bool alwaysOn) {
  alwaysOn_ = alwaysOn;
}
/******************************************************************************************************************
  // setAlwaysOn sets the alwaysOn_ flag based on the double press (in main.ino program)
  isAlwaysOn simply returns the current state of alwaysOn_. (like a question)
*/
bool CompassBelt::isAlwaysOn() {
  return alwaysOn_;
}
/******************************************************************************************************************
  // Turns off the haptic feedback for the belt.
  // This function calls the 'off' method of the HapticBelt object,
  ensuring that any ongoing vibrations are stopped immediately.
*/
void CompassBelt::off()
{
    _haptic.off();
  }
/******************************************************************************************************************
  //goes around the LED's or vibration motors one time, switching on every one , so see, if all are working
  //sometimes, there a bad solders or connection or motor is not tightly presses to skin , so it doesn't feel
  // also with LED's there had been problems with the dupont connectors used.
  // this is started with long press of the pushbutton
*/
void CompassBelt::lampTest() {
  int numberOfPins = 16;
  for (int i = 0; i < numberOfPins; i++) {
    for (int j = 0; j < numberOfPins; j++) {
      _bank.digitalWrite(j,LOW);//changed to high
    }
    _bank.digitalWrite(i,HIGH);//change to low
    delay(200);
  }
  _bank.digitalWrite(numberOfPins - 1,LOW);//change to high
}



/*
  // Direction Change & Initiation: If the heading value results in a new direction
  //  (calculated and snapped to nearest 18 degrees), the compass belt will update
  //  the new direction and turn on the belt. This resets lastOn_ to the current time
  //  returned by millis().
*/
void CompassBelt::update(double heading, int degree_shift)
{
  if (heading < 0 || heading >= 360) {
    return;
  }
  const double direction_threshold = 3;
  double direction = round(heading / 22.5) * 22.5;
//Serial.print("direction: ");
//  Serial.println(direction);

  if (lastDirection_ != -1 && abs(direction - heading) > direction_threshold)
    /* The choice of -1 for sentinel variable lastDirection_ is often due to several reasons:
      // Sentinel Value: -1 is used as a sentinel value to represent an invalid or uninitialized
      //  state since direction  values are usually non-negative. It helps distinguish between a real
      //  direction (e.g., 0, 1, 2, ...) and a state where no direction has been set.
      //
      // Ease of Checking: Checking if a variable is equal to -1 is straightforward and unambiguous,
      //  which makes the code easier to read and maintain.
      //
      // Common Convention: Using -1 or other negative values as sentinel values is a common
      //  programming practice, making the code more understandable to other developers who encounter it.
    */
  {
    direction = lastDirection_;
    //Serial.print(" Heading change too large, keeping last direction: ");
  }

  if (direction != lastDirection_) {
    if (lastDirection_ != -1) {
      _haptic.off(lastDirection_); 
    }
    //Serial.println(direction);
    lastDirection_ = direction;
    _haptic.on(direction);
    lastOn_ = millis();
  }
  
  if (shouldStartVibrating()) {
    _haptic.on(direction);
    lastOn_ = millis();
  } else if (shouldStopVibrating()) {
    _haptic.off(direction);
  }
}


//******************************************************************************************************************
  // Vibration should stop if the alwaysOn_ flag is false
  //  and enough time has passed since lastOn_ to exceed the onDuration_.

bool CompassBelt::shouldStopVibrating() {
  return !alwaysOn_ && millis() - lastOn_ >= onDuration_;
}

bool CompassBelt::shouldStartVibrating() {
  unsigned long timeSinceOn = millis() - lastOn_;
  return alwaysOn_ || timeSinceOn >= onDuration_ + vibrationInterval_;
}
/******************************************************************************************************************
  // Vibration should stop if the alwaysOn_ flag is false
  //  and enough time has passed since lastOn_ to exceed the onDuration_.
*/



  // Method to set the next vibration interval cyclically

void CompassBelt::setNextVibrationInterval() {
  static int currentIndex = 0;
  currentIndex = (currentIndex + 1) % (sizeof(vibrationIntervalChoices) / sizeof(vibrationIntervalChoices[0]));
  vibrationInterval_ = vibrationIntervalChoices[currentIndex];
}



