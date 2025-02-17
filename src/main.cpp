#include <Arduino.h>
#include <WiFi.h>
#include "wifiConfig.h"
#include "server.hpp"
static Conway conway(returnMapChar());
#define FPS 1000 *5
long lastTime = 0;

void setup()
{
  setupLed();
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);
  Serial.printf("Connecting to: %s\n", SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.printf("local IP: %s\n", WiFi.localIP().toString().c_str());
  StartServer(&conway);
}

void loop()
{
  ws.cleanupClients();

  long currentTime = millis();
  long deltaTime = currentTime - lastTime;
  if (deltaTime >= FPS)
  {
    lastTime = currentTime;
    conway.update_map(ws);
    if (ws.count() > 0)
    {
      ws.textAll(conway.map_to_string());
    }
  }
}
