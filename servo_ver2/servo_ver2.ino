#include <analogWrite.h>
uint8_t ServoMotorpin = 4;
uint16_t dutycycle;

void setup(){
  analogWrite(ServoMotorpin, 512);
  analogWriteFrequency(50); /* Set PWM frequency to 50Hz */
  Serial.begin(115200);
  Serial.println("ESP32 Analog IN Test");
}

void loop(){
  dutycycle= analogRead(5); /* Read potentiometer to control servo motor */
  Serial.println(dutycycle);
  if(dutycycle> 1023){
    dutycycle = 1023;
   }
  dutycycle = 25+((85*dutycycle/1023)); /* make it in range 20 to 110 */ 
  analogWrite(ServoMotorpin, dutycycle); /* Write duty cycle to pin */
  delay(100);
}
