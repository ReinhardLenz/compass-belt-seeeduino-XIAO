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

<img width="2477" height="1781" alt="circuit_image" src="https://github.com/user-attachments/assets/8d295dae-4ca2-45db-b3d6-d9cbdef87bef" />

## **Photo of breadboard**
note, that the potentiometer is missing and there are not motores but LED's instead!

![seeeduino_XIAO_compass_Belt_breadboard](https://github.com/user-attachments/assets/35766f08-f9db-4c87-be02-77b84abb9d76)

## **Component List**

1. **Seeeduino XIAO**  
   * Description: A compact microcontroller board based on the SAMD21 microcontroller.  
   * Pins: A0 \- D0 \- DAC, A1 \- D1, A2 \- D2, A3 \- D3, A4 \- D4 \- SDA, A5 \- D5 \- SCL, A6 \- D6 \- TX, 5V, GND, 3V3, A10 \- D10 \- MOSI, A9 \- D9 \- MISO, A8 \- D8 \- SCK, A7 \- D7 \- RX  
2. **MCP23S17**  
   * Description: A 16-bit I/O expander with SPI interface.  
   * Pins: GPB0, GPB1, GPB2, GPB3, GPB4, GPB5, GPB6, GPB7, A1, A0, SO, SI, CS, VSS, VDD, INTA, INTB, RESET, A2, GPA1, GPA0, GPA5, GPA4, GPA3, GPA2, GPA7, GPA6, SCK  
3. **ULN2803 Darlington Array (2 units)**  
   * Description: A high-voltage, high-current Darlington transistor array.  
   * Pins: I1, I2, I3, I4, I5, I6, I7, I8, O3, O4, O5, O6, O7, O8, GND, COMMON, O1, O2  
4. **COIN VIBRATION MOTOR (7 units)**  
   * Description: A small motor that provides vibration feedback.  
   * Pins: \+, \-  
5. **TPS63031**  
   * Description: A high-efficiency, low-power buck-boost converter.  
   * Pins: VIN, NC, GND, OUT  
6. **18650 Battery (2 units)**  
   * Description: A rechargeable lithium-ion battery.  
   * Pins: \+, \-  
7. **BNO085**  
   * Description: A 9-axis sensor with accelerometer, gyroscope, and magnetometer.  
   * Pins: VCC, GND, SCL/SCK/RX, SDA/MISO/TX, ADR/MOSI, CS, INT, RST, PS1, PS0  
8. **Push Button**  
   * Description: A simple push button for user input.  
   * Pins: pin1, pin2  
9. **Potentiometer Piher 10mm**  
   * Description: A variable resistor for adjusting resistance.  
   * Pins: A, Variable, B

## **Wiring Details**

### **Seeeduino XIAO**

* **A0 \- D0 \- DAC**: Connected to MCP23S17 CS  
* **A8 \- D8 \- SCK**: Connected to MCP23S17 SCK  
* **A10 \- D10 \- MOSI**: Connected to MCP23S17 SI  
* **A9 \- D9 \- MISO**: Connected to MCP23S17 SO  
* **A6 \- D6 \- TX**: Connected to Push Button pin2  
* **A3 \- D3**: Connected to Potentiometer Piher 10mm Variable  
* **A5 \- D5 \- SCL**: Connected to BNO085 SCL/SCK/RX  
* **A4 \- D4 \- SDA**: Connected to BNO085 SDA/MISO/TX  
* **A7 \- D7 \- RX**: Connected to MCP23S17 VDD  
* **3V3**: Connected to BNO085 VCC, ADR/MOSI, Potentiometer Piher 10mm B, TPS63031 OUT  
* **GND**: Connected to BNO085 GND, Push Button pin1, 18650 \-, ULN2803 Darlington Array GND, Potentiometer Piher 10mm A, TPS63031 GND, MCP23S17 VSS, A2, A1, A0

### **MCP23S17**

* **GPA7**: Connected to ULN2803 Darlington Array I1  
* **GPA6**: Connected to ULN2803 Darlington Array I2  
* **GPA5**: Connected to ULN2803 Darlington Array I3  
* **GPA4**: Connected to ULN2803 Darlington Array I4  
* **GPA3**: Connected to ULN2803 Darlington Array I5  
* **GPA2**: Connected to ULN2803 Darlington Array I6  
* **GPA1**: Connected to ULN2803 Darlington Array I7  
* **GPA0**: Connected to ULN2803 Darlington Array I8  
* **GPB7**: Connected to ULN2803 Darlington Array I1 (second unit)  
* **GPB6**: Connected to ULN2803 Darlington Array I2 (second unit)  
* **GPB5**: Connected to ULN2803 Darlington Array I3 (second unit)  
* **GPB4**: Connected to ULN2803 Darlington Array I4 (second unit)  
* **GPB3**: Connected to ULN2803 Darlington Array I5 (second unit)  
* **GPB2**: Connected to ULN2803 Darlington Array I6 (second unit)  
* **GPB1**: Connected to ULN2803 Darlington Array I7 (second unit)  
* **GPB0**: Connected to ULN2803 Darlington Array I8 (second unit)

### **ULN2803 Darlington Array**

* **O1**: Connected to COIN VIBRATION MOTOR \- (first unit)  
* **O2**: Connected to COIN VIBRATION MOTOR \- (second unit)  
* **O3**: Connected to COIN VIBRATION MOTOR \- (third unit)  
* **O8**: Connected to COIN VIBRATION MOTOR \- (fourth unit)  
* **O7**: Connected to COIN VIBRATION MOTOR \- (fifth unit)  
* **O6**: Connected to COIN VIBRATION MOTOR \- (sixth unit)

### **COIN VIBRATION MOTOR**

* **\+**: Connected to 18650 \+ (first unit)  
* **\+**: Connected to 18650 \+ (second unit)  
* **\+**: Connected to 18650 \+ (third unit)  
* **\+**: Connected to 18650 \+ (fourth unit)  
* **\+**: Connected to 18650 \+ (fifth unit)  
* **\+**: Connected to 18650 \+ (sixth unit)  
* **\+**: Connected to 18650 \+ (seventh unit)

### **TPS63031**

* **VIN**: Connected to 18650 \+  
* **OUT**: Connected to Seeeduino XIAO 3V3

### **18650 Battery**

* **\-**: Connected to GND net  
* **\+**: Connected to COIN VIBRATION MOTOR \+, TPS63031 VIN

### **BNO085**

* **VCC**: Connected to Seeeduino XIAO 3V3  
* **GND**: Connected to GND net  
* **SCL/SCK/RX**: Connected to Seeeduino XIAO A5 \- D5 \- SCL  
* **SDA/MISO/TX**: Connected to Seeeduino XIAO A4 \- D4 \- SDA

### **Push Button**

* **pin1**: Connected to GND net  
* **pin2**: Connected to Seeeduino XIAO A6 \- D6 \- TX

### **Potentiometer Piher 10mm**

* **A**: Connected to GND net  
* **Variable**: Connected to Seeeduino XIAO A3 \- D3  
* **B**: Connected to Seeeduino XIAO 3V3

## **Code Documentation**

There is no embedded code provided for this circuit. The microcontroller and other programmable components are not configured with any specific code in this documentation.





## Software Overview

### Environment

* Platform: Arduino
* Board: Seeeduino XIAO (SAMD21)
* Libraries used:

  * `SPI`
  * (BNO085 sensor library as required)

---

### Code Functionality

* Initializes SPI communication with MCP23S17
* Configures MCP23S17 GPIO pins as outputs
* Reads orientation data from BNO085 via I2C
* Calculates heading and maps it to one of 16 vibrators positions
* Activates the corresponding vibrators

Current test behavior:

* GPIOA pins are toggled to create a blinking vibrators pattern

---

## Future Improvements

* Improve enclosure and wearable integration
* Develop a mobile app for configuration via Bluetooth.
* 3D printed box for the electronics

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

