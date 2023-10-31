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
// Declare the D-Bus name of the server as a constant
const char *const SERVER_BUS_NAME = "in.softprayog.add_server";
// Declare the D-Bus object path of the server as a constant
const char *const SERVER_OBJECT_PATH_NAME = "/in/softprayog/adder";
// Declare the method name as a constant
const char *const METHOD_NAME = "add_numbers";

DBusError dbus_error; // Instance of DBusError to handle D-Bus errors
void print_dbus_error (char *str); // Declaration of the D-Bus error printing function
// Declaration of the server message handler function
DBusHandlerResult server_handle_message (DBusConnection *conn, DBusMessage *message, void *user_data);

// Initialize the server virtual table
DBusObjectPathVTable server_vtable = {
    .message_function = server_handle_message // Set the message handler function
};

int main (int argc, char **argv)
{
    DBusConnection *conn; // Pointer for D-Bus connection
    int ret; // Variable to store function call results

    dbus_error_init (&dbus_error); // Initialize dbus_error

    conn = dbus_bus_get (DBUS_BUS_SESSION, &dbus_error); // Connect to D-Bus and get the pointer pointing to that connection

    if (dbus_error_is_set (&dbus_error)) // Print the error message and exit if there's an error while connecting to D-Bus
        print_dbus_error ("dbus_bus_get");

    if (!conn) // Check the return value of D-Bus. Error handling and return value validation are different
        exit (1);

    // Check for the existence of SERVER_BUS_NAME with the same name. Pass if it doesn't exist, keep trying if it does
    while (1) {
        ret = dbus_bus_request_name (conn, SERVER_BUS_NAME, 0, &dbus_error); // Request a name from D-Bus

        if (ret == DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) 
           break; // Exit the loop if name request is successful

        if (ret == DBUS_REQUEST_NAME_REPLY_IN_QUEUE) {
           fprintf (stderr, "Waiting for the bus ... \n");
           sleep (1); // Wait for 1 second if the request is in the queue
           continue;
        }
        if (dbus_error_is_set (&dbus_error))
           print_dbus_error ("dbus_bus_request_name"); // Check for errors so far
    }

    if (dbus_connection_register_object_path (conn, SERVER_OBJECT_PATH_NAME, 
            &server_vtable, NULL) == false) {
        fprintf (stderr, "Error in dbus_connection_register_object_path\n");
        exit (1);
    }

    // Listen to messages from dbus
    while (1) {
        dbus_connection_read_write_dispatch (conn, -1);
    }

    return 0;
}

// Function to print D-Bus errors
void print_dbus_error (char *str) 
{
    fprintf (stderr, "%s: %s\n", str, dbus_error.message);
    dbus_error_free (&dbus_error);
}

DBusHandlerResult server_handle_message (DBusConnection *conn, DBusMessage *message, void *user_data) // Definition of server message handler function
{
    // If the received message has the same INTERFACE_NAME and METHOD_NAME
    if (dbus_message_is_method_call (message, INTERFACE_NAME, METHOD_NAME)) {
        DBusMessageIter iter; // Declare DBusMessageIter object
        char *msg; // Declare string pointer

        dbus_message_iter_init (message, &iter); // Initialize message iterator

        if (dbus_message_iter_get_arg_type (&iter) == DBUS_TYPE_STRING) { // If the argument type pointed by the iterator is string
            dbus_message_iter_get_basic (&iter, &msg); // Get the argument value and assign it to msg
        }

        printf("Received: %s\n", msg); // Print the received message

        DBusMessage *reply; // Declare a DBusMessage object pointer

        if ((reply = dbus_message_new_method_return (message)) == NULL) { // Print error message and exit if failed to create a method return message
            fprintf (stderr, "Error in dbus_message_new_method_return\n");
            exit (1);
        }

        if (!dbus_message_append_args (reply, DBUS_TYPE_STRING, &msg, DBUS_TYPE_INVALID)) { // Print error message and exit if failed to add arguments to the message
            fprintf (stderr, "Error in dbus_message_append_args\n");
            exit (1);
        }

        if (!dbus_connection_send (conn, reply, NULL)) { // Print error message and exit if failed to send the message
            fprintf (stderr, "Error in dbus_connection_send\n");
            exit (1);
        }
        dbus_connection_flush (conn); // Send all pending messages to the bus

        dbus_message_unref (reply); // Release the reference to the message

        return DBUS_HANDLER_RESULT_HANDLED; // Return that the message has been handled
    }

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED; // Return that the message has not been handled yet
}
