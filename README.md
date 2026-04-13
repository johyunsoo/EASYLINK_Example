# EASYLINK-PRO (EASY LINK 보드 예제)

회로도 **EASY LINK Rev 1.0** · MCU **ESP32-WROOM-32E** 핀맵은 Obsidian 단일 문서  
`EASYLINK-PRO/HARDWARE/EASY_LINK_핀맵_ESP32-WROOM32E` 와 동기한다.

## 저장소 구조

| 경로 | 설명 |
|------|------|
| `arduino/include/easylink_pins.h` | 보드 핀 `#define` 단일 소스 |
| `arduino/include/wifi_secrets.h.example` | Wi-Fi/MQTT 설정 템플릿 → `wifi_secrets.h` 로 복사 |
| `docs/pinmap/` | GitHub용 핀맵 요약(옵시디안과 동일 내용) |
| `examples/*` | PlatformIO 예제 (폴더별 `pio run`) |

## 예제 목록

| 예제 | 버스·핀 | 내용 |
|------|---------|------|
| `examples/i2c_oled_096` | I2C SDA=21, SCL=22 | SSD1306 128×64 OLED에 텍스트 출력 |
| `examples/spi_w5500_ethernet` | SPI MOSI/MISO/SCK/CS = 23/19/18/5 | W5500 이더넷 DHCP 후 IP 출력 |
| `examples/modbus_rtu_mqtt_rs485` | UART1 RX=16 TX=17 | Modbus RTU 마스터 읽기 → MQTT 발행 (Wi-Fi) |
| `examples/modbus_rtu_mqtt_rs232` | UART2 RX=26 TX=27 | 동일, RS232 경로 |
| `examples/gpio_digital_inputs` | DI 32·33·34·35 | 젖은/건 접점 입력 읽기 |

## 빠른 시작

1. [PlatformIO](https://platformio.org/) 설치.
2. `wifi_secrets.h.example` 을 `arduino/include/wifi_secrets.h` 로 복사하고 SSID·MQTT 브로커 등 수정 (MQTT 예제만 해당).
3. 예제 폴더에서:

```bash
cd examples/i2c_oled_096
pio run -t upload
```

## 주의

- **UART0** 는 USB(CH340)와 연결됨. RS485/232 예제는 **Serial1 / Serial2** 사용.
- Modbus 슬레이브 ID·레지스터 주소는 현장 장비에 맞게 `main.cpp` 상단 상수 수정.
- W5500 모듈에 **INT** 핀이 보드에 안 나온 경우 폴링 동작에 의존 (라이브러리 기본 동작).
