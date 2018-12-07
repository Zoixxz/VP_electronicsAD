
//secelct choosen pins for readout
#include <math.h> //math needed for temerature calculation
#include <PID_v1.h> // PID library

#define thermistorPin A0
#define SerialRate 9600 //the same as in the python code
#define operationModePID DIRECT
#define threshold 10// threshold set to 10 degrees celsius
int portFan = 3;
int portRPM = 2;
int portLED = 13;
int counts = 0;
int rpm;
int fanSpeed = 100;
int V0; //Voltage measured at the thermistor
float T0 = 298.15; // initial temperature
float R;
float Temperature;
float R0 = 100000.0;
float constB =  -4600;
float cKp = 1, cKi = 0.05, cKd = 0.25;  //@TODO define the conservative parameters
float aKp = 4, aKi = 0.2, aKd = 1;      //@TODO define the aggressive parameters
float Setpoint, Input, Output;
boolean newData = false;

PID myPID(&Temperature, &fanSpeed, &Setpoint, Kp, Ki, Kd, operationModePID); //set up PID @TODO:direct or indirect?

void counter(){
  counts++;
}

float functionTemperature(int Voltage)
{
    R = R0 * (1023/(float)Voltage - 1);
    int local_Temperature = 1.0/((log(R/R0)/constB) + (1.0/T0)) - 273.15;
    return local_Temperature;
}

void setup() {
  pinMode(portLED, OUTPUT);
  pinMode(portFan, OUTPUT);
  pinMode(portRPM, INPUT);
  Serial.begin(SerialRate);
  attachInterrupt(digitalPinToInterrupt(portRPM), counter, RISING); //runs function counter as soon signal is rising

  Setpoint = 30; //initialise the setpoint in degrees celsius
  int initVoltage = analogRead(thermistorPin);
  Temperature = functionTemperature(initVoltage);
  
  myPID.SetMode(AUTOMATIC);
}

void loop(){
    analogWrite(portFan, fanSpeed);
    counts = 0;
    sei(); //enable interrupts
    delay(500);
    cli(); //disable interrups
    rpm = int(counts*2.*60./2.);

    V0 = analogRead(thermistorPin);
    Temperature = functionTemperature(V0);
    
    float gap = abs(Temperature - Setpoint);
    if(gap < threshold)
    {
      myPID.SetTunings(cKp, cKi, cKd); //conservative tuning parameters
    }
    else
    {
      myPID.SetTunings(aKp, cKi, cKd); //aggressive tuning parameters
    }
    myPID.Compute();
    
    Serial.println(millis());
    Serial.println(V0);
    Serial.println(rpm);
    Serial.println(Temperature);

    
}
