
//secelct choosen pins for readout
#include <math.h> //math needed for temerature calculation
#include <PID_v1.h> // PID library

#define thermistorPin A0
#define SerialRate 9600 //the same as in the python code

int portFan = 3; //configure the ports
int portRPM = 2;
int portLED = 13;

int counts = 0;
int rpm;
double fanSpeed = 100;
int V0; //Voltage measured at the thermistor
float T0 = 298.15; // configuration temperature of the thermistor
float R;
double Temperature;
float R0 = 100000.0;
float constB =  -4600;
double cKp = 200, cKi = 100, cKd = 150;  //the parameters of the PID algorithm
double Setpoint, Input, Output;
boolean newData = false;

PID myPID(&Temperature, &fanSpeed, &Setpoint, cKp, cKi, cKd, REVERSE); //PID is set to reverse as it is used for cooling

void counter(){
  counts++;
}

float functionTemperature(int Voltage)
{
    R = R0 * (1023/(float)Voltage - 1);
    float local_Temperature = 1.0/((log(R/R0)/constB) + (1.0/T0)) - 273.15;
    return local_Temperature;
}

void setup() {
  pinMode(portLED, OUTPUT);
  pinMode(portFan, OUTPUT);
  pinMode(portRPM, INPUT);
  Serial.begin(SerialRate);
  attachInterrupt(digitalPinToInterrupt(portRPM), counter, RISING); //runs function counter as soon signal is rising

  Setpoint = 25; //initialise the setpoint in [°C]
  int initVoltage = analogRead(thermistorPin);
  Temperature = functionTemperature(initVoltage);
  
  myPID.SetMode(AUTOMATIC);
}

void loop(){
    analogWrite(portFan, fanSpeed);
    counts = 0;
    
    sei(); //enable interrupts
    delay(500);
    cli(); //disable interrupt
    
    rpm = int(counts*2.*60./2.);
  
    V0 = analogRead(thermistorPin);
    Temperature = functionTemperature(V0);
    
    myPID.SetTunings(cKp, cKi, cKd); 

    myPID.Compute();
    
    Serial.println(42); //used in to encode the signal start
    Serial.println(millis());
    Serial.println(V0);
    Serial.println(rpm);
    Serial.println(Temperature);
}
