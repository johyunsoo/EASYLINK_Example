//**********************************************************************************//
//* HTA JO-H                                                                    *//
//* EASY LINK PRO — GPIO / 버스 핀 정의 (회로도 Rev 1.0)                              *//
//*--------------------------------------------------------------------------------*//
//* *//
//* 1.Description : EASY LINK 보드(ESP32-WROOM-32E) 핀맵을 코드에서 단일 소스로 쓰기 위한 헤더 *//
//* 2.Protocol    : I2C, SPI, UART(Modbus RTU), GPIO DI                               *//
//* 3.DataBase    : N/A                                                             *//
//* 4.Create      : 2026/04/13_JO-H                                                 *//
//* 5.Release     : 2026/04/13                                                      *//
//* 6.Version     : V1.00_Release                                                   *//
//* 7.History     :                                                                 *//
//* 1) Version 1.00: Obsidian EASY_LINK_핀맵_ESP32-WROOM32E 와 동기                  *//
//**********************************************************************************//

#ifndef EASYLINK_PINS_H
#define EASYLINK_PINS_H

// [PINMAP] 회로도 EASY LINK Rev 1.0 (2023-04-24) 기준. 변경 시 Obsidian 핀맵 먼저 수정.

// RS485 (MAX13487, TX=17 / RX=16) — UART 번호는 스케치에서 Serial1 등으로 매핑
#define PIN_RS485_TX 17
#define PIN_RS485_RX 16

// RS232 (SP3232, TX=27 / RX=26)
#define PIN_RS232_TX 27
#define PIN_RS232_RX 26

// I2C (보드 LCD 헤더 네트망: SCL / SDA) — 0.96" OLED 등
#define PIN_I2C_SCL 22
#define PIN_I2C_SDA 21

// SPI (서비스 헤더: MOSI MISO SCK CS)
#define PIN_SPI_MOSI 23
#define PIN_SPI_MISO 19
#define PIN_SPI_SCK 18
#define PIN_SPI_CS 5

// 디지털 입력 (광접 / 건접)
#define PIN_WET_DI1 34
#define PIN_WET_DI2 35
#define PIN_DRY_DI1 32
#define PIN_DRY_DI2 33

// [NOTE] IO34/35는 입력 전용(풀업 없음). 외부 회로 극성 맞출 것.

#endif
