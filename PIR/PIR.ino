int LED = 5;
int PIR_Input = 15;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_Input, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, digitalRead(PIR_Input));
  Serial.println(digitalRead(PIR_Input));
  delay(10);

}
