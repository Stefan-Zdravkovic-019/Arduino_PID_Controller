README

This project involves using a PID controller to manage the speed of a CPU cooler based on the CPU temperature. The system consists of a Python script that reads CPU temperature using the OpenHardwareMonitor and communicates with an Arduino to control the fan speed.
A good portion of code is commented out, I did this out of troubleshooting/need to remove certain parts I felt were interfering with the rest of the code.
Components

    Python Script: Reads CPU temperature and sends the value to the Arduino.
    Arduino Code: Controls the fan speed based on the temperature value received from the Python script using a PID controller.

Requirements
Hardware

    Arduino Uno
    CPU cooler
    Jumper wires
    USB cable for Arduino

Software

    Python 3.x
    pyserial library
    wmi library
    Arduino IDE
    OpenHardwareMonitor

Setup and Installation
Python Script

    Install the required Python libraries:

    pip install pyserial wmi

    Ensure OpenHardwareMonitor is running on your system.

    Connect the Arduino to your computer.

Arduino Code

    Open the Arduino IDE and upload the provided Arduino code to your Arduino Uno.

    Ensure the connections are made as follows:
        PWM pin (pin 9) to the fan control pin.
        Tachometer pin (pin 2) to the fan tachometer pin.
	Ground pin goes to Ground.
	5v(12v) to 12v connector.

Usage
Running the Python Script

    Ensure the Arduino is connected to the correct COM port (adjust in the Python script if necessary).
    Run the Python script:
    python script.py

Arduino Code

    The Arduino will read the temperature value from the serial input and adjust the fan speed based on the PID controller's output.
    The temperature setpoint, PID constants, and input/output limits can be adjusted in the Arduino code.

Code Explanation
Python Script

    The script initializes a connection to the Arduino on COM3 and sets up a function write_read to send and receive data.
    It uses the wmi library to read the CPU temperature from OpenHardwareMonitor.
    The temperature value is sent to the Arduino, and the response (fan speed and PWM values) is read and printed.

Arduino Code

    The Arduino code initializes the PID controller and sets up the pins for PWM and tachometer.
    In the loop function, the Arduino reads the temperature value from the serial input, maps it to a suitable range, and computes the PID output.
    The fan speed is controlled using the analogWrite function based on the PID output.

Troubleshooting

    When COM is being used by one program the other cant use it, stop using serial monitor/plotter in arduino IDE if you want to run the python script, if your python script is running you wont be able to use serial monitor/plotter. 
    If you want to edit the Arduino code while Python code is running you will get an error due to COM port being in use by Python.

Notes

    The PID constants (Kp, Ki, Kd) may need to be tuned based on your specific hardware setup.
    Adjust the Setpoint value in the Arduino code to match the desired CPU temperature.

