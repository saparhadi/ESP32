int TOUCH = 15;
//Harus ditambahin "T" soalnya pake sensor Touch, pake nama pin juga bisa
int LED = 2;
int TRESHOLD = 50;

void setup() {
  Serial.begin(9600);
  Serial.println("Colek");
  pinMode(LED, OUTPUT);
}

void loop() {
  if (touchRead(TOUCH) < TRESHOLD){
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  Serial.println(touchRead(TOUCH) );
  delay(500);
}
