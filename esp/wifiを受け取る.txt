#include <LovyanGFX.hpp>
#include "lgfxesp32c3.hpp"

MyLGFX lcd;

const int SENSOR_PIN = 4;      // 受光部をつないだADCピンに変更
const int THRESHOLD = 10;    // 明るい/暗い判定のしきい値

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.setRotation(3);
  lcd.setBrightness(128);

  lcd.fillScreen(0x000000U);
  lcd.setTextColor(0x00FF00U, 0x000000U);
  lcd.setTextSize(2);

  lcd.setCursor(10, 10);
  lcd.println("Light Sensor Test");
}

void loop() {
  int value = analogRead(SENSOR_PIN);
  bool isLight = value > THRESHOLD;

  Serial.println(value);

  // 表示更新部分だけ消す
  lcd.fillRect(0, 50, 320, 120, 0x000000U);

  lcd.setCursor(10, 60);
  lcd.print("ADC: ");
  lcd.println(value);

  lcd.setCursor(10, 100);
  lcd.print("State: ");
  lcd.println(isLight ? "LIGHT" : "DARK");

  // 簡易バー表示
  int barWidth = map(value, 0, 4095, 0, 300);
  lcd.drawRect(10, 145, 300, 20, 0x00FF00U);
  lcd.fillRect(10, 145, barWidth, 20, 0x00FF00U);

  delay(50);
}