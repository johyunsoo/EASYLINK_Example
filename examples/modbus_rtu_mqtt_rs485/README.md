# RS485 — Modbus RTU → MQTT

- **UART**: `Serial1`, `RX=GPIO16`, `TX=GPIO17` (MAX13487 자동 방향)
- **Wi-Fi/MQTT**: `src/main.cpp` 상단 `****` 를 SSID·비밀번호·브로커 주소 등으로 바꿈 (`wifi_secrets.h` 미사용)
- **Modbus**: 기본 9600 8N1, FC03 Holding, 슬레이브 ID·시작 주소·개수는 `main.cpp` 상단

토픽: `easylink/modbus/rtu/rs485/holding`

슬레이브 없으면 `err` 필드로 실패 코드만 올라감 — 정상.
