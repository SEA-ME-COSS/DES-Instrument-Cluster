# **Dashboard Project**

---

# Result
<img src="https://github.com/dongdongO/SEA-ME_Embedded/blob/main/DES_Instrument-Cluster/Images/cluster final.png" alt="Alt text" width="100%" height="100%"/>

# **Introduction**

The Dashboard Project is an application designed to display and manage vehicle information in real-time. Built on the Qt framework, it encompasses both user interface and data processing functionalities. The project visually represents various vehicle sensor data such as speed, battery level, gear status, and RPM.

# **Architecture**

The application is primarily divided into two parts:

1. **Backend (C++ Layer)**: The **`CarInformation`** class handles vehicle data processing and communicates via the D-Bus interface.
2. **Frontend (QML Layer)**: Defines the user interface. Various QML files detail individual UI components and styles.

Using D-Bus facilitates inter-process communication, allowing for easy data sharing between different systems or applications.

# **Details**

- **`cardbus.xml`**: An XML file for D-BUS Object Introspection, it defines various D-Bus methods and interfaces. This file plays a crucial role in setting the protocol for inter-process communication.
- **`CarInformation.h`** & **`CarInformation.cpp`**: These define the **`CarInformation`** class which handles vehicle data processing and D-Bus communication. The class stores the status information of the vehicle and provides methods to set or retrieve this data.
- **`dashboard.pro`**: This project configuration file defines the necessary information and dependencies for building and compiling. It contains lists of Qt modules, resource files, headers, and source files.
- **`dashboard.qml`**: This QML file defines the main user interface of the dashboard, representing various UI components and interactions.
- **`DashboardGaugeStyle.qml`**: Defines the dashboard's gauge style, displaying data to the user with visual elements and animations.
- **`IconGaugeStyle.qml`**: This gauge style is defined alongside icons, depicting specific vehicle functionalities or statuses within the gauge.
- **`TachometerStyle.qml`**: Defines the style for representing the RPM, visually displaying the current RPM of the engine.
- **`ValueSource.qml`**: Defines the logic and structure to fetch values from various data sources, allowing the dashboard to display real-time data.

# **Usage**

1. **Setting Up**: Open the **`dashboard.pro`** file using Qt Creator and install the necessary Qt modules and libraries.
2. **Building & Running**: Build and run the project to view the dashboard interface. Various QML files define the UI components which can be viewed in real-time.
3. **D-Bus Integration**: Use the **`cardbus.xml`** file to set up the D-Bus service and employ the methods in the **`CarInformation`** class to send or receive data.

# References

- [Qt Dashboard](https://doc.qt.io/qt-5/qtquickextras-dashboard-example.html)
- [Qt DBus](https://doc.qt.io/qt-5/qtdbus-index.html)