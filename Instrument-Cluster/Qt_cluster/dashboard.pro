# Set the project template to create an application.
TEMPLATE = app

# Define the name of the output executable or application.
TARGET = dashboard

# Add the current directory to the include path for header files.
INCLUDEPATH += .

# Include necessary Qt modules.
QT += quick core dbus gui qml

# List of source code files to be compiled for the project.
SOURCES += \
    CarInformation.cpp \
    main.cpp

# List of header files that are part of the project.
HEADERS += \
    CarInformation.h

# Include Qt resource files in the project.
RESOURCES += \
    dashboard.qrc

# Include other non-source code files required by the project.
OTHER_FILES += \
    qml/dashboard.qml \
    qml/DashboardGaugeStyle.qml \
    qml/IconGaugeStyle.qml \
    qml/TachometerStyle.qml \
    qml/ValueSource.qml

# Set the installation path for the target executable.
target.path = $$[QT_INSTALL_EXAMPLES]/quickcontrols/extras/dashboard
INSTALLS += target

# Include D-Bus adaptor XML file for interprocess communication.
DBUS_ADAPTORS += cardbus.xml
