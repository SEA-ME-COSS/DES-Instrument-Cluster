// Include necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h> 
#include <string.h>

// Include CAN header
#include <fcntl.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>

// Include Dbus header
#include <stdbool.h>
#include <ctype.h>
#include <dbus/dbus.h>

// Include Multi-thread header
#include <pthread.h>

// Include Kalmanfilter header
#include <math.h>

#define SIZE 2
#define MEASURE_SIZE 1

#define CANbuffer_SIZE 10

// Kalmanfilter configuration

void kalmanFilter_(double measuredstate, double estimation[SIZE], double letterP[SIZE][SIZE], double dt, double renewed_e[SIZE], double renewed_P[SIZE][SIZE]);
void matrix_multiply(double A[SIZE][SIZE], double B[SIZE][SIZE], double result[SIZE][SIZE]);


// CAN configuration
int soc;    // Variable for can socket
typedef struct {
    uint16_t speed_sensor_rpm;  // Variable to store speed info    // Variable to store rpm info
} CANData;  // Define of CAN data sturcture

CANData CANbuffer[CANbuffer_SIZE] = {0};    // Data CANbuffer
int CANbufferIndex = 0;    // Current CANbuffer index
pthread_mutex_t CANbufferMutex = PTHREAD_MUTEX_INITIALIZER;    // Mutex for the CANbuffer

int open_port(const char *port);    // Function for open socket
void read_port(uint16_t *speed_sensor_rpm);   // Function for read CAN socket
int close_port();   // Function for close socket

// DBus configuration
const char *const INTERFACE_NAME = "org.team5.Des02.CarInformation";
const char *const SERVER_BUS_NAME = "org.team5.Des02";
const char *const CLIENT_BUS_NAME = "org.team5.Des02.Client";
const char *const SERVER_OBJECT_PATH_NAME = "/CarInformation";
const char *const CLIENT_OBJECT_PATH_NAME = "/CarInformationClient";

DBusError dbus_error;   // DBusError instance
void print_dbus_error(char *str);   // Function for print error message

// Multi-thread setting
void *readCANThread(void *arg); // Thread function for reading CAN
void * dbusSendThread(void *arg);   // Thread fucntion for sending via DBus

int main (int argc, char **argv)
{
    // Open the CAN port name "can0"
    open_port("can0");

    // Set up the DBus connection
    DBusConnection *conn;
    dbus_error_init(&dbus_error);
    conn = dbus_bus_get(DBUS_BUS_SESSION, &dbus_error);

    // Check for D-Bus connection errors
    if (dbus_error_is_set(&dbus_error)) 
    {
        print_dbus_error("Connecting D-Bus Error\n");
    }

    if (!conn) 
    { 
        exit(1);
    }
    
    // Create threads for CAN and DBus
    pthread_t canThread, dbusThread;
    pthread_create(&canThread, NULL, readCANThread, NULL);
    pthread_create(&dbusThread, NULL, dbusSendThread, (void *)conn);

    pthread_join(canThread, NULL);
    pthread_join(dbusThread, NULL);

    close_port();
    return 0;
}


// CAN function definitions

/**
 * @brief Opens the CAN port.
 * 
 * @param port The name of the port to be opened.
 * @return Returns 0 on success, -1 on failure.
 **/
int open_port(const char *port)
{
    struct ifreq ifr;
    struct sockaddr_can addr;
    struct can_filter rfilter[1];

    // Open the socket
    soc = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (soc < 0) 
    {
        printf("Error opening socket!");
        return (-1);
    }

    addr.can_family = AF_CAN;
    strcpy(ifr.ifr_name, port);

    // Retrieve the interface index for the interface name
    if (ioctl(soc, SIOCGIFINDEX, &ifr) < 0) 
    {
        printf("Error retrieving interface index!");
        return (-1);
    }

    addr.can_ifindex = ifr.ifr_ifindex;

    // Set the socket to non-blocking mode
    fcntl(soc, F_SETFL, O_NONBLOCK);

    // Bind the socket to the CAN interface
    if (bind(soc, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    {
        printf("Error binding to the socket!");
        return (-1);
    }

    // Set the filter for CAN ID 0xF6
    rfilter[0].can_id   = 0x0F6;
    rfilter[0].can_mask = CAN_SFF_MASK;  // Use standard filter mask

    // Apply the filter to the socket
    if (setsockopt(soc, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter)) < 0)
    {
        printf("Error setting CAN filter!");
        return (-1);
    }

    return 0;
}


/**
 * @brief Reads data from the CAN port.
 * 
 * @param speed_sensor_rpm Pointer to a variable where the speed sensor rpm data will be store.
 **/
void read_port(uint16_t *speed_sensor_rpm)
{
    struct can_frame frame;
    int recvbytes = 0;

    struct timeval timeout = {1, 0};
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(soc, &readSet);

    // Wait for data to be ready to read
    if (select((soc + 1), &readSet, NULL, NULL, &timeout) >= 0)
    {
        if (FD_ISSET(soc, &readSet))
        {
            recvbytes = read(soc, &frame, sizeof(struct can_frame));
    
            if (recvbytes)
            {
                if (frame.can_id == 0x0F6) 
                {
                    // Change to actual data by bit shift
                    *speed_sensor_rpm = (frame.data[0] << 8) + frame.data[1];
                }
            }
        }
    }
}


/**
 * @brief Closes the CAN port.
 * 
 * @return Returns 0 on success.
 **/
int close_port()
{
    close(soc);
    return 0;
}


// Dbus function definition

void print_dbus_error (char *str) 
{
    fprintf (stderr, "%s: %s\\n", str, dbus_error.message);
    dbus_error_free (&dbus_error);
}

// Thread function definition

/**
 * @brief Thread function that reads CAN data and CANbuffers it. This thread operates independently of dbusSendThread
 * 
 * @param arg Pointer to get own thread 
 * 
 * @return Returns NULL if it failed
 **/
void *readCANThread(void *arg) 
{
    while (1) 
    {
        uint16_t speed_sensor_rpm;
        
        read_port(&speed_sensor_rpm);  // Read speed and RPM values from the port

        // Lock the CANbuffer mutex before writing data to CANbuffer
        pthread_mutex_lock(&CANbufferMutex);

        CANbuffer[CANbufferIndex].speed_sensor_rpm = speed_sensor_rpm;  // Save speed value to CANbuffer
        CANbufferIndex = (CANbufferIndex + 1)%CANbuffer_SIZE;  // Update the CANbuffer index

        pthread_mutex_unlock(&CANbufferMutex);  // Unlock the CANbuffer mutex after updating
    }
    return NULL;
}


/**
 * @brief Thread function that send CAN data to Dbus. This thread operates independently of readCANThread.
 * 
 * @param arg Pointer to get own thread 
 * 
 * @return Returns NULL if it failed
 **/
void *dbusSendThread(void *arg) 
{
    // Initialize DBus variables for the connection, messages, and iterators
    DBusConnection *conn = (DBusConnection *)arg; // Convert argument to DBus connection type
    DBusMessage *speed_msg, *rpm_msg; // Messages for speed and RPM
    DBusMessageIter speed_args, rpm_args; // Iterators for appending data to messages
    DBusPendingCall *speed_pending, *rpm_pending; // Pending responses from messages
    DBusMessage *speed_reply, *rpm_reply; // Store the reply received from the server

    double speed_sensor_estimation[SIZE] = {0, 0};
    double speed_sensor_letterP[SIZE][SIZE] = {{100, 0},
                                  {0, 100}};
    double speed_sensor_dt = 1;
    double speed_sensor_renewed_e[SIZE], speed_sensor_renewed_P[SIZE][SIZE];
    double speed_sensor_measuredstate;

    while (1)  // Infinite loop to continuously send data
    {
        // Lock mutex to safely access shared CANbuffer
        pthread_mutex_lock(&CANbufferMutex);

        // Compute the most recent CANbuffer index
        int currentIndex = CANbufferIndex - 1;
        if (currentIndex < 0) // If at the beginning, wrap around to the end
        {
            currentIndex = CANbuffer_SIZE - 1;
        }

        // Retrieve the most recent data from the CANbuffer
        uint16_t speed_sensor_rpm = CANbuffer[currentIndex].speed_sensor_rpm;

        // Unlock the mutex after reading data
        pthread_mutex_unlock(&CANbufferMutex);

        // Print the CAN data retrieved
        printf("CAN Data - Speedsensor: %d\n", speed_sensor_rpm);

        speed_sensor_measuredstate = (double) speed_sensor_rpm;

        kalmanFilter_(speed_sensor_measuredstate, speed_sensor_estimation, speed_sensor_letterP, speed_sensor_dt, speed_sensor_renewed_e, speed_sensor_renewed_P);
        
        // Update the estimation and covariance for the next iteration
        for (int i = 0; i < SIZE; i++) {
            speed_sensor_estimation[i] = speed_sensor_renewed_e[i];
            for (int j = 0; j < SIZE; j++) {
                speed_sensor_letterP[i][j] = speed_sensor_renewed_P[i][j];
            }
        }

        uint16_t kf_speed_sensor_rpm = (uint16_t) round(speed_sensor_renewed_e[0]);

        printf("Updated Estimation: x = %d\n", kf_speed_sensor_rpm);

        uint16_t rpm_value = (uint16_t)((float)kf_speed_sensor_rpm / 2.6);
        uint16_t speed_value = (uint16_t)((float)rpm_value * 3.4); // mm/sec


        // Create and initialize the speed message for dbus
        speed_msg = dbus_message_new_method_call(SERVER_BUS_NAME, SERVER_OBJECT_PATH_NAME, INTERFACE_NAME, "setSpeed");
        if (speed_msg == NULL) 
        { 
            fprintf(stderr, "Speed Message Null\n");
            exit(1);
        }
        dbus_message_iter_init_append(speed_msg, &speed_args);
        if (!dbus_message_iter_append_basic(&speed_args, DBUS_TYPE_UINT16, &speed_value)) 
        {
            fprintf(stderr, "Out Of Memory for setSpeed!\n");
            exit(1);
        }

        // Send the speed message and wait for a reply
        if (!dbus_connection_send_with_reply(conn, speed_msg, &speed_pending, -1))
        { 
            fprintf(stderr, "Out Of Memory for setSpeed!\n"); 
            exit(1);
        }
        if (speed_pending == NULL) 
        { 
            fprintf(stderr, "Speed Pending Call Null\n"); 
            exit(1);
        }
        dbus_connection_flush(conn); // Send all CANbuffered data
        dbus_message_unref(speed_msg); // Unreference the speed message

        // Block until we receive a reply for the speed message
        dbus_pending_call_block(speed_pending);
        speed_reply = dbus_pending_call_steal_reply(speed_pending);
        if (speed_reply == NULL) 
        {
            fprintf(stderr, "Speed Reply Null\n");
            exit(1);
        }
        char *speed_reply_msg;
        // Extract the reply message string and print it
        if (dbus_message_get_args(speed_reply, &dbus_error, DBUS_TYPE_STRING, &speed_reply_msg, DBUS_TYPE_INVALID)) 
        {
            printf("setSpeed Reply: %s\n", speed_reply_msg);
        }
        dbus_message_unref(speed_reply);
        dbus_pending_call_unref(speed_pending);

        // Similarly, create and initialize the rpm message for dbus
        rpm_msg = dbus_message_new_method_call(SERVER_BUS_NAME, SERVER_OBJECT_PATH_NAME, INTERFACE_NAME, "setRpm");
        if (NULL == rpm_msg) 
        { 
            fprintf(stderr, "RPM Message Null\n");
            exit(1);
        }
        dbus_message_iter_init_append(rpm_msg, &rpm_args);
        if (!dbus_message_iter_append_basic(&rpm_args, DBUS_TYPE_UINT16, &rpm_value)) 
        {
            fprintf(stderr, "Out Of Memory for setRpm!\n");
            exit(1);
        }

        // Send the rpm message and wait for a reply
        if (!dbus_connection_send_with_reply(conn, rpm_msg, &rpm_pending, -1)) 
        { 
            fprintf(stderr, "Out Of Memory for setRpm!\n"); 
            exit(1);
        }
        if (NULL == rpm_pending) 
        { 
            fprintf(stderr, "RPM Pending Call Null\n"); 
            exit(1);
        }
        dbus_connection_flush(conn); // Send all CANbuffered data
        dbus_message_unref(rpm_msg); // Unreference the rpm message

        // Block until we receive a reply for the rpm message
        dbus_pending_call_block(rpm_pending);
        rpm_reply = dbus_pending_call_steal_reply(rpm_pending);
        if (NULL == rpm_reply) 
        {
            fprintf(stderr, "RPM Reply Null\n");
            exit(1);
        }
        char *rpm_reply_msg;
        // Extract the reply message string and print it
        if (dbus_message_get_args(rpm_reply, &dbus_error, DBUS_TYPE_STRING, &rpm_reply_msg, DBUS_TYPE_INVALID)) 
        {
            printf("setRpm Reply: %s\n", rpm_reply_msg);
        }
        dbus_message_unref(rpm_reply);
        dbus_pending_call_unref(rpm_pending);

        usleep(500000); // Sleep for half a second before the next iteration

    }

    return NULL; // Exit the thread function
}


void matrix_multiply(double A[SIZE][SIZE], double B[SIZE][SIZE], double result[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            result[i][j] = 0;
            for (int k = 0; k < SIZE; k++) 
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void kalmanFilter_(double measuredstate, double estimation[SIZE], double letterP[SIZE][SIZE], double dt, double renewed_e[SIZE], double renewed_P[SIZE][SIZE]) 
{
    double letterA[SIZE][SIZE] = {{1, dt},
                                  {0, 1}};
    double letterQ[SIZE][SIZE] = {{0.05, 0},
                                  {0, 0.05}};
    double letterH[MEASURE_SIZE][SIZE] = {{1, 0}};
    double letterR[MEASURE_SIZE] = {25};

    // 1. Predict the state and error covariance
    double predicted_e[SIZE];
    double temp_result[SIZE][SIZE];
    matrix_multiply(letterA, (double (*)[SIZE])estimation, temp_result);

    for (int i = 0; i < SIZE; i++)
        predicted_e[i] = temp_result[i][0];

    double predicted_P[SIZE][SIZE];
    matrix_multiply(letterA, letterP, predicted_P);

    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            predicted_P[i][j] += letterQ[i][j];
        }
    }

    // 2. Calculate Kalman Gain
    double K[SIZE];
    double denominator = (letterH[0][0] * predicted_P[0][0] + letterH[0][1] * predicted_P[1][0]) * letterH[0][0] 
                         + (letterH[0][0] * predicted_P[0][1] + letterH[0][1] * predicted_P[1][1]) * letterH[0][1] + letterR[0];
    for (int i = 0; i < SIZE; i++) 
    {
        K[i] = (predicted_P[i][0] * letterH[0][0] + predicted_P[i][1] * letterH[0][1]) / denominator;
    }

    // 3. Update the estimation
    double y = measuredstate - (letterH[0][0] * predicted_e[0] + letterH[0][1] * predicted_e[1]);
    for (int i = 0; i < SIZE; i++) 
    {
        renewed_e[i] = predicted_e[i] + K[i] * y;
    }

    // 4. Update the error covariance
    double I[SIZE][SIZE] = {{1, 0},
                            {0, 1}};

    double KH[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            KH[i][j] = K[i] * letterH[0][j];
        }
    }

    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            renewed_P[i][j] = (I[i][j] - KH[i][j]) * predicted_P[i][j];
        }
    }
}




