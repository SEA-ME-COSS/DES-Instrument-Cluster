# Setting

---

# PiRacer Hardware & Software Setting Guide

This document provides a guide to basic setup and configuration of PiRacer’s hardware and software. All contents of this project have been tested in an environment based on the components specified below.

# Requirements

Before starting this guide, you will need the following components:

1. PiRacer AI Kit (PiRacer Standard)
2. Raspberry Pi 4B
3. 2-Channel CAN-BUS(FD) Shield for Raspberry Pi (MCP2518FD)
4. Arduino UNO
5. CAN-BUS Shield V2.0 (MCP2515)
6. 7.9inch DSI LCD (400 x 1280, 60Hz)
7. Speed Sensor (LM393)

# Hardware Setting

1. To assemble the PiRacer's main body, check this [GitHub page]() for the detailed assembly process. You can also refer to the following official [waveshare guide](https://www.waveshare.com/wiki/PiRacer_Assembly_Manual).
2. Install the CAN-BUS shield on top of the Raspberry Pi and the LCD at the bottom. The wires of PiRacer's camera and LCD must be connected to the body of Raspberry Pi. Fix the LCD screen to the PiRacer with the standoff part so that it faces upward.

<img src="https://github.com/dongdongO/SEA-ME_Embedded/blob/main/DES_Instrument-Cluster/Images/hardwaresetting1.jpeg" alt="Alt text" width="60%" height="60%"/>

3. Combine Arduino Uno and CAN-BUS Shield. Connect the CAN_H and CAN_L to the corresponding locations of the CAN-BUS shield on the Raspberry Pi, respectively.

<img src="https://github.com/dongdongO/SEA-ME_Embedded/blob/main/DES_Instrument-Cluster/Images/hardwaresetting2.jpeg" alt="Alt text" width="60%" height="60%"/>

4. Carefully refer to the picture and fix the speed sensor to the rear wheel of the PiRacer body. Fix the rotating part of the speed sensor so that it is engaged with the tire and rotates together. Frames used to assemble the speed sensor can be found in the components provided in the PiRacer kit.

<img src="https://github.com/dongdongO/SEA-ME_Embedded/blob/main/DES_Instrument-Cluster/Images/hardwaresetting3.jpeg" alt="Alt text" width="60%" height="60%"/>

5. Connect the Raspberry Pi to the piracer's servo using 6pin gpio and connect all the necessary wires. Check Raspberry Pi and piracer's GPIO map.

<img src="https://github.com/dongdongO/SEA-ME_Embedded/blob/main/DES_Instrument-Cluster/Images/hardwaresetting4.jpeg" alt="Alt text" width="60%" height="60%"/>

6. Finally, insert the Micro SD card into the Raspberry Pi to complete the assembly.

# Precautions

- All assembly procedures should be done with the power off to avoid electric shock.
- Please assemble the components with care. Incorrect assembly could damage the components.
- Please keep the components safe and turn off the power when not in use.

# Software Setting