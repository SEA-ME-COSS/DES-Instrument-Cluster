# Basic Concepts :

1. **Pulse:** The sensor used in this code generates a pulse with each rotation. It's assumed here that two pulses are generated per revolution. This pulse is a digital signal produced a set number of times as the sensor completes one full rotation.  
2. **Period:** It refers to the time between two consecutive pulses. For instance, if pulses occur every 1ms, then the period is 1ms. 
3. **Frequency:** It denotes the number of pulses in a unit of time. It can be calculated as the inverse of the period. For example, if the period is 1ms, then the frequency is 1000Hz or 1kHz.

# How the Code Works :

1. **Detecting Pulses:** The attachInterrupt() function is used to detect pulses from the sensor. Every time a pulse is generated, the Pulse_Event() function is invoked. 
2. **Calculating the Period:** Inside the Pulse_Event() function, the difference between the time the last pulse occurred (LastTimeWeMeasured) and the time the current pulse occurred (micros()) is calculated to determine the period (PeriodBetweenPulses). 
3. **Calculating Frequency:** Within the main loop(), the frequency (FrequencyRaw) is calculated using the average period (PeriodAverage).
4. **Calculating RPM:** As we know the number of pulses per revolution (PulsesPerRevolution), the RPM can be determined using the frequency. This frequency is multiplied by 60 to convert it to revolutions per minute and then divided by the number of pulses per revolution.

# How does this represent speed?

Frankly, this code isn't directly measuring "speed." It's measuring the revolutions per minute (RPM), which indicates how many times a wheel rotates in a minute. 

If you know the diameter or circumference of the wheel, you can calculate the actual speed (e.g., km/h or m/s) using the RPM. This calculation would follow the formula: 

Speed=RPM×Circumference

$$
Speed = RPM \times Circumference
$$

For instance, if the wheel's circumference is 2m and the RPM is 30, the speed would be 3**0 x 2 = 60m/min** or **1m/s**. 

So, while the code doesn't provide speed directly, it offers the foundational rotational data that, combined with additional information (like wheel circumference), can facilitate this.

If you want to know more about it, go to our "arduino _can" repo