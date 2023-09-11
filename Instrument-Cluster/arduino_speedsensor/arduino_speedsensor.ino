#include <SPI.h>
#include <mcp2515.h>

// Data structure for CAN frame
struct can_frame canMsg1;
// Initialize MCP2515 instance with CS pin on 9
MCP2515 mcp2515(9);

// Define number of pulses per revolution
const byte PulsesPerRevolution = 20;
// Timeout duration for zero detection (100ms)
const unsigned long ZeroTimeout = 100000;
// Number of readings for RPM calculation
const byte numReadings = 2;

// Variables for pulse timing calculations
volatile unsigned long LastTimeWeMeasured;
volatile unsigned long PeriodBetweenPulses = ZeroTimeout + 1000;
volatile unsigned long PeriodAverage = ZeroTimeout + 1000;
unsigned long FrequencyRaw;
unsigned long FrequencyReal;
unsigned long RPM;
unsigned int PulseCounter = 1;
unsigned long PeriodSum;

// Variables for cycle timing and debouncing
unsigned long LastTimeCycleMeasure = LastTimeWeMeasured;
unsigned long CurrentMicros = micros();
unsigned int AmountOfReadings = 1;
unsigned int ZeroDebouncingExtra;
unsigned long readings[numReadings];
unsigned long readIndex;
unsigned long total;
unsigned long average;

void setup() 
{
  // Initialize serial communication at 115200 bps
  Serial.begin(115200);
  
  // Attach interrupt to pin 3 (speed sensor) for rising edge detection
  attachInterrupt(digitalPinToInterrupt(3), Pulse_Event, RISING);
  
  // Reset MCP2515 and configure CAN communication
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_16MHZ);
  mcp2515.setNormalMode();
}

void loop() 
{
  // Record start time of the current loop and end time of previous loop
  LastTimeCycleMeasure = LastTimeWeMeasured;
  CurrentMicros = micros();
  // Check for micros() overflow
  if (CurrentMicros < LastTimeCycleMeasure) 
  {
    LastTimeCycleMeasure = CurrentMicros;
  }

  // Calculate raw frequency based on average period between pulses
  FrequencyRaw = 10000000000 / PeriodAverage;

  // Check if wheel has stopped or not
  if (PeriodBetweenPulses > ZeroTimeout - ZeroDebouncingExtra || CurrentMicros - LastTimeCycleMeasure > ZeroTimeout - ZeroDebouncingExtra) 
  {
    FrequencyRaw = 0;  // Set frequency to 0
    ZeroDebouncingExtra = 2000;
  } 
  else 
  {
    ZeroDebouncingExtra = 0;
  }

  // Calculate actual real frequency (divided by 10,000)
  FrequencyReal = FrequencyRaw / 10000;

  // Calculate RPM based on raw frequency and number of pulses per revolution
  RPM = FrequencyRaw / PulsesPerRevolution * 60;
  RPM = RPM / 10000;

  // Update readings array for RPM averaging
  total = total - readings[readIndex];
  readings[readIndex] = RPM;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  // Check if readIndex exceeds numReadings
  if (readIndex >= numReadings) 
  {
    readIndex = 0;
  }
  // Calculate average RPM
  average = total / numReadings;

  // Print RPM to serial monitor
  Serial.print("RPM: ");
  Serial.println(RPM);

  // Prepare CAN message with RPM data
  canMsg1.can_id  = 0x0F6;
  canMsg1.can_dlc = 2;
  canMsg1.data[0] = (RPM & 0xFF00) >> 8;
  canMsg1.data[1] = (RPM & 0x00FF);

  // Send CAN message
  mcp2515.sendMessage(&canMsg1);
}

// Interrupt service routine for pulse event
void Pulse_Event() 
{
  // Calculate period between pulses and update last measurement time
  PeriodBetweenPulses = micros() - LastTimeWeMeasured;
  LastTimeWeMeasured = micros();

  // Calculate average period and adjust AmountOfReadings
  if (PulseCounter >= AmountOfReadings)  
  {
    PeriodAverage = PeriodSum / AmountOfReadings;
    PulseCounter = 1;
    PeriodSum = PeriodBetweenPulses;

    int RemappedAmountOfReadings = map(PeriodBetweenPulses, 40000, 5000, 1, 10);
    RemappedAmountOfReadings = constrain(RemappedAmountOfReadings, 1, 10);
    AmountOfReadings = RemappedAmountOfReadings;
  } 
  else 
  {
    PulseCounter++;
    PeriodSum = PeriodSum + PeriodBetweenPulses;
  }
}
