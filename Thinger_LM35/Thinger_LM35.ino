#include <ThingerESP32.h>

#define USERNAME "saparhadi"
#define DEVICE_ID "ESP32"
#define DEVICE_CREDENTIAL "nktkmpV1E@mt"

#define SSID "Saparhadi"
#define SSID_PASSWORD "ahahahaha"

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

const int analogIn = 34;

int RawValue = 0;
double Voltage = 0;
double tempC = 0;
double tempF = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Baca LM35");

  thing.add_wifi(SSID, SSID_PASSWORD);

  thing["LM35 RawValue"] >> [](pson& out) {
    out ["RawValue"] = analogRead(analogIn);
  };

  thing["LM35 Voltage"] >> [](pson& out) {
    out ["Voltage"] = (analogRead(analogIn) / 2048.0) * 3300;
    out ["Voltage Raw"] = (analogRead(analogIn) / 2048.0) * 5000;
  };

  thing["LM35 Temp"] >> [](pson& out) {
    out ["tempC"] = ((analogRead(analogIn) / 2048.0) * 3300) * 0.1;
    out ["tempF"] = ((((analogRead(analogIn) / 2048.0) * 3300) * 0.1) * 1.8) + 32;
  };
}

void loop() {
  thing.handle();
}
