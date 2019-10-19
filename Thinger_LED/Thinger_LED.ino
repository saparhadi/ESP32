#include <ThingerESP32.h>

#define USERNAME "saparhadi"
#define DEVICE_ID "ESP32"
#define DEVICE_CREDENTIAL "nktkmpV1E@mt"

//Your Wifi setting
#define SSID "Saparhadi"
#define SSID_PASSWORD "ahahahaha"

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(LED_BUILTIN);

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());

  // more details at http://docs.thinger.io/arduino/
  
}

void loop() {
  thing.handle();
  
}
