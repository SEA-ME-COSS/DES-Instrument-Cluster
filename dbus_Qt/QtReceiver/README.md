# Qt Receiver

## Introduction

This Qt program outputs speed, rpm, battery, and gear information received from speedstatus.c and [batterystatus.py](http://batterystatus.py/) to the Qt terminal.

## Details

### QtReceiver

Responsible for receiving the information sent from the sender folder and displaying it on the terminal. In the future, this received data is planned to be displayed on a QML-styled dashboard.

### carinformation.cpp/h:

This C++ class manages key vehicle information (speed, RPM, gear, battery status) in an object-oriented manner. It provides a D-Bus interface to query or set this information from the outside.

The set functions play the role of receiving information from dbus and storing the values in the appropriate values, and if you want to use the corresponding values, you can call the get functions.

### server_register.pro:

This is the Qt project configuration file. It contains settings related to D-Bus and other project configurations.

### test.xml:

This is the D-Bus interface definition file, containing information about available methods and interfaces. It is not manually edited but is written using the qdbuscpp2xml command.

