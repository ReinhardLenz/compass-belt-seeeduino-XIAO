# Compass Belt (Seeeduino XIAO + MCP23S17)

<img width="751" height="359" alt="compass_illustration" src="https://github.com/user-attachments/assets/4f6872b7-1c5e-4beb-9d7e-95de2bce0bb5" />


![keltainen_vyo-vyotairoityna](https://github.com/user-attachments/assets/7560b0e8-bc3e-4529-bb0a-b7f5bcb325cf)


## Overview

This repository contains a **Compass belt application** that drives **16 vibration motors arranged in a circular layout**. The motor pointing toward **magnetic north** is vibrating, creating a simple and intuitive directional indicator.

This project is a **compact evolution of an earlier compass belt design** that was based on an **Arduino Mega 2560**. By switching to a **Seeeduino XIAO** combined with an **MCP23S17 I/O expander**, and  the overall size and wiring complexity are significantly reduced while still supporting 16 vibrators. The vibration motors are powered by **ULN2803** Darlington arrays to provide sufficient current, as the **Seeeduino XIAO** alone can't supply enough. The vibration motors draw their power from **18650** batteries, while the **Seeeduino XIAO** controls the logic.

The circuit is a system that integrates a Seeeduino XIAO microcontroller, an MCP23S17 I/O expander, two ULN2803 Darlington Arrays, multiple coin vibration motors, a BNO085 sensor, a TPS63031 power management IC, and other components such as resistors, potentiometers, and push buttons. The circuit is designed to control multiple outputs, including vibration motors, and interfaces with sensors and other peripherals through I2C and SPI communication protocols. The power supply is managed by a TPS63031, which regulates the voltage from 18650 batteries.

---

## Features

* Always feel North**: A vibration motor on the belt buzzes gently to indicate magnetic north.
* Smart IMU sensor**: Uses the Adafruit BNO085 (SlimeVR-compatible) 9-DOF sensor for reliable orientation tracking.
* Custom vibration modes**: Supports intermittent and continuous haptic feedback with adjustable timing.
* Adjustable direction offset**: Use the built-in potentiometer to rotate the north indication (0–360°).
* Battery powered**: Dual 18650 batteries provide approximately 3 hours of navigation.
* 16  Vibration motor arranged in a circle
* motor pointing to magnetic north vibrates
* SPI-controlled I/O expansion using MCP23S17
* Absolute orientation sensing via BNO085 (I2C)
* Compact form factor using Seeeduino XIAO

Planned features:
3D box
---

# **Circuit Documentation**

## **Summary**

This circuit is a complex embedded system that integrates a variety of components, including a microcontroller, a port expander, a Darlington array, vibration motors, a power management IC, a battery, a sensor, a push button, and a potentiometer. The circuit is designed to control multiple vibration motors using a microcontroller and a port expander, with power supplied by a battery and regulated by a power management IC. The system also includes a sensor for additional functionality and a potentiometer for user input.


## **Circuit diagram**


<img width="3000" height="3253" alt="circuit_image3" src="https://github.com/user-attachments/assets/6893eaf3-517d-42cc-8194-1b0c31090bd7" />


## **Photo of breadboard**
note, that in the photo the potentiometer is missing and there are not motores but LED's instead. Also the TPS63031 is not yet inmplemented, but power supply is from Computer to Seeeduino XIAO. 

![seeeduino_XIAO_compass_Belt_breadboard_1](https://github.com/user-attachments/assets/f0536608-d132-4b15-991f-f23b8976a1ff)


# **Circuit Documentation**

## **Summary**

This circuit is a Seeeduino XIAO microcontroller, an MCP23S17 I/O expander, 2 pcs ULN2803 Darlington Arrays, 16 coin vibration motors, a BNO085 sensor, a TPS63031 power management IC, two 18650 batteries, a potentiometer, a push button, and an ON OFF switch. The circuit is designed to control multiple vibration motors using the I/O expander and Darlington arrays, with power management and sensor integration for enhanced functionality.

## **Component List**

1. **Seeeduino XIAO**  
   * Description: A compact microcontroller board based on the SAMD21G18 chip.  
   * Pins: A0 \- D0 \- DAC, A1 \- D1, A2 \- D2, A3 \- D3, A4 \- D4 \- SDA, A5 \- D5 \- SCL, A6 \- D6 \- TX, 5V, GND, 3V3, A10 \- D10 \- MOSI, A9 \- D9 \- MISO, A8 \- D8 \- SCK, A7 \- D7 \- RX

  ![SeeeduinoXIAO_pinout](https://github.com/user-attachments/assets/0ed14b73-8941-46c7-b2a2-2bc7261bacbb)


2. **MCP23S17**  
   * Description: 16-bit I/O expander with SPI interface.  
   * Pins: GPB0, GPB1, GPB2, GPB3, GPB4, GPB5, GPB6, GPB7, A1, A0, SO, SI, CS, VSS, VDD, INTA, INTB, RESET, A2, GPA1, GPA0, GPA5, GPA4, GPA3, GPA2, GPA7, GPA6, SCK

  ![MCP23S17](https://github.com/user-attachments/assets/644f30b3-bc0e-443f-adfb-a1b2bee335c3)

   
4. **ULN2803 Darlington Array (2 units)**  
   * Description: High-voltage, high-current Darlington transistor arrays.  
   * Pins: I1, I2, I3, I4, I5, I6, I7, I8, O3, O4, O5, O6, O7, O8, GND, COMMON, O1, O2

  ![ULN2803](https://github.com/user-attachments/assets/ced70a70-51d8-48f5-ac68-6810b382a1c9)

   
6. **COIN VIBRATION MOTOR (14 units)**  
   * Description: Small DC motors used for vibration feedback.  
   * Pins: \+, \-  
7. **TPS63031**  
   * Description: High-efficiency, low-power buck-boost converter.  
   * Pins: VIN, NC, GND, OUT

  ![TPS63031](https://github.com/user-attachments/assets/536e1c79-3bb5-49d2-8afd-97ba39a34019)


8. **18650 Battery (2 units)**  
   * Description: Rechargeable lithium-ion battery.  
   * Pins: \+, \-  
9. **BNO085**  
   * Description: 9-axis absolute orientation sensor.  
   * Pins: VCC, GND, SCL/SCK/RX, SDA/MISO/TX, ADR/MOSI, CS, INT, RST, PS1, PS0

  ![BNO085](https://github.com/user-attachments/assets/4857b41c-9c59-40cc-bdcf-2a0eceb9edd8)


10. **Push Button**  
   * Description: Simple push button switch.  
   * Pins: pin1, pin2  
11. **Potentiometer Piher 10mm**  
   * Description: Adjustable resistor for variable resistance.  
   * Pins: A, Variable, B  
11. **SPDT Switch**  
    * Description: Single pole double throw switch.  
    * Pins: 1, C, 2

## **Wiring Details**

### **Seeeduino XIAO**

* **3V3**: Connected to the positive terminals of multiple coin vibration motors, BNO085 VCC, and TPS63031 OUT.  
* **GND**: Connected to BNO085 GND, push button pin1, 18650 battery negative terminal, ULN2803 GND, and TPS63031 GND.  
* **A0 \- D0 \- DAC**: Connected to MCP23S17 CS.  
* **A8 \- D8 \- SCK**: Connected to MCP23S17 SCK.  
* **A10 \- D10 \- MOSI**: Connected to MCP23S17 SI.  
* **A9 \- D9 \- MISO**: Connected to MCP23S17 SO.  
* **A2 \- D2**: Connected to the variable pin of the Potentiometer.  
* **A6 \- D6 \- TX**: Connected to push button pin2.  
* **A5 \- D5 \- SCL**: Connected to BNO085 SCL/SCK/RX.  
* **A4 \- D4 \- SDA**: Connected to BNO085 SDA/MISO/TX.  
* **A7 \- D7 \- RX**: Connected to MCP23S17 VDD.

### **MCP23S17**

* **CS**: Connected to Seeeduino XIAO A0 \- D0 \- DAC.  
* **SCK**: Connected to Seeeduino XIAO A8 \- D8 \- SCK.  
* **SI**: Connected to Seeeduino XIAO A10 \- D10 \- MOSI.  
* **SO**: Connected to Seeeduino XIAO A9 \- D9 \- MISO.  
* **VSS**: Connected to ground.  
* **VDD**: Connected to Seeeduino XIAO A7 \- D7 \- RX.  
* **GPA0 to GPA7**: Connected to inputs I1 to I8 of the first ULN2803.  
* **GPB0 to GPB7**: Connected to inputs I1 to I8 of the second ULN2803.

### **ULN2803 Darlington Array**

* **COMMON**: Connected to the 3V3 net.  
* **GND**: Connected to ground.  
* **Outputs O1 to O8**: Connected to the negative terminals of various coin vibration motors.

### **COIN VIBRATION MOTOR**

* **\+**: Connected to the 3V3 net.  
* **\-**: Connected to outputs O1 to O8 of the ULN2803 arrays.

### **TPS63031**

* **VIN**: Connected to SPDT Switch pin 2\.  
* **GND**: Connected to ground.  
* **OUT**: Connected to the 3V3 net.

### **18650 Battery**

* **\+**: Connected to SPDT Switch common pin (C).  
* **\-**: Connected to ground and the positive terminal of the second 18650 battery.

### **BNO085**

* **VCC**: Connected to the 3V3 net.  
* **GND**: Connected to ground.  
* **SCL/SCK/RX**: Connected to Seeeduino XIAO A5 \- D5 \- SCL.  
* **SDA/MISO/TX**: Connected to Seeeduino XIAO A4 \- D4 \- SDA.

### **Push Button**

* **pin1**: Connected to ground.  
* **pin2**: Connected to Seeeduino XIAO A6 \- D6 \- TX.

### **Potentiometer Piher 10mm**

* **A**: Connected to ground.  
* **Variable**: Connected to Seeeduino XIAO A2 \- D2.  
* **B**: Connected to the 3V3 net.

### **SPDT Switch**

* **1**: Not connected.  
* **C**: Connected to the positive terminal of the first 18650 battery.  
* **2**: Connected to TPS63031 VIN.



## Software Overview

### Environment

* Platform: Arduino
* Board: Seeeduino XIAO (SAMD21)
* Libraries used:

  * `SPI`
  * (BNO085 sensor library sparkfun/SparkFun BNO08x Cortex Based IMU@^1.0.6)
  * mathertel/OneButton@^2.6.1
  * adafruit/Adafruit MCP23017 Arduino Library @ ^2.3.2
---

### Code Functionality

* Initializes SPI communication with MCP23S17
* Configures MCP23S17 GPIO pins as outputs
* Reads orientation data from BNO085 via I2C
* Calculates heading and maps it to one of 16 vibrators positions
* Activates the corresponding vibrators

Current  behavior:

* GPIOA pins are toggled to create a blinking vibrators pattern with different blink length
* Double click activates continuous vibration
* long click activates motor test
---

## Future Improvements

* Improve enclosure and wearable integration
* Develop a mobile app for configuration via Bluetooth.
* 3D printed box for the electronics
* soft start and end ramp for vibration motor

## ⚙️ Usage

### Controls

- **Single Click**: Switch vibration cycle (1s, 2s, 3s, 4s)
- **Double Click**: Toggle between continuous/intermittent mode
- **Long Press**: Test all motors



### Mounting & Wearing

- The electronics are housed in a custom 3D-printed box attached to elastic “suspender-style” straps.
- The belt with vibration motors wraps around your torso, covered with washable yellow synthetic fabric.
- The IMU sensor must stay relatively horizontal for accurate heading detection.
---

## License

This project is open-source under the MIT License. See [LICENSE](LICENSE) for more information.

---

## Acknowledgements

* Seeed Studio – Seeeduino XIAO
* Microchip – MCP23S17
* Bosch / Hillcrest Labs – BNO085

![Visitor Count](https://komarev.com/ghpvc/?username=ReinhardLenz&repo=compass-belt-seeeduino-XIAO&color=green)

