# **Raspberrypi4 - Arduino CAN**

# Result

<img src="https://github.com/dongdongO/SEA-ME_Embedded/blob/main/DES_Instrument-Cluster/Images/raspberrypican.png" alt="Alt text" width="60%" height="60%"/>
<br>  

# Introduction
CAN (Controller Area Network) is an advanced bus communication system, initially developed for automotive applications but has since become prevalent in various industrial applications. It facilitates robust and reliable communication among microcontrollers and devices without the need for a host computer.

This repository presents a seamless approach for connecting an Arduino with a Raspberry Pi 4 via CAN. This union of an immensely popular microcontroller and a versatile single-board computer extends the horizons for automation and data acquisition applications. Through the meticulous steps laid out here, both newcomers to CAN and seasoned developers will find a clear path to integrating these devices and maximizing their joint potential. 
<br>  

# Project Goals
This project is a sequel to the foundational work in the arduino_can repository. Capitalizing on that groundwork, the primary objectives of this endeavor are:  

* **Understanding CAN Protocol:** Delve deeper into the intricacies of the CAN protocol. Highlight its reliability, scalability, and efficiency in managing device communications.
* **Hardware Setup:** Offer detailed, step-by-step instructions to align the Arduino and Raspberry Pi 4 for CAN interface. This includes wiring details, hardware considerations, and potential pitfalls to avoid.
* **Data Exchange:** Showcase real-world applications by transmitting and receiving vital metrics, such as speed data, between the Arduino and Raspberry Pi. It’s not just about connection, but meaningful data transfer.
* **Documentation:** Deliver a well-structured, clear, and illustrative documentation, ensuring that users ranging from novices to experts find the guide informative and easy to follow. This will also include troubleshooting tips and common FAQs.
<br>  

# Usage

Proceed with the settings according to the README file in the setting folder.

You can compile C++ code using g++ :
```bash
g++ CAN_socket_test.cpp -o CAN_socket_test
./CAN_socket_test
```
<br>  

# Reference

- [RaspberryPi CAN](https://forums.raspberrypi.com/viewtopic.php?t=296117)
- [CAN Software Setting](https://www.waveshare.com/wiki/2-CH_CAN_HAT)
- [Speed Sensor](https://srituhobby.com/ir-infrared-speed-sensor-with-arduino-how-does-work-ir-speed-sensor/)
