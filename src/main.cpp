#include <Arduino.h>
#include "Compass.h"
#include "CompassBelt.h"
#include "HapticBelt.h"
#include "Button.h"
#include <Wire.h>
#include <SparkFun_BNO08x_Arduino_Library.h>
#include "potentiometer.h"
#define BNO08X_RESET -1
#define TIMEOUT_BOOT_BNO 100
#define BNO08X_I2C_ADDRESS 0x4B

unsigned long millisOld;
const unsigned long vibrationDurationMillis = 200UL;
const unsigned long vibrationIntervalMillis = 1000UL;


const int PIN_SDA = A4;   // works on many cores; otherwise set explicit pin numbers
const int PIN_SCL = A5;

static uint32_t lastGoodEventMs = 0;
static uint32_t bootMs = 0;
static uint32_t lastRecoverAttemptMs = 0;

// Tune these:
const uint32_t STARTUP_GRACE_MS = 3000;          // wait after setup before any recovery
const uint32_t NO_EVENT_BEFORE_RECOVER_MS = 4000; // must be "dead" this long before recovery
const uint32_t RECOVER_COOLDOWN_MS = 5000;        // minimum time between recovery attempts

int degree_shift;
long lastSerialRecv = -10000L;
float lastSerialHeading = 0.0f;
const int alwaysOnButtonPin = 6;

Compass compass;
BNO08x imu;

static inline void wdtSync() {
  while (WDT->STATUS.bit.SYNCBUSY) { }
}

void initWatchdog_2s() {
  // Route 1kHz clock to WDT (required on SAMD21)
  GCLK->GENDIV.reg  = GCLK_GENDIV_ID(4) | GCLK_GENDIV_DIV(32); // 32kHz/32 = 1kHz
  GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(4) |
                      GCLK_GENCTRL_SRC_OSCULP32K |
                      GCLK_GENCTRL_GENEN;
  while (GCLK->STATUS.bit.SYNCBUSY) { }

  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID_WDT |
                      GCLK_CLKCTRL_GEN_GCLK4 |
                      GCLK_CLKCTRL_CLKEN;
  while (GCLK->STATUS.bit.SYNCBUSY) { }

  // Disable WDT before config
  WDT->CTRL.reg = 0;
  wdtSync();

  // Set ~2s period (2048 cycles @ 1kHz)
  //  WDT->CONFIG.reg = WDT_CONFIG_PER(WDT_CONFIG_PER_2048);
  //  WDT->CONFIG.reg = WDT_CONFIG_PER(WDT_CONFIG_PER_2048_Val);
  WDT->CONFIG.reg = WDT_CONFIG_PER(0xB); // 2048 cycles is typically enum value 0xB on SAMD2  wdtSync();

  // Optional: early warning interrupt disabled
  WDT->EWCTRL.reg = 0;
  wdtSync();

  // Enable WDT
  WDT->CTRL.reg = WDT_CTRL_ENABLE;
  wdtSync();
}

static inline void feedWatchdog() {
  WDT->CLEAR.reg = WDT_CLEAR_CLEAR_KEY;
  wdtSync();
}

void initBNO085() {
  delay(1000);

  // Re-start the IMU and re-enable the report
  if (!imu.begin()) {
    Serial.println("BNO08x re-init failed");
    return;
  }
  Compass::setReports(&imu, SH2_GAME_ROTATION_VECTOR, compass.getReportInterval());
  Serial.println("BNO08x re-init OK");
}

bool i2cBusClear() {
  pinMode(PIN_SDA, INPUT_PULLUP);
  pinMode(PIN_SCL, INPUT_PULLUP);
  delayMicroseconds(5);

  // If SCL is stuck low, we can't clear it here
  if (digitalRead(PIN_SCL) == LOW) return false;

  // If SDA is stuck low, try to free it by clocking SCL
  if (digitalRead(PIN_SDA) == LOW) {
    pinMode(PIN_SCL, OUTPUT);
    for (int i = 0; i < 9; i++) {
      digitalWrite(PIN_SCL, HIGH);
      delayMicroseconds(5);
      digitalWrite(PIN_SCL, LOW);
      delayMicroseconds(5);
    }
    pinMode(PIN_SCL, INPUT_PULLUP);
    delayMicroseconds(5);
  }

  // Generate a STOP: SDA low -> SCL high -> SDA high
  pinMode(PIN_SDA, OUTPUT);
  digitalWrite(PIN_SDA, LOW);
  delayMicroseconds(5);

  pinMode(PIN_SCL, INPUT_PULLUP);
  delayMicroseconds(5);

  pinMode(PIN_SDA, INPUT_PULLUP);
  delayMicroseconds(5);

  return (digitalRead(PIN_SDA) == HIGH);
}

void reinitWire() {
  Wire.end();
  delay(10);
  Wire.begin();
  Wire.setClock(10000);
  Wire.setTimeout(50);
}

CompassBelt  compassBelt(vibrationDurationMillis, vibrationIntervalMillis,7);   // chip select = 7
void sensorValueToDegree(int &degree_shift);
Button buttonInstance(alwaysOnButtonPin, &compassBelt);

void waitForUser() {
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for Serial Monitor to open
  }

  Serial.println("=== Waiting for user ===");
  Serial.println("Send any character to start setup");

  while (!Serial.available()) {
    ; // wait for user input
  }

  Serial.read(); // consume char
  Serial.println("=== Starting setup ===");
}


void setup() {
    //waitForUser();
    delay(5000);  // give bootloader time to enumerate
    Serial.begin(9600);


   unsigned long t0 = millis();
  bool serialReady = false;

  while (millis() - t0 < 2000) {        // Wait max 2 sec
    if (Serial) {
      serialReady = true;
      break;
    }
    delay(10);
  }

  if (serialReady) {
    Serial.println("Serial monitor connected!");
    digitalWrite(LED_BUILTIN, HIGH);    // optional indicator
  } else {
    // Serial monitor not connected, continue anyway
  }
    
    Wire.begin();
    Wire.setClock(10000);
    delay(200);   // IMPORTANT: let BNO085 boot 


    if (!imu.begin())
    {
        Serial.println("BNO08x not detected!");
        while (1);
       Serial.println("BNO08x ready");
    }

      initWatchdog_2s();


                        
if (!imu.enableGameRotationVector(50)) {
  Serial.println("❌ enableGameRotationVector failed");
} else {
  Serial.println("✅ GameRotationVector enabled");
}



  buttonInstance.setup();
  compassBelt.setupPins(); 
  Serial.println("Setup complete");

  bootMs = millis();
  lastGoodEventMs = millis();        // start "alive"
  lastRecoverAttemptMs = 0;

}

void loop() {
  // 1) Button handling / small pacing
  buttonInstance.tick();
  delay(10);

  // 2) Read degree shift first (potentiometer)
  sensorValueToDegree(degree_shift);

  // 3) Get new IMU event & compute heading ONCE if there is a new event
  static float lastHeading = NAN;
  bool gotEvent = imu.getSensorEvent();

  if (gotEvent) {
    // Push the new event into Compass
    compass.updateFromSensor(imu.sensorValue);

    // Compute heading once for this event, using the latest degree_shift
    lastHeading = compass.getHeading(degree_shift);

    // Optional: print once per event
    uint8_t acc = compass.getAccuracy();
    Serial.print("✅ Event sensorId=");
    Serial.println(imu.sensorValue.sensorId);
    Serial.print("Heading: ");
    Serial.print(lastHeading);
    Serial.print(" Accuracy: ");
    Serial.println(acc);

    lastGoodEventMs = millis();
  } else {
    // Optional 1s heartbeat
    static uint32_t lastPrintMs = 0;
    if (millis() - lastPrintMs > 1000) {
      Serial.println("No sensor event (not necessarily an error)");
      lastPrintMs = millis();
    }
  }

  // 4) Drive the belt using the last good heading every loop
  if (!isnan(lastHeading)) {
    compassBelt.update(lastHeading, degree_shift);
  }

  // 5) Recovery logic (unchanged)
  if (millis() - bootMs < STARTUP_GRACE_MS) {
    feedWatchdog();
    return;
  }

  bool deadTooLong  = (millis() - lastGoodEventMs) > NO_EVENT_BEFORE_RECOVER_MS;
  bool cooldownOver = (lastRecoverAttemptMs == 0) ||
                      ((millis() - lastRecoverAttemptMs) > RECOVER_COOLDOWN_MS);
  if (deadTooLong && cooldownOver) {
    lastRecoverAttemptMs = millis();
    Serial.println("⚠️ No events for too long -> attempting recovery");
    i2cBusClear();
    reinitWire();
    delay(1000);
    initBNO085(); // calls imu.begin() + setReports
  }

  feedWatchdog();
}
