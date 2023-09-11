# Setting

---

## Software Setting

To compile python dbus, you have to install :

```bash
sudo apt-get install python3
sudo apt-get install python3-pip
pip3 install dbus-python
sudo apt-get install libglib2.0-dev
sudo apt-get install python3-gi
```

To compile C dbus, you have to install :

```bash
sudo apt-get update
sudo apt-get install gcc
sudo apt-get install libdbus-1-dev
```

add-client.c, add-server.c needs option for compile, so I made Make file.

So if you want to compile c :

```bash
make
./add-client_execution
```

## References

- [D-Bus Tutorial](https://www.softprayog.in/programming/d-bus-tutorial)
- [Python D-Bus Tutorial](https://dbus.freedesktop.org/doc/dbus-python/)