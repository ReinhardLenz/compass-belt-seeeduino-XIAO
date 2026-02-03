# Compass Belt (Seeeduino XIAO + MCP23S17)

## Overview

This repository contains a **Compass belt application** that drives **16 vibration motors arranged in a circular layout**. The motor pointing toward **magnetic north** is vibrating, creating a simple and intuitive directional indicator.

This project is a **compact evolution of an earlier compass belt design** that was based on an **Arduino Mega 2560**. By switching to a **Seeeduino XIAO** combined with an **MCP23S17 I/O expander**, and  the overall size and wiring complexity are significantly reduced while still supporting 16 vibrators. The vibration motors are powered by **ULN2803** Darlington arrays to provide sufficient current, as the **Seeeduino XIAO** alone can't supply enough. The vibration motors draw their power from **18650** batteries, while the **Seeeduino XIAO** controls the logic.

The circuit is a system that integrates a Seeeduino XIAO microcontroller, an MCP23S17 I/O expander, two ULN2803 Darlington Arrays, multiple coin vibration motors, a BNO085 sensor, a TPS63031 power management IC, and other components such as resistors, potentiometers, and push buttons. The circuit is designed to control multiple outputs, including vibration motors, and interfaces with sensors and other peripherals through I2C and SPI communication protocols. The power supply is managed by a TPS63031, which regulates the voltage from 18650 batteries.

---

## Features

* 16  Vibration motor arranged in a circle
* motor pointing to magnetic north vibrates
* SPI-controlled I/O expansion using MCP23S17
* Absolute orientation sensing via BNO085 (I2C)
* Compact form factor using Seeeduino XIAO

Planned features:

---

## Hardware Components

# 1. Seeeduino XIAO

Description: Compact microcontroller board based on the SAMD21G18.

Relevant Pins:

A0 – D0 – DAC (SPI CS)

A1 – D1

A2 – D2 (Potentiometer wiper)

A3 – D3 (Push button input)

A4 – D4 – SDA (I2C)

A5 – D5 – SCL (I2C)

A6 – D6 – TX

A7 – D7 – RX

A8 – D8 – SCK (SPI)

A9 – D9 – MISO (SPI)

A10 – D10 – MOSI (SPI)

3V3, 5V, GND

# 2. MCP23S17

Description: 16-bit I/O expander with SPI interface, used to control vibration motors via external drivers.

Pins Used:

GPA0–GPA7 → ULN2803 (unit 1 inputs)

GPB0–GPB7 → ULN2803 (unit 2 inputs)

SI, SO, SCK, CS (SPI)

VDD (3.3 V)

VSS (GND)

RESET

A0, A1, A2 (address pins tied to GND)

# 3. ULN2803 Darlington Array (2×)

Description: High-current Darlington transistor arrays used to drive vibration motors from a higher-voltage supply.

Inputs I1–I8 driven by MCP23S17 GPIOs

Outputs O1–O8 act as low-side switches

COMMON pins connected to motor supply for clamp diodes

GND connected to system ground

⚠️ Not all outputs have motors drawn in the schematic on purpose to reduce visual clutter.

# 4. Coin Vibration Motors

Description: Small DC vibration motors arranged conceptually in a circular layout.

Positive terminal connected to battery supply

Negative terminal switched by ULN2803 outputs

Currently drawn motors:

ULN2803 (unit 1): O6, O7, O8

ULN2803 (unit 2): O1, O2, O3

Remaining motors are intentionally omitted in the schematic but are electrically identical.

# 5. TPS63031

Description: High-efficiency single-inductor buck-boost converter for system power regulation.

VIN connected to 2×18650 battery pack

OUT provides regulated voltage for logic (3.3 V rail)

GND connected to system ground

# 6. 18650 Li-Ion Batteries (2×)

Description: Rechargeable lithium-ion cells connected in series.

Nominal motor voltage: ~7.4 V

Maximum voltage: ~8.2 V

Used directly for vibration motors

# 7. BNO085

Description: 9-axis absolute orientation sensor used for heading detection.

Connected via I2C

ADR/MOSI tied to 3.3 V

## Wiring Overview
<img width="1974" height="1374" alt="circuit_image_Seeeduino_XIAO_MCP23S17_BNO085_TPS63031" src="https://github.com/user-attachments/assets/29fa02c7-c036-4abd-bbf2-4c9207a3fb60" />



Wiring Details

# Seeeduino XIAO
•	3V3 is connected to:

o	BNO085 VCC

o	BNO085 ADR/MOSI

o	Push Button pin1

o	Potentiometer Piher 10mm B

o	TPS63031 OUT

o	MCP23S17 VDD



•	GND is connected to:

o	BNO085 GND

o	Resistor pin1

o	18650 Battery (-)

o	ULN2803 Darlington Array GND (both units)

o	Potentiometer Piher 10mm A

o	TPS63031 GND

o	MCP23S17 VSS, A2, A1, A0



•	A0 - D0 - DAC is connected to MCP23S17 CS


•	A8 - D8 - SCK is connected to MCP23S17 SCK


•	A10 - D10 - MOSI is connected to MCP23S17 SI


•	A9 - D9 - MISO is connected to MCP23S17 SO


•	A3 - D3 is connected to:

o	Resistor pin2

o	Push Button pin2



•	A2 - D2 is connected to Potentiometer Piher 10mm Variable


•	A5 - D5 - SCL is connected to BNO085 SCL/SCK/RX


•	A4 - D4 - SDA is connected to BNO085 SDA/MISO/TX


# MCP23S17

•	GPA7 is connected to ULN2803 Darlington Array I1 (first unit)

•	GPA6 is connected to ULN2803 Darlington Array I2 (first unit)

•	GPA5 is connected to ULN2803 Darlington Array I3 (first unit)

•	GPA4 is connected to ULN2803 Darlington Array I4 (first unit)

•	GPA3 is connected to ULN2803 Darlington Array I5 (first unit)

•	GPA2 is connected to ULN2803 Darlington Array I6 (first unit)

•	GPA1 is connected to ULN2803 Darlington Array I7 (first unit)

•	GPA0 is connected to ULN2803 Darlington Array I8 (first unit)

•	GPB7 is connected to ULN2803 Darlington Array I1 (second unit)

•	GPB6 is connected to ULN2803 Darlington Array I2 (second unit)

•	GPB5 is connected to ULN2803 Darlington Array I3 (second unit)

•	GPB4 is connected to ULN2803 Darlington Array I4 (second unit)

•	GPB3 is connected to ULN2803 Darlington Array I5 (second unit)

•	GPB2 is connected to ULN2803 Darlington Array I6 (second unit)

•	GPB1 is connected to ULN2803 Darlington Array I7 (second unit)

•	GPB0 is connected to ULN2803 Darlington Array I8 (second unit)

# ULN2803 Darlington Array (First Unit)

•	O1 is connected to COIN VIBRATION MOTOR (-) 

•	O2 is connected to COIN VIBRATION MOTOR 

...

•	O8 is connected to COIN VIBRATION MOTOR 



# ULN2803 Darlington Array (Second Unit)

•	O1 is connected to COIN VIBRATION MOTOR 

•	O2 is connected to COIN VIBRATION MOTOR

...

•	O8 is connected to COIN VIBRATION MOTOR 

# TPS63031

•	VIN is connected to:
o	18650 + 

•	GND is connected to:
o	18650 - 

•	VOUT is connected to:
o	Seeeduino XIAO 3V3 


# 	18650 Battery (+)

o	COIN VIBRATION MOTOR (+) (all instances)

o	ULN2803 Darlington Array COMMON (both units)

# 18650 Battery

•	- is connected to:
o	TPS63031 buck-boost converter

o	18650 Battery Documented Code
---

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

* Add north offset calibration using a potentiometer
* Add push button to adjust blinking speed
* Introduce ULN2803 for improved vibrators current handling
* Finalize and update schematic
* Improve enclosure and wearable integration

---

## License

GPL

---

## Acknowledgements

* Seeed Studio – Seeeduino XIAO
* Microchip – MCP23S17
* Bosch / Hillcrest Labs – BNO085
