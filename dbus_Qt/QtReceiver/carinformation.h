#ifndef CARINFORMATION_H  // Header guard to prevent multiple inclusions
#define CARINFORMATION_H

#include <QObject>  // Include QObject for base class

// Defines the CarInformation class which inherits from QObject
class CarInformation : public QObject
{
    Q_OBJECT  // Macro for QObject-based classes; helps with meta-object features like signals and slots

    // Specifies the D-Bus interface for this class
    Q_CLASSINFO("D-Bus Interface", "org.team4.Des02.CarInformation")

public:
    // Constructor with optional parent QObject
    explicit CarInformation(QObject *parent = nullptr);

    // Public slots for setting and getting car information
public Q_SLOTS:
    QString setSpeed(quint8 speed);     // Set speed and return a status string
    QString setBattery(qreal battery);  // Set battery level and return a status string
    QString setGear(quint8 gearByte);   // Set gear using a byte representation and return a status string
    QString setRpm(quint8 rpm);         // Set RPM and return a status string
    quint8 getSpeed();                  // Get current speed
    qreal getBattery();                 // Get current battery level
    char getGear();                     // Get current gear as a char
    quint8 getRpm();                    // Get current RPM

private:
    // Private member variables to hold car information
    quint8 speed;    // Speed of the car
    qreal battery;   // Battery level of the car
    char gear;       // Current gear of the car
    quint8 rpm;      // RPM of the car
};

#endif // CARINFORMATION_H  // End of header guard
