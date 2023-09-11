# Setting

---

# Hardware Setting

## Requirements

- 2 Arduino boards (either Uno or Nano)
- 1 Arduino CAN shield
- 1 MCP2515 module (you can also prepare 2 if you don't use the Arduino CAN shield)
- Several jumper wires
- Speed sensor
- Waveshare lcd 1602 rgb
- 2 laptops

## Connect

Please refer to the above image and the Arduino's GPIO map for connections.

<img src="https://github.com/dongdongO/SEA-ME_Embedded/blob/main/DES_Instrument-Cluster/Images/arduino_can_GPIO.png" alt="Alt text" width="60%" height="60%"/>

# Software Setting

If you want to test CAN on the configured Arduino, please follow these steps:

1. Install Arduino IDE on each laptop.
2. Download the GitHub repository at [here](https://github.com/autowp/arduino-mcp2515) as a zip file.
3. Upload the zipped folder to the Arduino IDE as a library on each laptop.
4. Connect Arduino to each laptop and execute the example provided in the repository.

For more detailed instructions, it's strongly recommended to read the README file of the [repository](https://github.com/autowp/arduino-mcp2515).

# References

1. [arduino-mcp2515](https://github.com/autowp/arduino-mcp2515.git)
2. [Waveshare LCD1602](https://www.waveshare.com/wiki/LCD1602_RGB_Module)


