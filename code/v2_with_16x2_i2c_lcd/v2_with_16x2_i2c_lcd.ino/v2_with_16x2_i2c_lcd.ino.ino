/*
 * Project: Smoke and Gas Detector Alarm System (v2 - With 16x2 I2C LCD)
 * Author: Aakash Ahirwar
 * Required Library: LiquidCrystal_I2C by Frank de Brabander
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int mq2Pin = A0;
const int redLED = 6;
const int greenLED = 7;
const int buzzer = 8;

const int threshold = 300; // Adjust based on testing environment

// Set LCD I2C address to 0x27 (try 0x3F if display stays blank)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Gas Detector");
  
  Serial.begin(9600);
  delay(1500);
  lcd.clear();
}

void loop() {
  int gasValue = analogRead(mq2Pin);
  Serial.print("Gas Level: ");
  Serial.println(gasValue);

  lcd.setCursor(0, 0);
  lcd.print("Gas Level: ");
  lcd.print(gasValue);
  lcd.print("   "); // Clears leftover trailing digits

  if (gasValue > threshold) {
    // Smoke/Gas detected
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzer, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Status: DANGER ");
  } else {
    // Air is clean
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Status: SAFE   ");
  }

  delay(500);
}