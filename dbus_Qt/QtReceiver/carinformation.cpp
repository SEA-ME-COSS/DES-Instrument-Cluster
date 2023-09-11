#include "carinformation.h"  // Include the header file for CarInformation class
#include <QDebug>            // Include for debugging purposes

// Constructor implementation for CarInformation class
CarInformation::CarInformation(QObject *parent) : QObject(parent)
{
    speed = 0;    // Initialize speed to 0
    battery = 0.0;  // Initialize battery level to 0.0
    gear = 'P';     // Initialize gear to 'P' (probably stands for 'Park')
}

// Implementation for setting the speed
QString CarInformation::setSpeed(quint8 speed)
{
    this->speed = speed;  // Update the class member with the provided speed
    qDebug() << "Receive Speed Data : " << speed;  // Debug log
    return "Get Speed";  // Return a status string
}

// Implementation for setting the battery level
QString CarInformation::setBattery(qreal battery)
{
    this->battery = battery;  // Update the class member with the provided battery level
    qDebug() << "Receive Battery Data : " << battery;  // Debug log
    return "Get Battery";  // Return a status string
}

// Implementation for setting the gear using a byte representation
QString CarInformation::setGear(quint8 gearByte)
{
    gear = static_cast<char>(gearByte);  // Convert byte to char and update the class member
    qDebug() << "Receive Gear Data : " << gear;  // Debug log
    return "Get Gear";  // Return a status string
}

// Implementation for setting the RPM
QString CarInformation::setRpm(quint8 rpm)
{
    this->rpm = rpm;  // Update the class member with the provided RPM
    qDebug() << "Receive Rpm Data : " << rpm;  // Debug log
    return "Get Rpm";  // Return a status string
}

// Implementation for getting the current speed
quint8 CarInformation::getSpeed()
{
    return speed;  // Return the current speed
}

// Implementation for getting the current battery level
qreal CarInformation::getBattery()
{
    return battery;  // Return the current battery level
}

// Implementation for getting the current gear
char CarInformation::getGear()
{
    return gear;  // Return the current gear
}

// Implementation for getting the current RPM
quint8 CarInformation::getRpm()
{
    return rpm;  // Return the current RPM
}
