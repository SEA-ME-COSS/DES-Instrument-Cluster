# **DES Project - Instrument Cluster**

---

# Result

<img src="https://github.com/SEA-ME-COSS/DES-Instrument-Cluster/blob/main/Images/final_result.gif" alt="Alt text" width="100%" height="100%"/>

# Introduction

This repo is the final version of a project to create a vehicle instrument cluster for embedded use on Raspberry Pi.

By connecting the Arduino and the speed sensor, the speed information of the vehicle was obtained and transferred to the Raspberry Pi through CAN. Then, a multi-thread was implemented using a total of two threads: one thread that reads the data and one thread that puts the read data into dbus, and put the information into dbus. Finally, the project was completed by transferring the Qt Instrument cluster compiled to the architecture of the Raspberry Pi by cross-compilation to the Raspberry Pi.

Through this project, you are able to have a practical understanding of IPC, and you can understand the overall concept of embedded.

# Architecture

<img src="https://github.com/SEA-ME-COSS/DES-Instrument-Cluster/blob/main/Images/software aritecture.png" alt="Alt text" width="120%" height="120%"/>

# Setting

## Requirements

Detailed setting-related information is in the setting folder. If you follow the contents, you can start with the setting we did.

Below are the hardware specs we used.

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

Just run run_dashboard.sh implemented in the parent folder of this folder.

```bash
sh run_dashboard.sh
```

**If you are curious about how we proceeded with this project, we recommend that you read the repo in the order below.**

1. [Arduino CAN communication](https://github.com/dongdongO/SEA-ME_Embedded/blob/main/DES_Instrument-Cluster/arduino_can)
2. [RaspberryPi CAN communication](https://github.com/dongdongO/SEA-ME_Embedded/blob/main/DES_Instrument-Cluster/raspberrypi_can)
3. [DBus tutorial](https://github.com/dongdongO/SEA-ME_Embedded/blob/main/DES_Instrument-Cluster/dbus_tutorial)
4. [DBus with Qt](https://github.com/dongdongO/SEA-ME_Embedded/blob/main/DES_Instrument-Cluster/dbus_Qt)
5. [Instrument Cluster](https://github.com/dongdongO/SEA-ME_Embedded/blob/main/DES_Instrument-Cluster/Instrument-Cluster)

**If you just want to see the final project results, you can look at Instrument Cluster.**

# Technical Requirements

1. Raspberry Pi: The Raspberry Pi is a small, low-cost, single-board computer that is ideal for developing and testing embedded applications. A Raspberry Pi 3 Model B or later is recommended for this project, as it provides sufficient processing power and memory for running the instrument cluster application and receiving data from the speed sensor via CAN.
2. Qt Creator and the Qt libraries for Raspberry Pi: Qt Creator is a powerful, cross-platform integrated development environment (IDE) for developing applications with the Qt framework. The Qt libraries for Raspberry Pi include all of the necessary components for building Qt applications for the Raspberry Pi.
3. CAN bus interface: A CAN bus interface is required for connecting the Raspberry Pi to the vehicle's CAN bus and receiving speed data from the speed sensor. Suitable CAN bus interfaces for the Raspberry Pi include the MCP2515 and the TJA1050.
4. Speed sensor: A speed sensor capable of transmitting speed data via CAN is required for this project. The type of speed sensor required will depend on the vehicle being used for testing.
5. OBD-II cable: An OBD-II cable is required for connecting the Raspberry Pi and the speed sensor to the vehicle's CAN bus. This cable provides a convenient and reliable way to tap into the vehicle's CAN bus and receive data from the speed sensor.
6. Voltage regulator: A 12V to 5V voltage regulator is required for powering the Raspberry Pi from the vehicle's electrical system. The voltage regulator ensures that the Raspberry Pi receives a stable, regulated power supply, even when the vehicle's electrical system voltage fluctuates.
7. Display: A display is required for the instrument cluster application. Suitable displays include LCD and OLED displays, and the size and resolution of the display will depend on the specific requirements of the instrument cluster application.
8. Mounting hardware: A suitable method of mounting the display and Raspberry Pi in the vehicle is required. This may involve mounting brackets, enclosures, or other hardware, depending on the specific requirements of the instrument cluster application.
9. Vehicle for testing: Access to a vehicle for testing the instrument cluster application is required. The vehicle should have a CAN bus system and should be compatible with the speed sensor and other hardware components.

The students will be responsible for sourcing all of the required hardware components and ensuring that the hardware is compatible with the Raspberry Pi and the CAN bus interface. They will also be responsible for installing and configuring the operating system, the Qt framework, and any necessary drivers or libraries. The students will need to write and test the instrument cluster application, including the user interface, data processing, and CAN communication code. They will also need to integrate the application with the hardware components and test the instrument cluster in a vehicle. Finally, the students will be expected to document their work and demonstrate the instrument cluster application in a final presentation. This project requires a solid understanding of software development and embedded systems, as well as the ability to work effectively in a team and to solve complex technical problems.

</br>

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

</br>

Shield:

!https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg

This work is licensed under a
[Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/).

!https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png