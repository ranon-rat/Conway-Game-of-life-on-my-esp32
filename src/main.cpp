#include <Arduino.h>
#include <WiFi.h>
#include "wifiConfig.h"
#include "server.hpp"
Conway conway(returnMapChar());
int fps = 1000 / 1;
long lastTime = 0;

void setup()
{

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
  if (deltaTime >= fps)
  {
    lastTime = currentTime;
    conway.update_map(ws);
    char *map = conway.map_to_char();
    char mapcp[WIDTH * HEIGHT + 1];
    memcpy(mapcp, map, WIDTH * HEIGHT + 1);
    if (ws.count() > 0)
      ws.textAll(map);
    delete[] map;
  }
}
