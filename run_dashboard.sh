#!/bin/bash

# 1. Setting for CAN
echo "Setting up CAN..."
sudo ip link set can0 up type can bitrate 500000
sudo ifconfig can0 txqueuelen 65536
echo "CAN setup complete."

# 2. Speedstatus.c compile and run
echo "Compiling and executing speedstatus.c..."
cd ./Instrument-Cluster/dbus_clients/
rm -rf speedstatus_execution
make
./speedstatus_execution > /dev/null 2>&1 &

echo "speedstatus_execution is running."

# 3. batterystatus.py 실행
echo "Executing batterystatus.py..."
python3 batterystatus.py > /dev/null 2>&1 &
cd ..
echo "batterystatus.py is running."

# 5. Piracer 조절 코드 실행
echo "Starting gamepad control for Piracer..."
python3 ./piracer_handler/gamepad_control.py > /dev/null 2>&1 &
echo "Piracer gamepad control is running."

# 4. Qt dashboard 실행
echo "Starting the Qt dashboard..."
./dashboard --platform linuxfb
echo "Qt dashboard is running."


echo "All tasks have been started!"
