# DBus with Qt

---

# Introduction

This project aims to manage key vehicle information (speed, RPM, gear, battery status) and communicate it to a Qt program using D-Bus. The logic for transmitting and receiving information is implemented in C, Python, and Qt.

# Project Goals

The primary goal of this repository is to delve deep into the intricacies of the D-Bus communication protocol and to grasp its versatility across different languages and frameworks, paving the way for its implementation in our subsequent projects.

Specific objectives include:

- **Comprehensive Understanding of D-Bus:** To gain an in-depth comprehension of how D-Bus functions, its connection methodologies, and its relevance in modern software architectures.
- **Real-time Vehicle Information Management:** Implement a robust system that manages, updates, and provides vehicle-related data in real-time with utmost precision. This is essential for applications that rely on real-time metrics for crucial decision-making processes.
- **Universal Access with D-Bus:** Design the system such that vehicle information is not only accessible in the native environment but can also be retrieved and manipulated across various programming languages and platforms using D-Bus communication. This promotes interoperability and flexibility in multi-language software ecosystems.
- **Modularity and Scalability:** Adopt a modular approach in the codebase to ensure that individual components can be updated or replaced without affecting the entire system. This not only simplifies maintenance but also ensures the system can scale to accommodate future advancements and requirements.
- **Documentation and Best Practices:** Alongside the code, provide comprehensive documentation and guidelines. This ensures that future developers or teams can easily understand, adopt, or adapt the system to their needs. Furthermore, adhering to best coding practices will ensure the longevity and reliability of the system.

# Usage

The chosen Qt compiler version is 5.15.0, and the Qt Creator version is 4.15.0.

Follow the instructions in the [settings folder](./setting/) to create an environment like ours.

Then, execute the codes in the sender folder as well.

To start the battery status information D-Bus service with the Python script, use the following command:

```bash
python3 batterystatus.py
```

To compile and execute the C code, relaying speed and RPM information to the Qt D-Bus service, use:

```bash
make
./speedstatus_execution
```

# Reference

- [Q-Dbus](https://doc.qt.io/qt-5/qtdbus-index.html)
- [qdbuscpp2xml](https://doc.qt.io/qt-6/qdbusxml2cpp.html)