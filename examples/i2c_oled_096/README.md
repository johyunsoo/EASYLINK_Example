# I2C 0.96" OLED (SSD1306)

- **핀**: `SDA=GPIO21`, `SCL=GPIO22` (`easylink_pins.h`)
- **라이브러리**: Adafruit SSD1306 + GFX
- **빌드**: `pio run -t upload`

화면이 안 나오면 I2C 주소를 `0x3D` 로 바꿔볼 것.
