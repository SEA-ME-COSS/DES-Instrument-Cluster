QT -= gui                     # Removes the GUI module from the project
QT += dbus                    # Adds the D-Bus module to the project

CONFIG += c++11 console        # Specifies that the project uses C++11 and is a console application
CONFIG -= app_bundle           # Prevents the app from being bundled into a single entity (relevant for macOS)

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DBUS_ADAPTORS += test.xml      # Specifies the XML file used for D-Bus adaptors

HEADERS += \                   # List of header files included in the project
        carinformation.h

SOURCES += \                   # List of source files included in the project
        carinformation.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin  # Specifies the deployment path for QNX platform
else: unix:!android: target.path = /opt/$${TARGET}/bin  # Specifies the deployment path for UNIX excluding Android
!isEmpty(target.path): INSTALLS += target  # Adds the target to the installation path if it's not empty
