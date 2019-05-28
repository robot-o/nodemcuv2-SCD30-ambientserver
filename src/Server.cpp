#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <SparkFun_SCD30_Arduino_Library.h>
#include <ArduinoJson.h>

int altitude = 519; // altitude in m
const char* deviceName = "co2node-1";
const char* ssid = "YOURSSID";
const char* password = "YOURPASSWORD";

ESP8266WebServer server(80);

SCD30 sensor;

const int led = 13;

void handleNotFound();
void handleRoot();

void handleNotFound(){
  digitalWrite(led, 1);
  server.send(404, "text/plain", "nope pope!");
  digitalWrite(led, 0);
}

void handleRoot() {
  digitalWrite(led, 1);
  digitalWrite(led, 0);
  String response = "";
  if (sensor.dataAvailable())
  {
    const int capacity = JSON_OBJECT_SIZE(4);
    StaticJsonDocument<capacity> json;
    json["node"] = deviceName;
    json["co2"] = sensor.getCO2();
    json["temperature"] = sensor.getTemperature();
    json["humidity"] = sensor.getHumidity();
    serializeJsonPretty(json, response);
    server.send(200, "application/json", response);
  }
  else
  {
    response += "data unavailable!";
    response += "\n";
    server.send(500, "text/plain", response);
  }
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print(" ");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin(deviceName)) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  Wire.begin();
  sensor.begin();
  sensor.setAltitudeCompensation(altitude);

  Serial.print("waiting for sensor to be ready..");
  while (!sensor.dataAvailable())
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("ready!");
}

void loop(void){
  server.handleClient();
}
