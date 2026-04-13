//**********************************************************************************//
//* HTA JO-H                                                                    *//
//* EASY LINK PRO — SPI W5500 이더넷 예제                                            *//
//*--------------------------------------------------------------------------------*//
//* 1.Description : MOSI/MISO/SCK/CS 핀맵에 맞춰 W5500 초기화 후 DHCP 로 IP 획득      *//
//* 2.Protocol    : SPI, Ethernet                                                   *//
//* 3.DataBase    : N/A                                                             *//
//* 4.Create      : 2026/04/13_JO-H                                                 *//
//* 5.Release     : 2026/04/13                                                      *//
//* 6.Version     : V1.00_Release                                                   *//
//* 7.History     :                                                                 *//
//* 1) Version 1.00: 최초 작성                                                       *//
//**********************************************************************************//

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include "easylink_pins.h"

// [INIT] MAC 은 네트워크에서 유일해야 함. 필요 시 변경
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println(F("[INIT] EASY LINK W5500 (SPI) 예제"));

  // [INIT] SPI 핀 — 회로도 서비스 헤더와 동일
  SPI.begin(PIN_SPI_SCK, PIN_SPI_MISO, PIN_SPI_MOSI, PIN_SPI_CS);
  Ethernet.init(PIN_SPI_CS);

  Serial.println(F("[LOGIC] DHCP 요청 중..."));
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("[ERROR] DHCP 실패. 케이블·허브·SPI 배선 확인"));
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println(F("[ERROR] W5500 칩 인식 실패 (배선/전원)"));
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println(F("[ERROR] 링크 다운 (케이블)"));
    }
    for (;;)
      delay(1000);
  }

  Serial.print(F("[LOGIC] IP: "));
  Serial.println(Ethernet.localIP());
  Serial.print(F("[LOGIC] GW: "));
  Serial.println(Ethernet.gatewayIP());
}

void loop() {
  // [LOGIC] Ethernet 유지 — DHCP 리스 갱신
  Ethernet.maintain();
  static uint32_t t = 0;
  if (millis() - t > 10000) {
    t = millis();
    Serial.print(F("[LOGIC] IP 유지: "));
    Serial.println(Ethernet.localIP());
  }
  delay(200);
}
