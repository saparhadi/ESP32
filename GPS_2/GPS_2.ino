#include <TinyGPS++.h>

TinyGPSPlus gps;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 3, 1);
  delay(1000);
  Serial.println("Let's start");
}

void loop() {
  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());
    if (gps.location.isUpdated()) {
      Serial.print("Latitude= ");
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= ");
      Serial.println(gps.location.lng(), 6);
    } else
      Serial.write(byte(Serial1.read()));
  }
}
