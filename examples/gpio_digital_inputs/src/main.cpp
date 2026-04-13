//**********************************************************************************//
//* HTA JO-H                                                                    *//
//* EASY LINK PRO — 디지털 입력 (젖은/건 접점) 예제                                   *//
//*--------------------------------------------------------------------------------*//
//* 1.Description : WET_DI1/2, DRY_DI1/2 핀 상태를 시리얼로 주기 출력                   *//
//* 2.Protocol    : GPIO                                                            *//
//* 3.DataBase    : N/A                                                             *//
//* 4.Create      : 2026/04/13_JO-H                                                 *//
//* 5.Release     : 2026/04/13                                                      *//
//* 6.Version     : V1.00_Release                                                   *//
//* 7.History     :                                                                 *//
//* 1) Version 1.00: 최초 작성                                                       *//
//**********************************************************************************//

#include <Arduino.h>
#include "easylink_pins.h"

// [NOTE] IO34/35는 입력 전용, 내장 풀업 없음. 회로에 풀업/풀다운 있는지 확인.

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println(F("[INIT] EASY LINK 디지털 입력 예제"));

  pinMode(PIN_WET_DI1, INPUT);
  pinMode(PIN_WET_DI2, INPUT);
  pinMode(PIN_DRY_DI1, INPUT);
  pinMode(PIN_DRY_DI2, INPUT);
}

void loop() {
  int w1 = digitalRead(PIN_WET_DI1);
  int w2 = digitalRead(PIN_WET_DI2);
  int d1 = digitalRead(PIN_DRY_DI1);
  int d2 = digitalRead(PIN_DRY_DI2);

  Serial.printf("[LOGIC] WET_DI1=%d WET_DI2=%d DRY_DI1=%d DRY_DI2=%d\n", w1, w2, d1, d2);
  delay(500);
}
