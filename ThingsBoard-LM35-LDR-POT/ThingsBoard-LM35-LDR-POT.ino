#include "ThingsBoard.h"
const int potentioPin = 32;
const int ldrPin = 33;
const int lm35Pin = 34;
int potentioValue;
int ldrValue;
float lm35Value;
float Temp, IntTemp;
String info;

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

void setup()
{
  thingsboard_Init();
}

void loop()
{
  String data;
  const size_t bufferSize = JSON_OBJECT_SIZE(3);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject& root = jsonBuffer.createObject();
  
  potentioValue = analogRead(potentioPin);
  ldrValue = analogRead(ldrPin);
  
  lm35Value = analogRead (lm35Pin);
  Temp = (lm35Value/4095)*500;
  IntTemp = ((temprature_sens_read() - 32) / 1.8);
  //Temp = map(lm35Value, 0, 4095, 2, 150);

  if (Temp <14.9){
    info = "Dingin";
  } else if (Temp >=15 && Temp <21){
      info = "Agak dingin";
  } else if (Temp >=21 && Temp <26){
      info = "Normal";
  } else if (Temp >=26 && Temp <30){
      info = "Agak Hangat";
  } else {
    info = "Panas";
    }
  
  root["pot "] = String(potentioValue);
  root["lux "] = String(ldrValue);
  root["C (LM35) "] = String(Temp);
  root["C (IntTemp) "] = String(IntTemp);
  root["info"] = String(info);
  
  root.printTo(data);
  thingsboard_Publish(data);
  client.loop();
}
