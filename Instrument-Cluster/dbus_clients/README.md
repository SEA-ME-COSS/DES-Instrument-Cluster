# Sender Info

---

# DBus Tutorial

If you want to know about DBus, follow [dbus_tutorial](https://github.com/dongdongO/SEA-ME_Embedded/DES_Instrument-Cluster/dbus_tutorial/)

# Details

### batterystatus.py

Written in Python, this code calculates and checks the vehicle's battery status. It also discerns the state of forward and reverse motions to relay gear information. Ultimately, it updates this information on Qt at 1-second intervals using D-Bus. 

### speedstatus.c

Written in C, this code manages the vehicle's speed and RPM information. Currently, the value is fixed at 10, but there are plans to relay data received from CAN in the future. It uses D-Bus to pass this information to the D-Bus service implemented in Qt.

Always check that the server, client, interface, and method names are the same, and that the data types on the sender and receiver are the same.

# References

- [D-Bus](https://www.freedesktop.org/wiki/Software/dbus/)
- [D-Bus Tutorial](https://www.softprayog.in/programming/d-bus-tutorial)
- [Python D-Bus Tutorial](https://dbus.freedesktop.org/doc/dbus-python/)