#ifndef CARINFORMATION_H
#define CARINFORMATION_H

#include <QObject>

class CarInformation : public QObject
{
    // Macro used to declare that this class contains Qt signals and slots.
    Q_OBJECT
    // Provides D-Bus interface information for the class.
    Q_CLASSINFO("D-Bus Interface", "org.team5.Des02.CarInformation")

public:
    // Constructor for the CarInformation class.
    explicit CarInformation(QObject *parent = nullptr);

public Q_SLOTS:
    // Qt slot to set the car's data. Returns a QString message.
    QString setSpeed(quint16 speed);
    QString setBattery(qreal battery);
    QString setGear(quint8 gear);
    QString setRpm(quint16 rpm);
    // Qt invokable function to retrieve the car's data.
    Q_INVOKABLE quint16 getSpeed();
    Q_INVOKABLE qreal getBattery();
    Q_INVOKABLE quint8 getGear();
    Q_INVOKABLE quint16 getRpm();

private:
    // Private member variable to store the car's data.
    quint16 speed;
    qreal battery;
    quint8 gear;
    quint16 rpm;
};

#endif // CARINFORMATION_H
