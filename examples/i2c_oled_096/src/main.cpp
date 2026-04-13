//**********************************************************************************//
//* HTA JO-H                                                                    *//
//* EASY LINK PRO — I2C 0.96" OLED (SSD1306) 예제                                   *//
//*--------------------------------------------------------------------------------*//
//* 1.Description : 핀맵 SDA=21, SCL=22 에 맞춰 OLED 초기화·문자 출력                  *//
//* 2.Protocol    : I2C                                                             *//
//* 3.DataBase    : N/A                                                             *//
//* 4.Create      : 2026/04/13_JO-H                                                 *//
//* 5.Release     : 2026/04/13                                                      *//
//* 6.Version     : V1.00_Release                                                   *//
//* 7.History     :                                                                 *//
//* 1) Version 1.00: 최초 작성                                                       *//
//**********************************************************************************//

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "easylink_pins.h"

// [INIT] OLED 128x64, I2C 주소 0x3C 가 흔함. 일부 모듈은 0x3D.
#define OLED_ADDR 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println(F("[INIT] EASY LINK I2C OLED 예제 시작"));

  // [INIT] I2C — 핀맵과 동일: SDA 21, SCL 22
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("[ERROR] SSD1306 찾기 실패. 배선·주소(0x3C/0x3D) 확인"));
    for (;;)
      delay(1000);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("EASY LINK"));
  display.println(F("I2C OLED 0.96"));
  display.printf("SDA=%d SCL=%d\n", PIN_I2C_SDA, PIN_I2C_SCL);
  display.display();
  Serial.println(F("[LOGIC] 화면 출력 완료"));
}

void loop() {
  // [LOGIC] 간단한 uptime 표시
  static uint32_t last = 0;
  if (millis() - last < 1000)
    return;
  last = millis();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("EASY LINK"));
  display.printf("uptime: %lu s\n", millis() / 1000);
  display.display();
  Serial.printf("[LOGIC] uptime %lu ms\n", (unsigned long)millis());
}
