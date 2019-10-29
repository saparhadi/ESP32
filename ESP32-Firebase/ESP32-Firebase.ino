#include <WiFi.h>                                                // esp32 library
#include <IOXhop_FirebaseESP32.h>

#define FIREBASE_HOST "saparhadi-191118.firebaseio.com"                         // the project name address from firebase id
#define FIREBASE_AUTH "fjuyfKHCJYJEVvpAhTon5J3RshAF0xsq09UNuAIK"                    // the secret key generated from firebase
#define WIFI_SSID "Saparhadi"                                          // input your home or public wifi name
#define WIFI_PASSWORD "ahahahaha"                                    //password of wifi ssid

int fireStatus = 0;                                                     // led status received from firebase
int led = 4;

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(led, OUTPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                                      //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
  Firebase.setInt("/led", 0);                                          //send initial string of led status
}

void loop() {
  fireStatus = Firebase.getInt("/led");                     // get led status input from firebase
  if (fireStatus == 255) {                         // compare the input of led status received from firebase
    Serial.println("Led Turned ON");
    digitalWrite(led, HIGH);                                                         // make output led ON
  }
  else if (fireStatus == 0) {              // compare the input of led status received from firebase
    Serial.println("Led Turned OFF");
    digitalWrite(led, LOW);                                                         // make output led OFF
  }
  else {
    Serial.println("Wrong Credential! Please send ON/OFF");
  }
}
