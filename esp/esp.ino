#include <Arduino.h>
#include <LovyanGFX.hpp>
#include "lgfxesp32c3.hpp"

MyLGFX lcd;

const int SENSOR_PIN = 4;

const int BUZZ1 = 1;
const int BUZZ2 = 2;
const int BUZZ3 = 3;

const int PWM_BITS = 8;
const int DUTY = 128;

void startChord(int f1, int f2, int f3) {
  ledcAttach(BUZZ1, f1, PWM_BITS);
  ledcAttach(BUZZ2, f2, PWM_BITS);
  ledcAttach(BUZZ3, f3, PWM_BITS);

  ledcWrite(BUZZ1, DUTY);
  ledcWrite(BUZZ2, DUTY);
  ledcWrite(BUZZ3, DUTY);
}

void changeChord(int mode) {
  if (mode == 0) {
    startChord(523, 659, 784);
  } else if (mode == 1) {
    startChord(587, 740, 880);
  } else {
    startChord(392, 494, 587);
  }
}

void setup() {
  lcd.init();
  lcd.setRotation(3);
  lcd.setBrightness(128);

  lcd.fillScreen(0x000000U);
  lcd.setTextColor(0x00FF00U, 0x000000U);
  lcd.setTextSize(2);

  lcd.setCursor(10, 10);
  lcd.println("PWM Chord Test");

  changeChord(0);
}

void loop() {
  static unsigned long lastChange = 0;
  static int chordMode = 0;

  int value = analogRead(SENSOR_PIN);

  if (millis() - lastChange > 2000) {
    lastChange = millis();
    chordMode = (chordMode + 1) % 3;
    changeChord(chordMode);
  }

  lcd.fillRect(0, 45, 320, 180, 0x000000U);

  lcd.setCursor(10, 55);
  lcd.print("ADC: ");
  lcd.println(value);

  lcd.setCursor(10, 90);
  lcd.print("Chord: ");
  lcd.println(chordMode);

  lcd.setCursor(10, 125);
  lcd.print("Time: ");
  lcd.print(millis() / 1000);
  lcd.println(" s");

  int barWidth = map(value, 0, 4095, 0, 300);
  lcd.drawRect(10, 165, 300, 20, 0x00FF00U);
  lcd.fillRect(10, 165, barWidth, 20, 0x00FF00U);


  delay(50);
}