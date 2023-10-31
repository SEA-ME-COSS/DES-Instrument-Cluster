# **DES Project - Instrument Cluster**
PiRacer instrument cluster Qt application running on RPi and receiving speed data from a speed sensor via CAN  

---

# Result

<img src="../images/final_result.gif" alt="Alt text" width="100%" height="100%"/>

# Introduction
This repo is the final version of a project to create a vehicle instrument cluster for embedded use on Raspberry Pi.  

By connecting the Arduino and the speed sensor, the speed information of the vehicle was obtained and transferred to the Raspberry Pi through CAN. Then, a multi-thread was implemented using a total of two threads: one thread that reads the data and one thread that puts the read data into dbus, and put the information into dbus. Finally, the project was completed by transferring the Qt Instrument cluster compiled to the architecture of the Raspberry Pi by cross-compilation to the Raspberry Pi.  

Through this project, you are able to have a practical understanding of IPC, and you can understand the overall concept of embedded.

# Architecture


<img src="../images/software aritecture.png" alt="Alt text" width="120%" height="120%"/>

# Requirements

## Raspberry Pi 4B

- Raspberry Pi OS Lite 64bit (Linux 6.1 kernel)
- 2-Channel CAN-BUS(FD) Shield for Raspberry Pi (MCP2518FD)
- 7.9inch DSI LCD (400 x 1280, 60Hz)
- PiRacer AI Kit (PiRacer Standard)
- Joystick

## Arduino UNO

- CAN-BUS Shield V2.0 (MCP2515)
- Speed Sensor (LM393)

## Tools

- Qt Creator 4.15.0 (with qmake)
- Qt 5.15.0
- Ubuntu 20.04
- Arduino IDE
- Raspberry Pi Imager
- VI Editor

# Usage

After finishing the [setting](./setting/), just run run_dashboard.sh implemented in the [parent folder](../) of this folder.

```bash
sh run_dashboard.sh
```
