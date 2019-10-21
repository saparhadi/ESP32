#define LED_PIN 2
#define LDR_PIN 34
#define TRESHOLD 500

void setup() {
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (analogRead(LDR_PIN < TRESHOLD)(
    digitalWrite(LED_PIN, HIGH);
    ) else (
      digitalWrite(LED_PIN, LOW);
      )
}
