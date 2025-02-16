#include <Arduino.h>
#include <wifiConfig.h>
#include "conway.hpp"
Conway conway(returnMapChar());
int fps=1000/1;
long lastTime=0;
void setup()
{
  Serial.begin(115200);
}

void loop()
{
  long currentTime = millis();
  long deltaTime = currentTime - lastTime;
  if (deltaTime >= fps)
  {
    lastTime = currentTime;
    char* char_map = conway.map_to_char();
    Serial.println("-------------------");
    for (int y = 0; y < HEIGHT; y++){
      for (int x = 0; x < WIDTH; x++){
        Serial.print(char_map[y*WIDTH+x]);
      }
      Serial.println();
    }
    Serial.println();
    conway.update_map();

  }
}

