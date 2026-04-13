# EASY LINK 핀맵 — ESP32-WROOM-32E (Rev 1.0)

> GitHub 동기용 요약. 원본·이미지는 Obsidian `EASYLINK-PRO/HARDWARE/EASY_LINK_핀맵_ESP32-WROOM32E` 참고.

## 통신 버스

| GPIO | 네트망 | 기능 |
|------|--------|------|
| 17 | 485_TX | RS485 TX → 드라이버 DI |
| 16 | 485_RX | RS485 RX ← 수신기 RO |
| 27 | 232_TX | RS232 |
| 26 | 232_RX | RS232 |
| 22 | LCD_SCL | I2C SCL |
| 21 | LCD_SDA | I2C SDA |
| 23 | SPI_MOSI | SPI |
| 19 | SPI_MISO | SPI |
| 18 | SPI_SCK | SPI |
| 5 | SPI_CS | SPI CS |

## 디지털 입력

| GPIO | 네트망 |
|------|--------|
| 34 | WET_DI1 |
| 35 | WET_DI2 |
| 32 | DRY_DI1 |
| 33 | DRY_DI2 |

IO34/35는 입력 전용(내장 풀업 없음).

## 코드 매크로

`arduino/include/easylink_pins.h` 와 동일.
