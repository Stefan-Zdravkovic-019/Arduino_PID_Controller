#include<PID_v1.h>

// Define pins
const int pwmPin = 9;   // PWM pin for fan control
const int tachPin = 2;  // Tachometer pin for reading fan speed


volatile unsigned long pulseCount = 0;
unsigned long lastMillis = 0;
const unsigned long interval = 1000;  // Interval to measure RPM (in milliseconds)


//PID STUFF HERE
double Setpoint;
double Input;
double Output;
double Kp = 3.0/*Maybe 2.0 here*/, Ki = 0.1, Kd = 0.5;  // Start with moderate values

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, REVERSE);

void setup() {
  Serial.begin(9600);

  Setpoint = 47;
  Serial.println("Setpoint set as: " + String(Setpoint)); //Serial.println(Setpoint);

  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(1, 254);
  myPID.SetTunings(Kp, Ki, Kd);


  pinMode(tachPin, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(tachPin), countPulse, FALLING);  //Attach an interrupt to the tachometer pin
}

void loop() {
  // Read the temperature value from the serial input
  if (Serial.available() > 0) {
     int value = Serial.parseInt();
     if (value != 0) {

      Serial.print ("Value: "); 
      Serial.println(value);

      Input = map(value, 0, 110, 1, 254);  // Adjust this mapping as necessary for your temperature sensor
      Serial.print("Input: "); Serial.print(Input);
      // Print the Output value for debugging

      myPID.Compute();
      
      Serial.print(" Output Value: ");
      Serial.print(Output);
      Serial.print(", ");
      


      // Control the fan speed based on PID output
      analogWrite(pwmPin, Output);

    }
  }




  // Calculate and print RPM every 'interval' milliseconds
  unsigned long currentMillis = millis();
  if (currentMillis - lastMillis >= interval) {
    lastMillis = currentMillis;
    unsigned long rpm = (pulseCount * 60) / 2;  // Calculate RPM
    pulseCount = 0;  // Reset pulse count
    // Serial.print("RPM: ");
    // Serial.println(rpm);
  }


}

// Interrupt service routine to count pulses
void countPulse() {
  pulseCount++;
}