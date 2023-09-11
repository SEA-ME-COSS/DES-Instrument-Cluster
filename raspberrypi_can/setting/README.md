# Setting

## Hardware Setting

### Requirements

* Arduino Uno: Any Arduino board with CAN capability or with a CAN shield/module.
* Raspberry Pi 4: Ensure it's updated to the latest firmware and OS.
* CAN Interface Module/Shield: For Arduino if it doesn't natively support CAN.
* CAN Hat or Module for Raspberry Pi 4: Used to enable CAN capability on the Pi.
* Jumper Wires: For connections.
* Speed Sensor : To get speed data
* Power Supply: Appropriate for both Raspberry Pi and Arduino.
* (Optional) Breadboard: For easy prototyping.  
<br>  

### Connect

<img src="https://github.com/SEA-ME-COSS/DES-Instrument-Cluster/blob/main/Images/arduino_rasp_pin.png" alt="Alt text" width="100%" height="100%"/>

1. Power Up: Ensure both the Arduino and Raspberry Pi 4 are powered off. Connect their power supplies.
2. Set Up CAN Interfaces: Attach the CAN module/shield to the Arduino and the CAN hat/module to the Raspberry Pi 4.
3. Connections: Using jumper wires, connect the CAN High and CAN Low pins between the Arduino and Raspberry Pi. It's crucial to ensure that these connections match.
4. Grounding: Connect the ground (GND) of the Arduino to the ground (GND) of the Raspberry Pi 4 to establish a common ground.
5. Power On: Once all connections are secured, power on both devices. Ensure that there's no short circuit or incorrect connections.  
<br>  

Note: Before running any software, always double-check your connections to prevent any damage to your devices.
<br>  

## Software Setting

### Enable SPI interface
Open the terminal, and use the command to enter the configuration page.

```bash
sudo raspi-config
```

Choose Interfacing Options -> SPI -> Yes to enable the SPI interface.

<img src="https://github.com/SEA-ME-COSS/DES-Instrument-Cluster/blob/main/Images/spisetting.png" alt="Alt text" width="70%" height="70%"/>



Reboot Raspberry Pi:

```bash
sudo reboot
```

Please make sure that the SPI interface was not used by other devices, you can check in the /boot/config.txt.
<br>  

### Install libraries
* bcm2835

Open the terminal and run the commands below to install the bcm2835 library:

```bash
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.60.tar.gz
tar zxvf bcm2835-1.60.tar.gz 
cd bcm2835-1.60/
sudo ./configure
sudo make
sudo make check
sudo make install
# For More：http://www.airspayce.com/mikem/bcm2835/
```

* wiringPi

```bash
#Open the Raspberry Pi terminal and run the following command
cd
sudo apt-get install wiringpi
#For Raspberry Pi systems after May 2019 (earlier than that can be executed without), an upgrade may be required:
wget https://project-downloads.drogon.net/wiringpi-latest.deb
sudo dpkg -i wiringpi-latest.deb
gpio -v
# Run gpio -v and version 2.52 will appear, if it doesn't it means there was an installation error

# Bullseye branch system using the following command:
git clone https://github.com/WiringPi/WiringPi
cd WiringPi
. /build
sudo gpio -v
# Run gpio -v and version 2.70 will appear, if it doesn't it means there was an installation error
```

* Python

Install python library:

```bash
#python3
sudo apt-get update
sudo apt-get install python3-pip
sudo apt-get install python3-pil
sudo apt-get install python3-numpy
sudo pip3 install RPi.GPIO
sudo pip3 install spidev 
sudo pip3 install python-can
```
<br>  

### Preparation
* Insert the module into Raspberry Pi, and then modify the config.txt file:

```bash
sudo nano /boot/config.txt
```

* Append these statements to the file:

```bash
dtparam=spi=on
dtoverlay=mcp2515-can1,oscillator=16000000,interrupt=25
dtoverlay=mcp2515-can0,oscillator=16000000,interrupt=23
dtoverlay=spi-bcm2835-overlay
dtparam=spi=on
dtoverlay=spi1-3cs
dtoverlay=mcp251xfd,spi0-0,interrupt=25
dtoverlay=mcp251xfd,spi1-0,interrupt=24
```

* Save and exit, then restart your Pi:
```bash
sudo reboot
```

* After restart, check if initialize successfully:
```bash
sudo dmesg | grep spi
```

<img src="https://github.com/SEA-ME-COSS/DES-Instrument-Cluster/blob/main/Images/checkspi.png" alt="Alt text" width="70%" height="70%"/>


* Set up CAN:
```bash
sudo ip link set can0 up type can bitrate 500000
sudo ip link set can1 up type can bitrate 500000
sudo ifconfig can0 txqueuelen 65536
sudo ifconfig can1 txqueuelen 65536
```

* For more information about CAN kernel instructions, please check:
```bash
# https://www.kernel.org/doc/Documentation/networking/can.txt
```

* Run "ifconfig":
```bash
ifconfig
```

<img src="https://github.com/SEA-ME-COSS/DES-Instrument-Cluster/blob/main/Images/checkifconfig.png" alt="Alt text" width="70%" height="70%"/>
<br>  

### Testing
If there is one 2-CH CAN HAT on hand, you can connect CAN0_H and CAN1_H and CAN0_L and CAN1_L of the module:

* install can-utils:
```bash
sudo apt-get install can-utils
```

* Open two terminal windows:
One terminal input receives the CAN0 data command:
```bash
candump can0
```

Another terminal input sends the CAN1 data command:
```bash
cansend can1 000#11.22.33.44
```

<img src="https://github.com/SEA-ME-COSS/DES-Instrument-Cluster/blob/main/Images/checkcan.png" alt="Alt text" width="70%" height="70%"/>


If you have two 2-CH CAN HAT on hand, you can directly connect CAN_H and CAN_L two by two. The effect is the same as the above, pay attention to match the communication rate, identify the ID, and output the interface serial number.
<br>  

# References

- [CAN Software Setting](https://www.waveshare.com/wiki/2-CH_CAN_HAT)
- [Speed Sensor](https://srituhobby.com/ir-infrared-speed-sensor-with-arduino-how-does-work-ir-speed-sensor/)