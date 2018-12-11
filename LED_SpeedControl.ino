
//secelct choosen pins for readout
#include <math.h>
int portfan = 3;
int portrpm = 2;
int portled = 13;
int counts = 0;
int rpm;
int spd = 0;
int V0; //Voltage measured at the thermistor
float T0 = 298.15; // initial temperature
float R;
float Temperature;
#define SerialRate 9600 //the same as in the python shell
float R0 = 100000.0;
#define thermistorPin A0
float constB =  -4600;

void counter(){
  counts++;
}


void setup() {
  pinMode(portled, OUTPUT);
  pinMode(portfan, OUTPUT);
  pinMode(portrpm, INPUT);
  Serial.begin(SerialRate);
  attachInterrupt(digitalPinToInterrupt(portrpm),counter, RISING); //runs function counter as soon signal is rising
}
void loop(){
    if(!Serial.available()){
    char inChar = Serial.read();
    spd = int(inChar);
    analogWrite(portfan, spd);
    Serial.println(spd);
    counts = 0;
    sei(); //enable interrupts
    digitalWrite(portled, HIGH);
    delay(200);
    digitalWrite(portled,LOW);
    delay(200);
    cli(); //disable interrups
    rpm = int(counts*5.*60./2.);

    V0 = analogRead(thermistorPin);
    R = R0 * (1023/(float)V0 - 1);
    Temperature = 1.0/((log(R/R0)/constB) + (1.0/T0));
    Serial.println(V0);
    Serial.println(rpm);
    Serial.println(Temperature-273.15);
    Serial.println(millis());
    }
}
