#include <TinyGPS++.h>
static const int RXPin = 16, TXPin = 17;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;

void setup()
{
  Serial.begin(9600);
  Serial2.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);
  delay(1000);
  Serial.println("Test!");
}

void loop() {
  while (Serial2.available()) {
    byte gpsData = Serial2.read();
    gps.encode(Serial2.read());
    if (gps.location.isUpdated()) {
      Serial.print("Latitude= ");
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= ");
      Serial.println(gps.location.lng(), 6);
    } else
    Serial.write(gpsData);
    
  }
}
