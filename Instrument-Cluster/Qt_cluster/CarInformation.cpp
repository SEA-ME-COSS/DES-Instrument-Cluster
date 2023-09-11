#include "CarInformation.h"
#include <QtDBus/QDBusConnection>
#include <QDebug>

CarInformation::CarInformation(QObject *parent) : QObject(parent)
{
    // Register the D-Bus service name and object path for the CarInformation instance.
    QDBusConnection::sessionBus().registerService("org.team5.Des02");
    QDBusConnection::sessionBus().registerObject("/CarInformation", this);

    // Initialize the member variables with default values.
    speed = 0;
    battery = 0.0;
    gear = 0;
    rpm = 0;
}

// Set the car's speed.
QString CarInformation::setSpeed(quint16 speed)
{
    this->speed = speed;
    qDebug() << "Receive Speed Data : " << speed;
    return "Get Speed";
}

// Set the car's battery level.
QString CarInformation::setBattery(qreal battery)
{
    this->battery = battery;
    qDebug() << "Receive Battery Data : " << battery;
    return "Get Battery";
}

// Set the car's gear.
QString CarInformation::setGear(quint8 gear)
{
    this->gear = gear;
    qDebug() << "Receive Gear Data : " << gear;
    return "Get Gear";
}

// Set the car's RPM.
QString CarInformation::setRpm(quint16 rpm)
{
    this->rpm = rpm;
    qDebug() << "Receive Rpm Data : " << rpm;
    return "Get Rpm";
}

// Return the car's speed.
Q_INVOKABLE quint16 CarInformation::getSpeed()
{
    return speed;
}

// Return the car's battery level.
Q_INVOKABLE qreal CarInformation::getBattery()
{
    return battery;
}

// Return the car's gear.
Q_INVOKABLE quint8 CarInformation::getGear()
{
    return gear;
}

// Return the car's RPM.
Q_INVOKABLE quint16 CarInformation::getRpm()
{
    return rpm;
}
