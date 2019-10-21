float vref = 5.0;
float resolution = vref/1024;

void setup() {
  Serial.begin(9600);

}

void loop() {
  float temperature = analogRead(34);
  temperature = (temperature*resolution);
  temperature = temperature*100;
  Serial.println(temperature);
  delay(100);

}
