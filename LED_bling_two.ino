#define LED_one //TODO
#define LED_two //TODO

void setup() {
  pinMode(LED_one, OUTPUT);
  pinMode(LED_two, OUTPUT);

}
void blink(long intervall, int LED_pin)
  {
    unsigned long last_time = 0;
    unsigned long current_time = millis();
    if(current_time - last_time > intervall)
      {
        if(digitalRead(LED_pin) == LOW) //change the state of the LED
          {
            digitalWrite(LED_pin, HIGH);
          }
         else
          {
            digitalWrite(LED_pin, LOW);
          }
          last_time = current_time;
      }
      else
        {
          current_time = millis(); 
        }
  }

void loop() {
  const long blink_intervall1 = 500; //in milliseconds
  const long bling_intervall2 = 300; //in milliseconds
  blink(blink_intervall1, LED_one);
  blink(blink_intervall2, LED_two);

}
