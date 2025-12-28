#include <SoftwareSerial.h>

// -------- PIN DEFINITIONS --------
#define PIEZO_PIN A0
#define SOUND_PIN 2
#define LED_PIN 8

#define GSM_RX 10   // Arduino RX ← SIM800L TX
#define GSM_TX 11   // Arduino TX → SIM800L RX

// -------- GSM --------
SoftwareSerial gsm(GSM_RX, GSM_TX);

// -------- THRESHOLDS --------
int piezoThreshold = 120;     // Adjust based on testing
bool smsSent = false;

void sendSMS() {
  gsm.println("AT+CMGF=1");  // Text mode
  delay(1000);

  gsm.println("AT+CMGS=\"+639XXXXXXXXX\""); // <-- CHANGE NUMBER
  delay(1000);

  gsm.print("Alert! Knock or doorbell sound detected.");
  delay(500);

  gsm.write(26); // CTRL+Z to send SMS
  delay(5000);
}

void setup() {
  pinMode(SOUND_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
  gsm.begin(9600);

  digitalWrite(LED_PIN, LOW);

  delay(3000);
  Serial.println("System Ready");
}

void loop() {
  int piezoValue = analogRead(PIEZO_PIN);
  int soundValue = digitalRead(SOUND_PIN);

  Serial.print("Piezo: ");
  Serial.print(piezoValue);
  Serial.print(" | Sound: ");
  Serial.println(soundValue);

  // Knock OR Doorbell detected
  if ((piezoValue > piezoThreshold || soundValue == HIGH) && !smsSent) {
    digitalWrite(LED_PIN, HIGH);
    sendSMS();
    smsSent = true; // Prevent SMS spam
  }

  // Reset system when quiet
  if (piezoValue < 50 && soundValue == LOW) {
    digitalWrite(LED_PIN, LOW);
    smsSent = false;
  }

  delay(200);
}
