#define soundPin 7          // digital output pin of sound sensor
#define LED_BUILDIN 13      // LED pin (built-in LED)

int Sound_out = LOW;
unsigned long previousMillis = 0;
const long interval = 5000; // LED stays ON for 5 seconds

void setup() {
  Serial.begin(9600);
  pinMode(soundPin, INPUT);       // sound sensor input
  pinMode(LED_BUILDIN, OUTPUT);   // LED output
}

void loop() {
  unsigned long currentMillis = millis();
  Sound_out = digitalRead(soundPin);

  if (Sound_out == HIGH) {
    Serial.println("Sound Detected");
    digitalWrite(LED_BUILDIN, HIGH);   // LED ON
    delay(200);                        // debounce
  }

  // turn off LED after 5 seconds
  if (currentMillis - previousMillis >= interval) {
    digitalWrite(LED_BUILDIN, LOW);
    previousMillis = currentMillis;
  }
}
