#include <ThingerESP32.h>

#define USERNAME "saparhadi"
#define DEVICE_ID "ESP32"
#define DEVICE_CREDENTIAL "nktkmpV1E@mt"

#define SSID "kondrong"
#define SSID_PASSWORD "kondrong123"

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

void setup() {
  Serial.begin(115200);
  Serial.println("Baca InternalTemp");

  thing.add_wifi(SSID, SSID_PASSWORD);

  thing["InternalTemp"] >> [](pson& out){
    out = ((temprature_sens_read() - 32) / 1.8);
  };
}

void loop() {
  thing.handle();
  Serial.print("Temperature: ");
  
  // Convert raw temperature in F to Celsius degrees
  Serial.print((temprature_sens_read() - 32) / 1.8);
  Serial.println(" C");
  delay(1000);
}
