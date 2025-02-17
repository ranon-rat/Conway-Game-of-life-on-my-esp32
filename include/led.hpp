#include <Arduino.h>
void setupLed()
{
    pinMode(LED_BUILTIN, OUTPUT);
}
void turnOnLed()
{
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
   
}
