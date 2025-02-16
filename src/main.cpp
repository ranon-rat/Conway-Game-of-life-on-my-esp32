#include <Arduino.h>
#include <wifiConfig.h>
#include "conway.hpp"
// put function declarations here:
int myFunction(int, int);
Conway conway(returnMapChar());
int fps=1000;
long lastTime=0;
int f=0;

// now i should work on the way i render stuff 
void setup()
{
  
  Serial.begin(115200);
  // put your setup code here, to run once:
  // so ahora solo es tiempo de que me ponga a hacer el juego de conway
  Serial.println("");
}

void loop()
{
  // how i can get the current time?
  long currentTime = millis();
  long deltaTime = currentTime - lastTime;
  if(f<10){
    f++;
    Serial.println("");
    return;
  }
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
  // put your main code here, to run repeatedly:
}

