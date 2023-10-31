# **DES Project - Instrument Cluster**

---

# Result

<img src="./images/final_result.gif" alt="Alt text" width="100%" height="100%"/>

# Introduction

This repo is the final version of a project to create a vehicle instrument cluster for embedded use on Raspberry Pi.

By connecting the arduino and the speed sensor, the speed information of the vehicle was obtained and transferred to the raspberrypi through CAN. Then, a multi-thread was implemented using a total of two threads: one thread that reads the data and one thread that puts the read data into dbus, and put the information into dbus. Finally, the project was completed by transferring the Qt instrument cluster compiled to the architecture of the raspberrypi by cross-compilation to the raspberrypi.

Through this project, you are able to have a practical understanding of IPC, and you can understand the overall concept of embedded.

# Architecture

<img src="./images/software aritecture.png" alt="Alt text" width="120%" height="120%"/>

# Setting

## Requirements

Detailed setting-related information is in the [setting folder](./Instrument-Cluster/setting). If you follow the contents, you can start with the setting we did.

Below are the hardware and software specs we used.

### Raspberry Pi 4B

- Raspberry Pi OS Lite 64bit (Linux 6.1 kernel)
- 2-Channel CAN-BUS(FD) Shield for Raspberry Pi (MCP2518FD)
- 7.9inch DSI LCD (400 x 1280, 60Hz)
- PiRacer AI Kit (PiRacer Standard)
- Joystick

### Arduino UNO

- CAN-BUS Shield V2.0 (MCP2515)
- Speed Sensor (LM393)

### Tools

- Qt Creator 4.15.0 (with qmake)
- Qt 5.15.0
- Ubuntu 20.04
- Arduino IDE
- Raspberry Pi Imager
- VI Editor

# Usage

After finishing the [setting](./Instrument-Cluster/setting), just run run_dashboard.sh implemented in the parent folder of this folder.

```bash
sh run_dashboard.shß
```

**All information about this project is in ['Instrument-Cluster'](./Instrument-Cluster/).**

**However, if you would like to learn more about our development process, please follow the steps below.**


1. [Arduino CAN communication](./arduino_can/)
2. [RaspberryPi CAN communication](./raspberrypi_can/)
3. [DBus tutorial](./dbus_tutorial/)
4. [DBus with Qt](./dbus_Qt/)
5. [Instrument Cluster](./Instrument-Cluster/)

# References

1. Embedded Systems Design with the Raspberry Pi, by Muhammed Ali, Packt Publishing (2017)
2. The Qt Company (2021). Qt 5.15.0 Reference Documentation. Available at: https://doc.qt.io/qt-5/index.html
3. Bosch, R. (2016). Automotive Handbook (9th edition). Springer.
4. SAE International (2018). J1939 Digital Annex Document, Society of Automotive Engineers, Warrendale, PA.
5. CAN in Automation (CiA) e.V. (2017). CAN FD Specification Version 1.0.
6. K. Mäntylä, T. Mäntylä (2008). “Requirements Engineering Processes in the Automotive Domain.” Journal of Systems and Software, vol. 81, no. 11, pp. 19-29.
7. H. Elmqvist, B. Englund (2010). “Qt Quick and QML for N950”. Available at: https://www.slideshare.net/QtDevelopment/qt-quick-and-qml-for-n950
8. Raspberry Pi Foundation (2021). Raspberry Pi Hardware Reference. Available at: https://www.raspberrypi.org/documentation/hardware/raspberrypi/
9. R. Davis (2016). “Agile Estimating and Planning”. Prentice Hall.
10. I. Sommerville (2011). “Software Engineering”. Addison-Wesley.
<br/>  

Shield: [![CC BY-NC-SA 4.0][cc-by-nc-sa-shield]][cc-by-nc-sa]

This work is licensed under a
[Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License][cc-by-nc-sa].

[![CC BY-NC-SA 4.0][cc-by-nc-sa-image]][cc-by-nc-sa]

[cc-by-nc-sa]: http://creativecommons.org/licenses/by-nc-sa/4.0/
[cc-by-nc-sa-image]: https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png
[cc-by-nc-sa-shield]: https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg