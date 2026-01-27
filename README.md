# Compass Belt (Seeeduino XIAO + MCP23S17)

## Overview

This repository contains a **Compass application** that drives **16 LEDs arranged in a circular layout**. The LED pointing toward **magnetic north** is illuminated, creating a simple and intuitive directional indicator.

This project is a **compact evolution of an earlier compass belt design** that was based on an **Arduino Mega 2560**. By switching to a **Seeeduino XIAO** combined with an **MCP23S17 I/O expander**, the overall size and wiring complexity are significantly reduced while still supporting 16 LEDs.

> ⚠️ **Status**: Work in progress
>
> * Potentiometer for north offset calibration: **not yet implemented**
> * Push button for blinking-rate adjustment: **not yet implemented**
> * ULN2803 LED driver: **not yet included**
> * Circuit PNG exists but is **incomplete** (missing components listed above)

---

## Features

* 16 discrete LEDs arranged in a circle
* LED pointing to magnetic north lights up
* SPI-controlled I/O expansion using MCP23S17
* Absolute orientation sensing via BNO085 (I2C)
* Compact form factor using Seeeduino XIAO

Planned features:

* Adjustable north offset using a potentiometer
* User-selectable LED blinking rate via push button
* Improved LED driving using ULN2803

---

## Hardware Components

### 1. Seeeduino XIAO

**Description:** Compact microcontroller board based on the SAMD21.

**Relevant Pins:**

* A0 – D0 – DAC
* A1 – D1
* A2 – D2
* A3 – D3
* A4 – D4 – SDA (I2C)
* A5 – D5 – SCL (I2C)
* A6 – D6 – TX
* A7 – D7 – RX
* A8 – D8 – SCK (SPI)
* A9 – D9 – MISO (SPI)
* A10 – D10 – MOSI (SPI)
* 3V3, 5V, GND

---

### 2. MCP23S17

**Description:** 16-bit I/O expander with SPI interface.

**Pins Used:**

* GPA0–GPA7 (LED outputs)
* GPB0–GPB7 (LED outputs)
* SDA (SPI MOSI)
* SCK (SPI clock)
* VDD (3.3 V)
* VSS (GND)
* RESET
* A0, A1, A2 (address pins tied to GND)

---

### 3. BNO085

**Description:** 9-axis absolute orientation sensor.

**Pins Used:**

* VCC
* GND
* SCL / SCK / RX (I2C clock)
* SDA / MISO / TX (I2C data)
* ADR / MOSI (address select)

---

### 4. LEDs

**Type:** 2-pin green LEDs

* Anode connected to 3.3 V
* Cathode driven by MCP23S17 via resistor

### 5. Resistors

**Value:** 220 Ω

* One resistor per LED (16 total)

---

## Wiring Overview

<img width="1641" height="2322" alt="circuit_image_Seeeduino_XIAO_MCP23S17_BNO085" src="https://github.com/user-attachments/assets/1c1d9f80-74e1-4b26-8c21-7124b67dd187" />



### Power Distribution

* **3V3** → MCP23S17 VDD, MCP23S17 RESET, BNO085 VCC, BNO085 ADR/MOSI, all LED anodes
* **GND** → MCP23S17 VSS, MCP23S17 A0/A1/A2, BNO085 GND

---

### SPI Connections (XIAO ↔ MCP23S17)

* XIAO **A10 (MOSI)** → MCP23S17 **SDA**
* XIAO **A8 (SCK)** → MCP23S17 **SCK**
* XIAO **A9 (MISO)** → MCP23S17 **NC** (not used)

---

### I2C Connections (XIAO ↔ BNO085)

* XIAO **A5 (SCL)** → BNO085 **SCL/SCK/RX**
* XIAO **A4 (SDA)** → BNO085 **SDA/MISO/TX**

---

### LED Connections (via MCP23S17)

Each GPIO pin drives one LED cathode through a 220 Ω resistor:

* GPA0–GPA7 → LEDs 1–8
* GPB0–GPB7 → LEDs 9–16

LED anodes are tied to **3.3 V**.

---

## Circuit Diagram

A PNG schematic of the circuit is included in the repository.

> ⚠️ **Note:** The current schematic is incomplete.
> The following components are still missing and will be added later:
>
> * Potentiometer (north offset calibration)
> * Push button (blink rate control)
> * ULN2803 LED driver

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
* Calculates heading and maps it to one of 16 LED positions
* Activates the corresponding LED

Current test behavior:

* GPIOA pins are toggled to create a blinking LED pattern

---

## Future Improvements

* Add north offset calibration using a potentiometer
* Add push button to adjust blinking speed
* Introduce ULN2803 for improved LED current handling
* Finalize and update schematic
* Improve enclosure and wearable integration

---

## License

Specify your license here (e.g. MIT, GPL, CERN-OHL, etc.).

---

## Acknowledgements

* Seeed Studio – Seeeduino XIAO
* Microchip – MCP23S17
* Bosch / Hillcrest Labs – BNO085
