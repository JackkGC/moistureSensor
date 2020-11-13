#include <Arduino.h>
#include <FS.h>
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"

AsyncWebServer server(80);

const char *ssid = "abc";
const char *password = "xyz";

int moistureSensor = 36;

void notFound(AsyncWebServerRequest *request)
{
  request->send(404);
}

void setupWiFi()
{
  WiFi.disconnect(true);
  delay(1000);
  WiFi.softAPdisconnect(true);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.printf("WiFi Failed!\n");
    return;
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(moistureSensor, INPUT);

  SPIFFS.begin(true);

  setupWiFi();

  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(analogRead(moistureSensor)));
  });

  server.serveStatic("/", SPIFFS, "/public/").setDefaultFile("index.html");
  server.onNotFound(notFound);
  server.begin();
  Serial.println(WiFi.localIP());
}

void loop()
{
  // float moisVal = ((analogRead(moistureSensor) * 100L)/1024);
  // float moisVal = analogRead(moistureSensor);
  // Serial.println(moisVal);
  // delay(1000);
}