# Setting

## Environment

### Ubuntu 20.04

### Qt 5.15.0

- You can download qt 5.15.0 version in [here](https://download.qt.io/official_releases/qt/5.15/)

### Qt Creator 4.15.0

- You can download qt creator 4.15.0 version in [here](https://download.qt.io/archive/qtcreator/4.15/4.15.0/)

## Compile

### You can use "senders" by following [dbus-tutorial](https://github.com/dongdongO/SEA-ME_Embedded/DES_Instrument-Cluster/dbus_tutorial/)

### Before you compile Qt program, you have to update .xml file to your .h file

```bash
sudo apt-get update
sudo apt-get install qttools5-dev-tools
qdbuscpp2xml carinformation.h -o test.xml
```

- The xml file is a file that is automatically changed through the above command, not a file that is modified and used by the user.
- You should always update the .xml file when you modify a .h file or a .cpp file.
- If you want to use a .xml file with a different name, you must change the name of (changed_name).xml file while using 'qdbuscpp2xml' command and change it to (changed_name)_adaptor.h instead of test_adaptor.h in main.cpp.
- The file test_adaptor.h is automatically generated when compiling and will be created in your build folder.

## Reference

- [qdbuscpp2xml](https://doc.qt.io/qt-6/qdbusxml2cpp.html)