import serial
import time
import wmi

try:
    arduino = serial.Serial(port='COM3', baudrate=9600, timeout=1)
except Exception as e:
    print("No Arduino connected")
finally:
    print("Program start")


def write_read(x):
    arduino.write(bytes(str(x), 'utf-8'))  # Add newline character for Arduino parseInt
    data = arduino.readline().decode('utf-8').strip()  # Read the response from Arduino
    return data


# inp = input("SET INPUT: ")
# write_read(inp)
#

w = wmi.WMI(namespace="root\\OpenHardwareMonitor")
while True:
    for sensor in w.Sensor():
        if sensor.SensorType == u'Temperature' and "CPU Package" in sensor.Name:
            try:
                # Send temperature value to Arduino
                temp_value = sensor.Value
                # temp_value = 45
                print(f"{temp_value}")

                # Send the temperature value to Arduino and read the response
                response = write_read(temp_value)
                print(f"Response: {response}")
                print("\n")

                # Parse RPM and PWM values from Arduino response
                # if response.startswith("Output Value:"):
                #     data_parts = response.split(", ")
                #     rpm_value = data_parts[0].split(":")[1]
                #     pwm_value = data_parts[1].split(":")[1]
                #     print("RPM: {rpm_value}, PWM: {pwm_value}")

                time.sleep(1)
            except Exception as e:
                print(e)
                continue
