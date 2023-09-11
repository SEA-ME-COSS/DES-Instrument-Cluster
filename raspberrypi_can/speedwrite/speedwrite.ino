// Include the necessary libraries for SPI communication and MCP2515 (a CAN controller)
#include <SPI.h>
#include <mcp2515.h>

// Define constants and global variables
const byte PulsesPerRevolution = 20;    // We expect 20 pulses for each wheel revolution
const unsigned long ZeroTimeout = 100000;    // Timeout set for 100ms
const byte numReadings = 2;    // Number of readings to consider for RPM averaging

// These variables are used to calculate the period between pulses and the RPM
volatile unsigned long LastTimeWeMeasured;    
volatile unsigned long PeriodBetweenPulses = ZeroTimeout + 1000;
volatile unsigned long PeriodAverage = ZeroTimeout + 1000;
unsigned long FrequencyRaw;
unsigned long FrequencyReal;
unsigned long RPM;
unsigned int PulseCounter = 1;
unsigned long PeriodSum;

unsigned long LastTimeCycleMeasure = LastTimeWeMeasured;    
unsigned long CurrentMicros = micros();    // Get the current microsecond reading
unsigned int AmountOfReadings = 1;
unsigned int ZeroDebouncingExtra;
unsigned long readings[numReadings];    // Array to store the last RPM readings for averaging
unsigned long readIndex;    
unsigned long total; 
unsigned long average;

// Define a structure for the CAN message
struct can_frame canMsg;

// Initialize the MCP2515 CAN controller with CS pin 10
MCP2515 mcp2515(10);

void setup() 
{
    Serial.begin(9600);    // Initialize serial communication at 9600 baud rate
    attachInterrupt(digitalPinToInterrupt(3), Pulse_Event, RISING);    // Attach an interrupt to pin 3 to detect pulses (RISING edge)

    // Initialize and set up the MCP2515 CAN controller
    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS);
    mcp2515.setNormalMode();

    delay(1000);    // Delay for 1 second
}

void loop() 
{
    // Calculate time since last measurement
    LastTimeCycleMeasure = LastTimeWeMeasured;
    CurrentMicros = micros();
    if (CurrentMicros < LastTimeCycleMeasure) LastTimeCycleMeasure = CurrentMicros;

    // Calculate frequency using the period average
    FrequencyRaw = 10000000000 / PeriodAverage;

    // Check if wheel is stationary or not
    if (PeriodBetweenPulses > ZeroTimeout - ZeroDebouncingExtra || CurrentMicros - LastTimeCycleMeasure > ZeroTimeout - ZeroDebouncingExtra) 
    {
        FrequencyRaw = 0;
        ZeroDebouncingExtra = 2000;
    } 
    else 
    {
        ZeroDebouncingExtra = 0;
    }

    FrequencyReal = FrequencyRaw / 10000;
    RPM = FrequencyRaw / PulsesPerRevolution * 60;    // Calculate RPM using the raw frequency
    RPM = RPM / 10000;

    // Logic for averaging the RPM readings
    total = total - readings[readIndex];
    readings[readIndex] = RPM;
    total = total + readings[readIndex];
    readIndex = readIndex + 1;
    if (readIndex >= numReadings) readIndex = 0;
    average = total / numReadings;

    // Prepare CAN message and send
    canMsg.can_id  = 0x0F6;
    canMsg.can_dlc = 2;
    canMsg.data[0] = 0xFF;
    canMsg.data[1] = 0xFF;
    mcp2515.sendMessage(&canMsg);

    // Print relevant data to Serial monitor
    Serial.print("Period: ");
    Serial.print(PeriodBetweenPulses);
    Serial.print("\tReadings: ");
    Serial.print(AmountOfReadings);
    Serial.print("\tFrequency: ");
    Serial.print(FrequencyReal);
    Serial.print("\tRPM: ");
    Serial.print(RPM);
    Serial.print("\tTachometer: ");
    Serial.println(average);
    int rpm_integer = static_cast<int>(RPM);
    Serial.print("\tRPM(int): ");
    Serial.println(rpm_integer);
}

void Pulse_Event() 
{
    // Calculate the period between two consecutive pulses
    PeriodBetweenPulses = micros() - LastTimeWeMeasured;
    LastTimeWeMeasured = micros();

    // Logic to determine the average period based on the number of readings taken
    if (PulseCounter >= AmountOfReadings)  
    {
        PeriodAverage = PeriodSum / AmountOfReadings;
        PulseCounter = 1;
        PeriodSum = PeriodBetweenPulses;

        int RemapedAmountOfReadings = map(PeriodBetweenPulses, 40000, 5000, 1, 10);
        RemapedAmountOfReadings = constrain(RemapedAmountOfReadings, 1, 10);
        AmountOfReadings = RemapedAmountOfReadings;
    } 
    else 
    {
        PulseCounter++;
        PeriodSum = PeriodSum + PeriodBetweenPulses;
    }
}
