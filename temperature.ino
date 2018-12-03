int fanSpeed = 0;
int V0; //Voltage measured at the thermistor
float T0 = 289.15; // initial temperature
#define SerialRate 9600 //the same as in the python shell
#define R0 //TODO  
#define thermistorPin //TODO
#define constB //TODO

void setup(){
  Serial.begin(SerialRate);
  Serial.println("print ready");
  pinMode(fan, OUTPUT);
  }
void loop(){
    V0 = analogRead(thermistorPin);
    R = R0 * (1023/(float)V0 - 1);
    Temperature = 1.0/((log(R/R0)/constB) + (1.0/T0));
    
    analogWrite(fan, fanSpeed);
    
    if(Serial.available()){
      int fanSpeed = Serial.read();  //fan speed needs to be set
      Serial.print(fanSpeed, DEC);
      Serial.print(";");
      Serial.print(Temperature, DEC);
      Serial.print(";");
      Serial.println(millis());      
      }
      delay(1000);
  }
