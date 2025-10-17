# Bike Sensors Logger

This project aims to get as much information as possible from the bike via the vehicle's OBD2 port, extended with the data of other sensors, like GPS (for geolocation and time), accelerometer, gyroscope, magnometer and possiblty others, saving the information in a microSD.

## License

Hardware is licensed under the CERN Open Hardware License "Strongly Reciprocal" (CERN-OHL-S) v2.0.

Software is licensed under the GNU General Public License v3.0.

## Repository folders

- schematics: PCB design, using the KiCAD open source software
- firmware: the microcontroller's firmware
- software:
  - tools: PC tools to extract the data from the microSD

## Hardware's high level design

### Inputs

- OBD II port: used to get 12V power and the bike's data.
- GNSS (Global Navigation Satellite System) antenna: to get the GNSS signal, and thus the position and the time. Can be active (3.3V) or passive.

### Main components, to target release v1.0

- Arduino Nano R4: microcontroller to manage the logics.
- The OBD II port: power and some of the data (speed, engine's rpm, throttle).
- The OBD II transreceiver: to connect the OBD II port to the Arduino microcontroller.
- GPS module: to get geolocation and time.
- Accelerometer / gyroscope.
- microSD slot: to save the data.

### Future enhancements

- Magnometer
- Bluetooth, to provide the GPS signal to some action cams that support external GPS devices, and thus easily synchronize video and data

### What has been done so far

| Project component | Component            | Current state  | Notes |
| ----------------- | -------------------- | -------------- | ----- |
| PCB Schematic     | 12V to 5V/3.3V buck  | To be reviewed | To power the microprocessor (Arduino) and the various sensors. |
| PCB Schematic     | Accel - Gyro         | To be reviewed | LSM6DSOXTR based accelerometer + gyroscope with embedded ML capabilities in MODE 1 "Stand alone", connected via I2C. Direct I2C connection to Arduino is possible thanks to the microprocessor's integrated I2C level translation. |
| PCB Schematic     | GNSS                 | To be reviewed | GNSS module powered by TESEO-LIV3R chip and an external antenna. The external antenna can be either active (3.3V) or passive. The antenna is connected via a MMCX connector and can be powered if active via a switch. The module provides ANT_PWR to hint the state of the switch, and it's connected to a status LED. |
| PCB Schematic     | OBD II Transreceiver | To be reviewed | CAN bus transreceiver to talk with the OBD II's CAN data interface. Enhanced with a CAN_H / CAN_L termination check and automatic application if required during startup phase. |
| PCB Schematic     | Micro SD             | To be reviewed | Micro SD slot connected to Arduino. |

### Known problems or TODO list

- The GNSS chip should be also powered by a 3.3V battery to let the internal clock continue ticking. It requires either a CR2032 battery (easier), or a rechargeable solution (more robust).

## Changelog

### Dev 5

- Added I2C level shifters
- Added I2C pull-up resistors
- Added pull-up resistor to accel-gyro's CS pin to (always) enable I2C communication
- Removed typo short-circuit connection between 5-to-3.3V buck FB and VI pins

### Dev 4

- Added Micro SD port
- Added double buck step-down converter to support 3V3 current circuit requirements


### Dev 3

- Added OBD II port + relative transreceiver and connections between the two and the microcontroller.

### Dev 2

- Added GNSS (GPS, GLONASS, Galileo, Beidu) module

### Dev 1

- Removed 5V to 3.3V buck, using Arduino Nano R4's 3V3 pin instead (schematic is being kept for possible future use).
- Added LSM6DSOXTR accelerometer / gyroscope in MODE 1 (standalone) connected via I2C
