const int analogIn = 34;

float RawValue;
float Voltage = 0;
float tempC = 0;
float tempF = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Baca LM35");
}

void loop() {

  RawValue = analogRead(analogIn);
  Voltage = (RawValue/4095)*3300; // with 3.3V input
  tempC = Voltage*0.1;
  tempF = (tempC * 1.8) + 32; // convert to F

  Serial.print("Raw Value = " ); // shows pre-scaled value
  Serial.print(RawValue);

  Serial.print("\t milli volts = "); // shows the voltage measured
  Serial.print(Voltage, 0); //

  Serial.print("\t Temperature in C = ");
  Serial.print(tempC, 1);

  Serial.print("\t Temperature in F = ");
  Serial.println(tempF, 1);

  delay(500);
}
