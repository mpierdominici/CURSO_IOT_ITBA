#define PIN_LED_VERDE D1
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(PIN_LED_VERDE, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(PIN_LED_VERDE, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(PIN_LED_VERDE, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); // wait for a second
  for(int i=0;i<10;i++){
    analogWrite(PIN_LED_VERDE,i*103);
    delay(500);
  }
}
