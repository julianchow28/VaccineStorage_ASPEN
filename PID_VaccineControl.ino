#include <PID_v1.h> // need this package

int ThermistorPin1 = 3;
int ThermistorPin2 = 4;
int ThermistorPin3 = 5;
int V1,V2,V3;
float R1 = 10000;
float logR2_1, R2_1, T_1, Tc_1, Tf_1;
float logR2_2, R2_2, T_2, Tc_2, Tf_2;
float logR2_3, R2_3, T_3, Tc_3, Tf_3;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int icr, frecuency, duty_cycle;

int hotPin = 6; // output pin is PWM Output pin

// defining variables for PID
double Setpoint, Input, Output=100;
double Kp=20, Ki=0, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, REVERSE);

// for printing outputs
unsigned long previousMillis = 0;
const unsigned long interval = 1000; 

void setup() {

  Serial.begin(9600);
  pinMode(hotPin, OUTPUT);
  pinMode(11, OUTPUT);
  
  // Timer/Counter 1 initialization
  TCCR1A = 0xA2;
  TCCR1B = 0x19;
  TCNT1H = 0x00;
  TCNT1L = 0x00;

  duty_cycle = 110; // Change this value to the desired duty cycle (0-100 %)
  icr = 639; // icr and frecuency values are set to generate a 25 kHZ signal
  frecuency = 16000000 / (1 + icr);

  ICR1H = icr >> 8;
  ICR1L = icr & 0x00ff;
  // Sets the duty cycle with the value entered in line 12 
  OCR1A = icr * (duty_cycle / 100.0);

  float Tc_1 = readTemperature(ThermistorPin1);
  float Tc_2 = readTemperature(ThermistorPin2);
  float Tc_3 = readTemperature(ThermistorPin3);
  Input = median(Tc_1, Tc_2, Tc_3);
  Setpoint = 8;

  myPID.SetMode(AUTOMATIC);

}

float readTemperature(int pin) {
    int V = analogRead(pin);
    float R2 = R1 * (1023.0 / (float)V - 1.0);
    float logR2 = log(R2);
    float T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)) - 273.15;
    return T;
}

float median(float a, float b, float c) {
    if ((a >= b && a <= c) || (a >= c && a <= b)) return a;
    if ((b >= a && b <= c) || (b >= c && b <= a)) return b;
    return c;
}

void loop() {

  unsigned long elapsedTime = millis() / 1000; // to track elapsed time
  unsigned long currentMillis = millis(); // Get current time

  float Tc_1 = readTemperature(ThermistorPin1);
  float Tc_2 = readTemperature(ThermistorPin2);
  float Tc_3 = readTemperature(ThermistorPin3);
  Input = median(Tc_1, Tc_2, Tc_3);
  myPID.Compute();
  analogWrite(hotPin, Output);

  // Print data in CSV format (Thermistor 1/2/3, PID Input, PID Output, Kp, Ki, Kd, duty_cycle)
  if (currentMillis - previousMillis >= interval) { // Check if 1000ms have passed
    previousMillis = currentMillis; // Update last printed time
    Serial.print(elapsedTime);
    Serial.print(",");
    Serial.print(Tc_1);
    Serial.print(",");
    Serial.print(Tc_2);
    Serial.print(",");
    Serial.print(Tc_3);
    Serial.print(",");
    Serial.print(Input);
    Serial.print(",");
    Serial.print(Output);
    Serial.print(",");
    Serial.print(myPID.GetKp());
    Serial.print(",");
    Serial.print(myPID.GetKi());
    Serial.print(",");
    Serial.print(myPID.GetKd());
    Serial.print(",");
    Serial.println(duty_cycle);
  }

}