int val;
int tempPin = 36;

void setup() {
  Serial.begin(9600);

}

void loop() {
  val = analogRead(tempPin);
  float mv = ( val/4096.0)*5000;
  float cel = mv/10;
  float farh = (cel*9)/5 + 32;
  Serial.print("TEMPERATURE= ");
  Serial.print(cel);
  Serial.print(" *C");
  Serial.println();
  delay(500);

}
