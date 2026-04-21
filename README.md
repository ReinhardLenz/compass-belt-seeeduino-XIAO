# Compass Belt (Seeeduino XIAO + MCP23S17)

![Diagram](images/01_eksynyt_nainen.png)


![Diagram](02_itse_keltainen_vyo.jpg)



## Overview

This repository contains a **Compass belt application** that drives **16 vibration motors arranged in a circular layout**. The motor pointing toward **magnetic north** is vibrating, creating a simple and intuitive directional indicator.

This project is a **compact evolution of an earlier compass belt design** that was based on an **Arduino Mega 2560**. By switching to a **Seeeduino XIAO** combined with an **MCP23S17 I/O expander**, and  the overall size and wiring complexity are significantly reduced while still supporting 16 vibrators. The vibration motors are powered by **ULN2803** Darlington arrays to provide sufficient current, as the **Seeeduino XIAO** alone can't supply enough. The vibration motors draw their power from **18650** battery, while the **Seeeduino XIAO** controls the logic.

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

This circuit integrates a microcontroller, a port expander, a Darlington array, vibration motors, a power management IC, a battery, an Inertial measurement sensor, a push button, and a potentiometer. The circuit controls multiple vibration motors using a microcontroller and a port expander, with power supplied by a battery and regulated by a power management IC. The system core is an inertial measurement sensor to detect the orientation in earth magnet field, and a pushbutton and potentiometer for user input.


## **Circuit diagram**

![Diagram](03_circuit_image.png)


## **Demonstation video link**

[![Demo video](https://img.youtube.com/vi/urYNUAdMZ-0/0.jpg)](https://www.youtube.com/watch?v=urYNUAdMZ-0)

## **Photo of breadboard**
note, that in the photo  there are no motors but LED's instead, these are better for testing. 

![Diagram](04_breadboard_LED.jpg)


## **Photo of compass belt**

He marked positions on the elastic belt in such a way that he didn't make extra pockets for the vibration motors, but wrapped the elastic band around the cylindrical motor like a loop, so that it formed a pocket and then sewed the seam closed, from the side and bottom. Before he did anything else, he pushed the yellow silicone sleeves over the motor's output wires. Then he first soldered the "plus" red terminals of all the motors together with pieces of red wire. He stripped the ends of the wire pieces with that stripping tool, and this tool really speeds up the job. He attach the ends of the wires to the work table with blu-tack. First he soldered two red pieces of wire together, and then attached this connection point to the motor wire. He cut the silicone ribbon cable. In it, the wires of the flat cable have to be separated and cut off in stages and separately. The wire going to the last motor is the longest, the second to last motor branches 6cm before it, the third to last motor branches 12cm before the last one and so on, until all the branch points have been separated at 6cm intervals. There are 16 motors in total, the first 8 motors are powered by the first 8-wire flat cable and the next ones by a second flat cable, which forms itself as if it were the counterpart of the first flat cable; it is basically a mirror image of the first cable, the only difference is that it is 8 * 6 = 48 cm longer, because the next 8 motors are this distance further away from the control unit. Next, he also stripped the ends of the flat cable wires. He put silicone glue on all the soldering points, and pulled silicone sleeves over it, and that way he sealed the soldering point from mechanical bending stress. The solder points itself are fragile and does not withstand the constant bending very well when the belt actually goes around the body.

![Diagram](06_vyö_ilman_sukkahousuja.jpg)


## **box for the electronics**

![Diagram](07_elektroniikka_laatikko_NX.png)


## **link to the 3D printable parts for the box**

http://raikkulenz.kapsi.fi/downloadfolder_not_protected/stl_kotelo.zip

## **link to picture of 3D printable parts for the box**

http://raikkulenz.kapsi.fi/downloadfolder_not_protected/tulostettavat_osat.pdf

## **wiring scheme inside the box**

![Diagram](08_isometrinen_johdotuskaavio.png)


## **component placement inside the box**


![Diagram](09_elektroniikkalaatikko_sisakalut.jpg)


The potentiometer, the push button and the flip switch are mounted in holes, and are screwed to the wall. The IMU sensor is hold in a bracket on the side, kept horizontally. The base plate and the battery compartment are glued in place with flexible epoxi or silicone mass.

# **Circuit Documentation**

## **Summary**

This circuit is a Seeeduino XIAO microcontroller, an MCP23S17 I/O expander, 2 pcs ULN2803 Darlington Arrays, 16 coin vibration motors, a BNO085 sensor, a TPS63031 power management IC, two 18650 batteries, a potentiometer, a push button, and an ON OFF switch. The circuit is designed to control multiple vibration motors using the I/O expander and Darlington arrays, with power management and sensor integration for enhanced functionality.

## **Component List**

### shopping basket

https://linktr.ee/compassbelt

All necessary component a link to more detailed component.

1. **Seeeduino XIAO**  
   * Description: A compact microcontroller board based on the SAMD21G18 chip.  
   * Pins: A0 \- D0 \- DAC, A1 \- D1, A2 \- D2, A3 \- D3, A4 \- D4 \- SDA, A5 \- D5 \- SCL, A6 \- D6 \- TX, 5V, GND, 3V3, A10 \- D10 \- MOSI, A9 \- D9 \- MISO, A8 \- D8 \- SCK, A7 \- D7 \- RX

![Diagram](10_Seeeduino_XIAO_pinnien_merkitykset.jpg)


2. **MCP23S17**  
   * Description: 16-bit I/O expander with SPI interface.  
   * Pins: GPB0, GPB1, GPB2, GPB3, GPB4, GPB5, GPB6, GPB7, A1, A0, SO, SI, CS, VSS, VDD, INTA, INTB, RESET, A2, GPA1, GPA0, GPA5, GPA4, GPA3, GPA2, GPA7, GPA6, SCK

![Diagram](11_MCP23S17_pinnien_merkitykset.jpg)

   
4. **ULN2803 Darlington Array (2 units)**  
   * Description: High-voltage, high-current Darlington transistor arrays.  
   * Pins: I1, I2, I3, I4, I5, I6, I7, I8, O3, O4, O5, O6, O7, O8, GND, COMMON, O1, O2

![Diagram](12_ULN2803_pinnien_merkitykset.png)

   
6. **COIN VIBRATION MOTOR (14 units)**  
   * Description: Small DC motors used for vibration feedback.  
   * Pins: \+, \-  
7. **TPS63031**  
   * Description: High-efficiency, low-power buck-boost converter.  
   * Pins: VIN, NC, GND, OUT

![Diagram](13_TPS63031_pinnien_merkitykset.png)



8. **18650 Battery (1 units)**  
   * Description: Rechargeable lithium-ion battery.  
   * Pins: \+, \-  
9. **BNO085**  
   * Description: 9-axis absolute orientation sensor.  
   * Pins: VCC, GND, SCL/SCK/RX, SDA/MISO/TX, ADR/MOSI, CS, INT, RST, PS1, PS0

![Diagram](14_BNO085_pinnien_merkitykset.png)



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

* **3V3** is connected to the positive terminals of multiple coin vibration motors, the VCC and ADR/MOSI pins of the BNO085, the COMMON pins of both ULN2803 arrays, the B pin of the potentiometer, and the VDD pin of the MCP23S17.  
* **GND** is connected to the negative terminal of the 18650 battery, the GND pin of the BNO085, pin1 of the push button, the A pin of the potentiometer, the GND pins of both ULN2803 arrays, and the VSS, A2, A1, and A0 pins of the MCP23S17.  
* **A7 \- D7 \- RX** is connected to the CS pin of the MCP23S17.  
* **A8 \- D8 \- SCK** is connected to the SCK pin of the MCP23S17.  
* **A10 \- D10 \- MOSI** is connected to the SI pin of the MCP23S17.  
* **A9 \- D9 \- MISO** is connected to the SO pin of the MCP23S17.  
* **A2 \- D2** is connected to the Variable pin of the potentiometer.  
* **A6 \- D6 \- TX** is connected to pin2 of the push button.  
* **A5 \- D5 \- SCL** is connected to the SCL/SCK/RX pin of the BNO085.  
* **A4 \- D4 \- SDA** is connected to the SDA/MISO/TX pin of the BNO085.

### **MCP23S17**

* **GPA7 to GPA0** are connected to the I1 to I8 pins of the first ULN2803 Darlington Array.  
* **GPB7 to GPB0** are connected to the I1 to I8 pins of the second ULN2803 Darlington Array.

### **ULN2803 Darlington Array**

* **O1 to O8** of the first array are connected to the negative terminals of various coin vibration motors.  
* **O1 to O8** of the second array are connected to the negative terminals of other coin vibration motors.

### **TPS63031**

* **VIN** is connected to pin 2 of the SPDT switch.  
* **OUT** is connected to the 3V3 net.

### **18650 Battery**

* **\+** is connected to the C pin of the SPDT switch.  
* **\-** is connected to the GND net.

### **SPDT Switch**

* **1** is not connected.  
* **C** is connected to the positive terminal of the 18650 battery.  
* **2** is connected to the VIN pin of the TPS63031.

### **BNO085**

* **VCC** and **ADR/MOSI** are connected to the 3V3 net.  
* **GND** is connected to the GND net.  
* **SCL/SCK/RX** is connected to the A5 \- D5 \- SCL pin of the Seeeduino XIAO.  
* **SDA/MISO/TX** is connected to the A4 \- D4 \- SDA pin of the Seeeduino XIAO.

### **Push Button**

* **pin1** is connected to the GND net.  
* **pin2** is connected to the A6 \- D6 \- TX pin of the Seeeduino XIAO.

### **Potentiometer Piher 10mm**

* **A** is connected to the GND net.  
* **Variable** is connected to the A2 \- D2 pin of the Seeeduino XIAO.  
* **B** is connected to the 3V3 net.

### **Coin Vibration Motors**

* **\+** terminals are connected to the 3V3 net.  
* **\-** terminals are connected to the O1 to O8 pins of the ULN2803 Darlington Arrays.



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

