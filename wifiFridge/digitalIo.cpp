#include <Arduino.h>
#include "digitalIo.h"

// Assign output variables to GPIO pins
const int relay = 2;
const int door = 16;

void ioInit(void)
{
  pinMode(relay, OUTPUT);
  pinMode(door, INPUT);
  ioCompressonOff();
}

bool ioDoorOpen(void)
{
  return digitalRead(door) == HIGH;
}

bool ioCoolingOn(void)
{
  return digitalRead(relay) == HIGH;
}

void ioCompressonOn(void)
{
  digitalWrite(relay, HIGH);
}
void ioCompressonOff(void)
{
  digitalWrite(relay, LOW);
}
