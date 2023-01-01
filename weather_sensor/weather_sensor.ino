#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Arduino_LSM6DSOX.h>
#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;
int status = WL_IDLE_STATUS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = BROKER_URL;
int port = 1883;
const char topic[] = "test";

Adafruit_BME280 bme;

unsigned long delayTime = 3000;

void setup() {
  Serial.begin(9600);
  delay(4000);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  if (!bme.begin(0x76)){  
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      while (1);
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid); 

    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  printWifiStatus();

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void loop() { 
  mqttClient.poll();
  mqttClient.beginMessage(topic);
  mqttClient.print("{\"location\":\"office\",\"temp\":");
  mqttClient.print(bme.readTemperature());
  mqttClient.print(",\"humidity\":");
  mqttClient.print(bme.readHumidity());
  mqttClient.print("}");
  mqttClient.endMessage();

  delay(delayTime);
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}