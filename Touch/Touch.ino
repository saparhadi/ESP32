int TOUCH = T3;
//Harus ditambahin "T" soalnya pake sensor Touch, pake nama pin juga bisa
int LED = 23;
int TRESHOLD = 50;

void setup() {
  Serial.begin(9600);
  Serial.println("Eh kesentuh :P");    
}

void loop() {
  Serial.println(touchRead(touch);
  delay(500);
}
