/*
 * Project: Smoke and Gas Detector Alarm System (v1 - Basic LED & Buzzer)
 * Author: Aakash Ahirwar
 * Description: Reads analog values from an MQ2 gas/smoke sensor.
 *              Triggers a Red LED and Buzzer when gas exceeds the threshold;
 *              illuminates a Green LED when air is clean.
 */

const int mq2Pin = A0;
const int redLED = 6;
const int greenLED = 7;
const int buzzer = 8;

const int threshold = 300; // Adjust based on ambient environment calibration

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int gasValue = analogRead(mq2Pin);
  Serial.print("Gas Level: ");
  Serial.println(gasValue);

  if (gasValue > threshold) {
    // Smoke/Gas detected
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzer, HIGH);
  } else {
    // Air is clean
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, LOW);
  }

  delay(500);
}