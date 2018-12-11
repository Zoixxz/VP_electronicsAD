#include <Wire.h>
#include "rgb_lcd.h"
#include <math.h>

#define SerialRate 9600

rgb_lcd lcd;

const int colorR = 200;
const int colorG = 200;
const int colorB = 200;

const int pinTempSensor = A0;
const int rotaryAngleSensor = A1;
const int B = 4275;               // B value of the thermistor
const int R0 = 100000;
float threshold = 25;        

void setup() {
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
    pinMode(rotaryAngleSensor, INPUT);
    pinMode(pinTempSensor, INPUT);
    Serial.begin(SerialRate);
    delay(1000);
    
}

void loop() {
    //read rotary angle
    float sensor_value = analogRead(rotaryAngleSensor);
    threshold = map(sensor_value, 0, 1023, 20, 40);
    
    int V0 = analogRead(pinTempSensor);
    float R = 1023.0/V0-1.0;
    R = R0*R;
    
    float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
    if(temperature> threshold){
      lcd.setRGB(200, 0, 0);
    }
    else{
      lcd.setRGB(colorR, colorG, colorB);
    }
    lcd.setCursor(0, 0);
    lcd.print("time = ");
    lcd.print(millis()/1000);
    lcd.print("s");
    lcd.setCursor(0, 1);
    lcd.print("temp = ");
    lcd.print(temperature);
    lcd.print("C");
    delay(100);
    Serial.println(4242);
    Serial.println(millis());
    Serial.println(threshold);
    Serial.println(temperature);
    
}
