const int LED_two = 8;         
const long blink_intervall1 = 500; //in milliseconds
const long blink_intervall2 = 250; //in milliseconds
unsigned long last_time_1 = 0; 
unsigned long last_time_2 = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_two, OUTPUT);

}
void loop() {
    unsigned long current_time_1 = millis();
    if(current_time_1 - last_time_1 >= blink_intervall1)
      {
        if(digitalRead(LED_BUILTIN) == LOW) //change the state of the LED
          {
            digitalWrite(LED_BUILTIN, HIGH);
          }
         else
          {
            digitalWrite(LED_BUILTIN, LOW);
          }
          last_time_1 = current_time_1; //set the last time to the new time if the state of the led was changed
      }
      else
      {
        current_time_1 = millis(); 
      }
    unsigned long current_time_2 = millis();
    if(current_time_2 - last_time_2 >= blink_intervall2)
      {
        if(digitalRead(LED_two) == LOW) //change the state of the LED
          {
            digitalWrite(LED_two, HIGH);
          }
         else
          {
            digitalWrite(LED_two, LOW);
          }
          last_time_2 = current_time_2;
      }
      else
      {
        current_time_2 = millis(); 
      }
}
