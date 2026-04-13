//**********************************************************************************//
//* HTA JO-H                                                                    *//
//* EASY LINK PRO — RS232 Modbus RTU → MQTT (Wi-Fi)                                 *//
//*--------------------------------------------------------------------------------*//
//* 1.Description : UART2(26/27) 로 RTU 마스터 폴링 후 MQTT 로 JSON 발행               *//
//* 2.Protocol    : Modbus RTU, Wi-Fi, MQTT                                         *//
//* 3.DataBase    : N/A                                                             *//
//* 4.Create      : 2026/04/13_JO-H                                                 *//
//* 5.Release     : 2026/04/13                                                      *//
//* 6.Version     : V1.00_Release                                                   *//
//* 7.History     :                                                                 *//
//* 1) Version 1.00: 최초 작성                                                       *//
//**********************************************************************************//

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ModbusMaster.h>
#include "easylink_pins.h"
#include "wifi_secrets.h"

static const uint8_t MODBUS_SLAVE_ID = 1;
static const uint16_t HOLD_REG_START = 0;
static const uint16_t HOLD_REG_COUNT = 4;
static const uint32_t MODBUS_BAUD = 9600;
static const char *MQTT_TOPIC_BASE = "easylink/modbus/rtu/rs232";

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);
ModbusMaster modbus;

void connectWifi() {
  Serial.printf("[INIT] Wi-Fi 연결 시도: %s\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  uint32_t start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 20000) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(F("[ERROR] Wi-Fi 실패"));
    return;
  }
  Serial.print(F("[LOGIC] Wi-Fi OK IP="));
  Serial.println(WiFi.localIP());
}

void connectMqtt() {
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);
  uint8_t mac[6];
  WiFi.macAddress(mac);
  char cid[24];
  snprintf(cid, sizeof(cid), "el-%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  while (!mqtt.connected()) {
    Serial.println(F("[INIT] MQTT 연결 시도"));
    bool ok;
    if (strlen(MQTT_USER) > 0)
      ok = mqtt.connect(cid, MQTT_USER, MQTT_PASSWORD);
    else
      ok = mqtt.connect(cid);
    if (ok) {
      Serial.println(F("[LOGIC] MQTT 연결됨"));
      return;
    }
    Serial.printf("[ERROR] MQTT 실패 rc=%d, 3초 후 재시도\n", mqtt.state());
    delay(3000);
  }
}

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println(F("[INIT] EASY LINK RS232 Modbus → MQTT"));

  // [INIT] RS232 UART — RX26 TX27
  Serial2.begin(MODBUS_BAUD, SERIAL_8N1, PIN_RS232_RX, PIN_RS232_TX);
  modbus.begin(MODBUS_SLAVE_ID, Serial2);

  connectWifi();
  connectMqtt();
}

void loop() {
  // [MQTT] 발행 형식 (토픽: easylink/modbus/rtu/rs232/holding)
  // 성공: {"bus":"rs232","slave":1,"start":0,"vals":[r0,r1,r2,r3],"ts":밀리초}
  // 실패: {"bus":"rs232","err":Modbus오류코드,"slave":1,"ts":밀리초}
  // err/slave/start/vals 는 HOLD_REG_*·MODBUS_SLAVE_ID 설정에 따라 실제 값으로 채워짐

  if (WiFi.status() != WL_CONNECTED)
    connectWifi();
  if (!mqtt.connected())
    connectMqtt();
  mqtt.loop();

  uint8_t res = modbus.readHoldingRegisters(HOLD_REG_START, HOLD_REG_COUNT);
  char payload[320];
  if (res != ModbusMaster::ku8MBSuccess) {
    snprintf(payload, sizeof(payload),
             "{\"bus\":\"rs232\",\"err\":%u,\"slave\":%u,\"ts\":%lu}",
             (unsigned)res, (unsigned)MODBUS_SLAVE_ID, (unsigned long)millis());
    Serial.printf("[ERROR] Modbus 실패 code=%u\n", (unsigned)res);
  } else {
    snprintf(payload, sizeof(payload),
             "{\"bus\":\"rs232\",\"slave\":%u,\"start\":%u,\"vals\":[%u,%u,%u,%u],\"ts\":%lu}",
             (unsigned)MODBUS_SLAVE_ID, (unsigned)HOLD_REG_START,
             modbus.getResponseBuffer(0), modbus.getResponseBuffer(1),
             modbus.getResponseBuffer(2), modbus.getResponseBuffer(3),
             (unsigned long)millis());
    Serial.printf("[LOGIC] Modbus OK payload=%s\n", payload);
  }

  String topic = String(MQTT_TOPIC_BASE) + "/holding";
  if (mqtt.connected())
    mqtt.publish(topic.c_str(), payload);

  delay(2000);
}
