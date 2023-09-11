# D-Bus Tutorial

---

# Intorduction

In this repository, we test D-Bus by providing clear examples of how to implement both a client and a server in two popular programming languages: C and Python. D-Bus is a powerful inter-process communication protocol that is widely used in Linux for software components to communicate with each other.

# Project Goals

Our overarching aim is to delve deep into the D-Bus communication protocol and harness its capabilities for inter-process communication. By embarking on this project, we're not only setting out to understand D-Bus in theory but also to practically implement and test it across different programming languages, namely C and Python.

To be more specific, our objectives are:

- **Understanding D-Bus:** Gain a comprehensive understanding of the D-Bus communication protocol.
- **Cross-Language Implementation:** Develop both client and server programs using C and Python, showcasing the flexibility and applicability of D-Bus across languages.
- **Seamless Communication:** Implement and test communication between the client and server, ensuring seamless data exchange through method calls and return values.
- **Error Handling Mastery:** Familiarize ourselves with error handling in D-Bus, preparing for any potential pitfalls or exceptions that may arise.
- **Evaluating Interoperability:** Evaluate the characteristics, advantages, and challenges of D-Bus communication between different languages.
- **Broadening Networking Knowledge:** Ultimately, elevate our knowledge in communication protocols and networking as a whole through hands-on experience.

# Usages

To run the code, ensure you have the required libraries and dependencies installed.

Follow the setting README.

### client:

- pydbus-client.py : Contains the Python implementation of a D-Bus client using the dbus module.

```bash
python3 pydbus-client.py
```

- add-client.c: Contains the C implementation of a D-Bus client(sender).

```bash
make
./add-client_execution
```

### server:

- pydbus-server.py: Contains the Python implementation of a D-Bus server using the dbus module.

```bash
python3 pydbus-server.py
```

- add-server.c: Contains the C implementation of a D-Bus server(receiver).

```bash
make
./add-server_execution
```

# Reference

- [D-Bus](https://www.freedesktop.org/wiki/Software/dbus/)
- [D-Bus Tutorial](https://www.softprayog.in/programming/d-bus-tutorial)
- [Python D-Bus Tutorial](https://dbus.freedesktop.org/doc/dbus-python/)