# Bike Sensors Logger

This project aims to get as much information as possible from the bike via the vehicle's OBD2 port, extended with the data of other sensors, like GPS (for geolocation and time), accelerometer, gyroscope, magnometer and possiblty others, saving the information in a microSD.

## License

Hardware is licensed under the CERN Open Hardware License "Strongly Reciprocal" (CERN-OHL-S) v2.0.

Software is licensed under the GNU General Public License v3.0.

## Repository folders

- schematics: PCB design, using the KiCAD open source software
- software
  - microcontroller: the hardware's firmware
  - tools: PC tools to extract the data from the microSD

## Hardware's high level design

- Inputs

The box only has one input: the OBD2 port. It uses the 12V pins to power itself, with an estimated maximum consumption of <500 mA.

Main components, to target release v1.0:
- [ ] The OBD2 port: power and some of the data (speed, engine's rpm, throttle)
- [ ] Arduino Nano R4: microcontroller to manage the logics
- [ ] GPS module: to get geolocation and time
- [ ] Accelerometer / gyroscope
- [ ] microSD slot: to save the data

Future enhancements:
- [ ] Magnometer
- [ ] Bluetooth, to provide the GPS signal to some action cams that support external GPS devices, and thus easily synchronize video and data

## Changelog

What has been done so far:

| Project component | Component       | Current state  | Notes |
| ----------------- | --------------- | -------------- | ----- |
| PCB Schematic     | 12V to 5V buck  | To be reviewed | To power the microprocessor (Arduino) |
| PCB Schematic     | 5V to 3.3V buck | To be reviewed | To power most of the sensors. Preferred over a linear dropout regulator due to lower overheating and possibly bad ventilation |
