# RS232 — Modbus RTU → MQTT

- **UART**: `Serial2`, `RX=GPIO26`, `TX=GPIO27`
- **설정**: `wifi_secrets.h` 필수. Modbus 파라미터는 `main.cpp` 상단

토픽: `easylink/modbus/rtu/rs232/holding`

RS485 예제와 동시에 쓰려면 한쪽 UART 만 쓰거나, 한 보드에 한 예제만 플래시할 것.
