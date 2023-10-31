# **CAN with Arduino**

---

# Introduction

This document outlines the experiments conducted by our team, utilizing the Controller Area Network (CAN) communication protocol for data exchange between two Arduino boards. The CAN protocol is widely used in automobiles, robotics, embedded systems, and more, offering high reliability, efficiency, and flexibility, making it a standard in various application fields.

Our team has set a goal to leverage these capabilities of the CAN communication in applying it for communication between Raspberry Pi and Arduino. However, before implementing such communication protocol, we first tested whether CAN communication between Arduinos is successfully achieved.

This document details the process and results of such testing, so that you will gain a basic understanding of how to implement CAN communication between Arduinos and learn how to execute actual communication scenarios.

# Project Goals

The primary aim of our project is to maximize the capabilities of the Controller Area Network (CAN) communication protocol to enable effective communication between Arduino boards.

Here are the specific objectives of the project:

- To understand the intricacies of the CAN protocol and how it facilitates real-time data transmission in various systems.
- To conduct a successful pilot test of CAN communication between two Arduino boards, ensuring the efficient exchange of data between them.
- To apply the knowledge and results obtained from the Arduino-Arduino CAN communication testing to implement effective communication between Arduino boards.
- To ensure the Arduino-Arduino communication via CAN is efficient, reliable, and meets the needs of the desired applications.
- To document all the processes, experiments, results, and conclusions comprehensively, providing a robust guide for future endeavors involving the CAN protocol.

By accomplishing these objectives, the project will not only verify the efficacy of CAN communication between Arduino boards but also provide a practical guide on how to implement efficient communication between Arduino boards using the CAN protocol.

# Usage

Proceed with the settings according to the [README file](./setting/) in the setting folder.

Additionally, if you want to communicate data from the speed sensor, please use the 'speedwrite' and 'speedread' codes.

Be sure to check which CS pin you are using. You need to replace the numbers in the code below according to your pin number.

```bash
MCP2515 mcp2515(10);
```

Also, both CANs must have the same speed and HZ. Check the information in the code below

```bash
mcp2515.setBitrate(CAN_500KBPS, MCP_16MHZ);
```

# References

- [arduino-mcp2515](https://github.com/autowp/arduino-mcp2515.git)
- [Waveshare LCD1602](https://www.waveshare.com/wiki/LCD1602_RGB_Module)
