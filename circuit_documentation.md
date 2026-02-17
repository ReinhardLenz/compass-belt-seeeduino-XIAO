# **Circuit Documentation**

## **Summary**

This circuit is a complex embedded system that integrates a variety of components, including a microcontroller, a port expander, a Darlington array, vibration motors, a power management IC, a battery, a sensor, a push button, and a potentiometer. The circuit is designed to control multiple vibration motors using a microcontroller and a port expander, with power supplied by a battery and regulated by a power management IC. The system also includes a sensor for additional functionality and a potentiometer for user input.

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