#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <dbus/dbus.h>

// D-Bus constants for server and client information.
const char *const INTERFACE_NAME = "org.team4.Des02.CarInformation";
const char *const SERVER_BUS_NAME = "org.team4.Des02";
const char *const CLIENT_BUS_NAME = "org.team4.Des02.Client";
const char *const SERVER_OBJECT_PATH_NAME = "/CarInformation";
const char *const CLIENT_OBJECT_PATH_NAME = "/CarInformationClient";

DBusError dbus_error;  // Structure to hold any D-Bus related errors.

// Function to print any D-Bus errors.
void print_dbus_error (char *str);

int main (int argc, char **argv)
{
    DBusConnection *conn;  // Represents the D-Bus connection.
    int ret;  // To store return values.

    // Initialize the D-Bus error structure.
    dbus_error_init (&dbus_error);  

    // Connect to the D-Bus session bus. This bus is most commonly used for user applications.
    conn = dbus_bus_get (DBUS_BUS_SESSION, &dbus_error);  

    // Check if there's an error while connecting.
    if (dbus_error_is_set (&dbus_error))  
        print_dbus_error ("Error while connecting to D-Bus");

    // If no connection, exit the program.
    if (!conn) 
        exit(1);

    // Main loop to continuously interact with the D-Bus server.
    while (1) 
    {
        // Hardcoded values for speed and RPM. These could be dynamic in a real-world scenario.
        uint8_t speed_value = 10;
        uint8_t rpm_value = 10;

        while (1) 
        {
            // Request a name on the D-Bus. It ensures unique naming and helps in communication.
            ret = dbus_bus_request_name (conn, CLIENT_BUS_NAME, 0, &dbus_error);  

            // If successfully got the name, break out.
            if (ret == DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) 
                break;

            // If the name is already in use and waiting in the queue.
            if (ret == DBUS_REQUEST_NAME_REPLY_IN_QUEUE) 
            {
                fprintf (stderr, "Waiting for the bus ... \n");
                sleep (1);  // Wait for a second before retrying.
                continue;
            }

            // Print errors related to D-Bus naming.
            if (dbus_error_is_set (&dbus_error))
                print_dbus_error ("Failed to get the CLIENT_BUS_NAME");
        }

        // Construct a message to set the car's speed using the D-Bus API.
        DBusMessage *request_speed;
        if ((request_speed = dbus_message_new_method_call(SERVER_BUS_NAME, SERVER_OBJECT_PATH_NAME, 
                            INTERFACE_NAME, "setSpeed")) == NULL) 
        {
            fprintf(stderr, "Error creating a message for the 'setSpeed' method\n");
            exit(1);
        }

        // Initialize the message iterator for appending arguments.
        DBusMessageIter iter_speed;
        dbus_message_iter_init_append(request_speed, &iter_speed);

        // Append the speed value to the message.
        if (!dbus_message_iter_append_basic(&iter_speed, DBUS_TYPE_BYTE, &speed_value)) 
        {
            fprintf(stderr, "Error appending speed value to the message\n");
            exit(1);
        }

        // Send the message to the server and await a reply.
        DBusPendingCall *pending_return_speed;
        if (!dbus_connection_send_with_reply(conn, request_speed, &pending_return_speed, -1)) 
        {
            fprintf(stderr, "Error sending the 'setSpeed' message and waiting for a reply\n");
            exit(1);
        }

        // Check if there's a pending reply.
        if (pending_return_speed == NULL) 
        {
            fprintf(stderr, "No pending reply for the 'setSpeed' message\n");
            exit(1);
        }

        // Wait for the reply to be ready.
        dbus_pending_call_block(pending_return_speed);

        // Extract the reply for the 'setSpeed' method.
        DBusMessage *reply_speed;
        if ((reply_speed = dbus_pending_call_steal_reply(pending_return_speed)) == NULL) 
        {
            fprintf(stderr, "Error extracting the reply for the 'setSpeed' method\n");
            exit(1);
        }

        // Parse the reply to extract the response message.
        char *reply_msg_speed;
        if (dbus_message_get_args(reply_speed, &dbus_error, DBUS_TYPE_STRING, &reply_msg_speed, DBUS_TYPE_INVALID)) 
        {
            printf("Response for 'setSpeed': %s\n", reply_msg_speed);
        } 
        else 
        {
            fprintf(stderr, "Failed to extract arguments from the 'setSpeed' reply\n");
            exit(1);
        }
        

        // Construct a message to set the car's RPM using the D-Bus API.
        DBusMessage *request_rpm;
        if ((request_rpm = dbus_message_new_method_call(SERVER_BUS_NAME, SERVER_OBJECT_PATH_NAME, 
                        INTERFACE_NAME, "setRpm")) == NULL) 
        {
            fprintf(stderr, "Error creating a message for the 'setRpm' method\n");
            exit(1);
        }

        // Initialize the message iterator for appending arguments.
        DBusMessageIter iter_rpm;
        dbus_message_iter_init_append(request_rpm, &iter_rpm);

        // Append the RPM value to the message.
        if (!dbus_message_iter_append_basic(&iter_rpm, DBUS_TYPE_BYTE, &rpm_value)) 
        {
            fprintf(stderr, "Error appending RPM value to the message\n");
            exit(1);
        }

        // Send the message to the server and await a reply.
        DBusPendingCall *pending_return_rpm;
        if (!dbus_connection_send_with_reply(conn, request_rpm, &pending_return_rpm, -1)) 
        {
            fprintf(stderr, "Error sending the 'setRpm' message and waiting for a reply\n");
            exit(1);
        }

        // Check if there's a pending reply.
        if (pending_return_rpm == NULL) 
        {
            fprintf(stderr, "No pending reply for the 'setRpm' message\n");
            exit(1);
        }

        // Wait for the reply to be ready.
        dbus_pending_call_block(pending_return_rpm);

        // Extract the reply for the 'setRpm' method.
        DBusMessage *reply_rpm;
        if ((reply_rpm = dbus_pending_call_steal_reply(pending_return_rpm)) == NULL) 
        {
            fprintf(stderr, "Error extracting the reply for the 'setRpm' method\n");
            exit(1);
        }

        // Parse the reply to extract the response message.
        char *reply_msg_rpm;
        if (dbus_message_get_args(reply_rpm, &dbus_error, DBUS_TYPE_STRING, &reply_msg_rpm, DBUS_TYPE_INVALID)) 
        {
            printf("Response for 'setRpm': %s\n", reply_msg_rpm);
        } 
        else 
        {
            fprintf(stderr, "Failed to extract arguments from the 'setRpm' reply\n");
            exit(1);
        }
        

        // Release the name we requested earlier. This is a cleanup step.
        if (dbus_bus_release_name (conn, CLIENT_BUS_NAME, &dbus_error) == -1) 
        {
             fprintf (stderr, "Error releasing the CLIENT_BUS_NAME\n");
             exit (1);
        }

        sleep(1);  // Sleep for a second before next iteration.
    }

    return 0;  // End the program.
}

// Function definition for printing D-Bus errors.
void print_dbus_error (char *str) 
{
    fprintf (stderr, "%s: %s\n", str, dbus_error.message);
    dbus_error_free (&dbus_error);
}
