#include <Arduino.h>
#include <SimpleDHT.h>
#include "adc.h"

SimpleDHT11 dht11(4);
byte tempCelsius = 10;
int targetTempCelsius = 10;
byte humidity;
char adcText[5];
int err = SimpleDHTErrSuccess;


void updateAdc(void)
{
  if ((err = dht11.read(&tempCelsius, &humidity, NULL)) == SimpleDHTErrSuccess){
    sprintf(adcText, "%d", tempCelsius); 
  }
}

const char* getAdcText(void)
{
  return adcText;
}

int getTempCelsius(void)
{
  return tempCelsius;
}

int getTargetTempCelsius(void)
{
  return targetTempCelsius;
}


void setTargetTempCelsius(int degreeCelsius)
{
  targetTempCelsius = degreeCelsius;
}
