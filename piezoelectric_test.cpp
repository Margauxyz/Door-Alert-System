const int sensorPin = 7; 
int sensorValue = 0;

void setup(){
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop(){
  sensorValue = digitalRead(sensorPin);
  if(sensorValue == HIGH){
    Serial.println("someone knocking");
    delay(2000);
  }
}
