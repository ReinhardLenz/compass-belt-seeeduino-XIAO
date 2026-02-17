#include <Arduino.h>
#include "Compass.h"
#include "Compassbelt.h"
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
int degree_shift;
long lastSerialRecv = -10000L;
float lastSerialHeading = 0.0f;
const int alwaysOnButtonPin = 6;

Compass compass;
BNO08x imu;
CompassBelt  compassBelt(vibrationDurationMillis, vibrationIntervalMillis,7);   // chip select = 0
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
    Compass::setReports(&imu, SH2_ROTATION_VECTOR,
                        compass.getReportInterval());
    //compassBelt.begin(); 
    //pinMode(alwaysOnButtonPin, INPUT_PULLUP);

    buttonInstance.setup();
    compassBelt.setupPins(); 
    Serial.println("Setup complete");
}

void loop() {
    //Serial.println(digitalRead(alwaysOnButtonPin));
    buttonInstance.tick();
    delay(10);
    sensorValueToDegree(degree_shift);
    float heading = compass.getHeading(&imu, degree_shift);
    //Serial.println(heading);
    //compassBelt.update_old(heading,degree_shift);  // 
    compassBelt.update(heading, degree_shift);
    //Serial.print("update");
}
