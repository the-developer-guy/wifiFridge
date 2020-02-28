#include <ESP8266WiFi.h>
#include "server.h"
#include "adc.h"
#include "digitalIo.h"

bool wifiInit(const char* ssid, const char* password);

const char* ssid     = "YOUR_SSID";
const char* password = "WIFI_PASSWORD";
unsigned long adcTask = 0;
int tempHysteresis = 1;

void setup() {
  Serial.begin(115200);
  ioInit();  
  setTargetTempCelsius(10);
  updateAdc();
  Serial.println("Fridge starting, target temperature: " 
    + String(getTargetTempCelsius(), 1)
    + "C, current temperature: "
    + String(getTempCelsius(), 1));
  wifiInit(ssid, password);
  startServer();
}

void loop(){
  if(adcTask < millis())
  {
    adcTask += 5000;
    updateAdc();
    if(getTempCelsius() > (getTargetTempCelsius() + tempHysteresis))
    {
      ioCompressonOn();
    }
    else if(getTempCelsius() < (getTargetTempCelsius() - tempHysteresis))
    {
      ioCompressonOff();
    }
  }
  checkClient();
}

bool wifiInit(const char* ssid, const char* password)
{
  int connectTimeoutSecond = 60;
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && (connectTimeoutSecond > 0)) {
    delay(1000);    
    connectTimeoutSecond--;
    Serial.print(".");
  }
  if(WiFi.status() == WL_CONNECTED)
  {
    Serial.println("\nWiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    return true;
  }
  else
  {
    Serial.println("\nWifi connection failed!");
    return false;
  }
}
