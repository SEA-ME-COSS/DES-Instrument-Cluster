#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <dbus/dbus.h>

// Define names
// Declare D-Bus interface name as a constant
const char *const INTERFACE_NAME = "in.softprayog.dbus_example";
// Declare D-Bus names for the server and client as constants
const char *const SERVER_BUS_NAME = "in.softprayog.add_server";
const char *const CLIENT_BUS_NAME = "in.softprayog.add_client";
// Declare D-Bus object paths for the server and client as constants
const char *const SERVER_OBJECT_PATH_NAME = "/in/softprayog/adder";
const char *const CLIENT_OBJECT_PATH_NAME = "/in/softprayog/add_client";
// Declare method name as a constant
const char *const METHOD_NAME = "add_numbers";

DBusError dbus_error;  // Instance of DBusError to handle D-Bus errors
void print_dbus_error (char *str);  // Function to print D-Bus errors

int main (int argc, char **argv)
{
    DBusConnection *conn;  // Pointer for D-Bus connection
    int ret;  // Variable to store function call results
    char speed[80], temperature[80];  // Strings to receive user input

    dbus_error_init (&dbus_error);  // Initialize dbus_error

    conn = dbus_bus_get (DBUS_BUS_SESSION, &dbus_error);  // Connect to D-Bus and obtain a pointer to that connection

    if (dbus_error_is_set (&dbus_error))  // If there's an error during D-Bus connection, print the error message and exit
        print_dbus_error ("Connecting D-Bus Error");

    if (!conn)  // Validate the return value from D-Bus. Note that error handling and return value validation are separate operations.
        exit(1);

    // The following section runs a loop that sends a message to the server via D-Bus and waits for a response
    // In this code, two parameters "speed" and "temperature" are sent to the server. You can modify this part to send different data.
    while (1) {
        printf ("Please type speed: ");  // Prompt user to enter speed value
        fgets (speed, 78, stdin);

        printf ("Please type temperature: ");  // Prompt user to enter temperature value
        fgets (temperature, 78, stdin);

        // Split speed and temperature based on newline
        speed[strcspn(speed, "\n")] = 0;
        temperature[strcspn(temperature, "\n")] = 0;

        char message[160];
        // Format the entered speed and temperature values into a string format
        snprintf(message, sizeof(message), "speed=%s temperature=%s", speed, temperature);

        // Check if CLIENT_BUS_NAME with the same name exists. If not, proceed; if yes, keep trying
        while (1) {
            ret = dbus_bus_request_name (conn, CLIENT_BUS_NAME, 0, &dbus_error);  // Request a name from D-Bus

            if (ret == DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) 
                break;  // If name request is successful, break out of loop

            if (ret == DBUS_REQUEST_NAME_REPLY_IN_QUEUE) {
                fprintf (stderr, "Waiting for the bus ... \n");
                sleep (1);  // If the request is in a queue, wait for 1 second and continue
                continue;
            }
            if (dbus_error_is_set (&dbus_error))
                print_dbus_error ("CLIENT_BUS_NAME Fail");  // Check if there's any error so far
        }
    
        // The next section sends a message to the server via D-Bus and waits for a response
        // DBus message only contains related names
        DBusMessage *request;

        // Use the dbus_message_new_method_call function to create a D-Bus message and store it in request. The message doesn't get onto dbus yet.
        // This message specifies a certain bus name, object path, interface, and method name
        if ((request = dbus_message_new_method_call (SERVER_BUS_NAME, SERVER_OBJECT_PATH_NAME, 
                           INTERFACE_NAME, METHOD_NAME)) == NULL) {
            fprintf (stderr, "Error in dbus_message_new_method_call\n");
            exit (1);
        }

        // The actual data (speed and temperature) is sent through DBusMessageIter
        DBusMessageIter iter;
        // Call dbus_message_iter_init_append function to append parameters to the message
        dbus_message_iter_init_append (request, &iter);
        char *ptr = message;

        // Use dbus_message_iter_append_basic function to append a string parameter to the message. The actual data is added to the Message here.
        if (!dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &ptr)) {
            fprintf (stderr, "Error in dbus_message_iter_append_basic\n");
            exit (1);
        }

        DBusPendingCall *pending_return;
        // Check the success of the dbus_connection_send_with_reply function call
        // Here, conn and request are tied together
        if (!dbus_connection_send_with_reply (conn, request, &pending_return, -1)) {
            fprintf (stderr, "Error in dbus_connection_send_with_reply\n");
            exit (1);
        }

        // Check the object of the called function
        if (pending_return == NULL) {
            fprintf (stderr, "pending return is NULL");
            exit (1);
        }

        dbus_connection_flush (conn);  // Immediately transmit all changes to D-Bus. conn is involved in the connection.
                
        dbus_message_unref (request);  // Unref the message and free up memory when it's no longer needed. request is involved with information.

        // If the response message is not an error, then only process the received data: i.e., if the response message is an error, it won't process that data
        dbus_pending_call_block (pending_return);  // Block until pending_return is ready

        DBusMessage *reply;
        // Use dbus_pending_call_steal_reply function to get the response message
        if ((reply = dbus_pending_call_steal_reply (pending_return)) == NULL) {
            fprintf (stderr, "Error in dbus_pending_call_steal_reply");
            exit (1);
        }

        dbus_pending_call_unref (pending_return);  // If the response message isn't NULL, approve the operation & remove the reference for the pending call

        char *s;
        // Use dbus_message_get_args function to get arguments of the response message. If there's a response message, print it.
        if (dbus_message_get_args (reply, &dbus_error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID)) {
            printf ("%s\n", s);
        }
        else {
             fprintf (stderr, "Did not get arguments in reply\n");
             exit (1);
        }

        dbus_message_unref (reply);  // Unref the response message and free up memory when it's no longer needed.

        // Call dbus_bus_release_name function to release the previously requested CLIENT_BUS_NAME from D-Bus
        if (dbus_bus_release_name (conn, CLIENT_BUS_NAME, &dbus_error) < 0)
            print_dbus_error ("Release CLIENT_BUS_NAME");
    }
}

// Function to print errors related to D-Bus
void print_dbus_error (char *str) {
    fprintf (stderr, "%s: %s\n", str, dbus_error.message);  // Print the error message with a prefix
    dbus_error_free (&dbus_error);  // Free the memory associated with dbus_error
    exit(1);
}
