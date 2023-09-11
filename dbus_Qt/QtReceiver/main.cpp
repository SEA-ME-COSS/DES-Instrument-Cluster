#include <QCoreApplication>         // Include for core application functionalities
#include <QtDBus/QDBusConnection>  // Include for D-Bus connection functionalities

#include "carinformation.h"        // Include for CarInformation class
#include "test_adaptor.h"          // Include for CarInformationAdaptor class

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);  // Create a QCoreApplication object for this application

    // Create a connection to the D-Bus session bus
    QDBusConnection connection = QDBusConnection::sessionBus();
    
    // Create a CarInformation object
    CarInformation *carinfo = new CarInformation();
    
    // Create an adaptor for the CarInformation object to expose it on D-Bus
    new CarInformationAdaptor(carinfo);
    
    // Register the CarInformation object with the D-Bus connection under the path "/CarInformation"
    connection.registerObject("/CarInformation", carinfo);
    
    // Register the service "org.team4.Des02" with the D-Bus connection
    connection.registerService("org.team4.Des02");

    // Start the application's event loop
    return a.exec();
}
