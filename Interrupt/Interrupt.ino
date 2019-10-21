uint8_t GPIO_Pin = 5;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(GPIO_Pin), IntCallback, RISING);
  pinMode(2, OUTPUT);
}

void loop()
  {}

void IntCallback()
{
  Serial.print("Stamp(ms):");
  Serial.println(millis());
}
