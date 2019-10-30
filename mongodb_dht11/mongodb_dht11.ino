/*************************
   Green Robot Machinery
   Linkit Code that senses temperature and publishes to MQTT broker
 * **********************/

#include <SPI.h>        //includes the Serial Peripheral Interface library
#include <PubSubClient.h>    // A client library that provides support for MQTT
#include <dht11.h>      // library for DHT11 Temperature and Humidity sensor

#include <HttpClient.h>   // library for posting HTTP requests

// MediaTek LinkIt libraries for WiFi connectivity
#include <LTask.h>
#include <LWiFi.h>
#include <LWiFiClient.h>

#define WIFI_AP "Saparhadi"    // write your WiFi name in between double quotes
#define WIFI_PASSWORD "ahahahaha"  // write the WiFi password in between double quotes
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.


LWiFiClient wifiClient;
byte localserver[] = {192, 168, 43, 142 };  //this is ip address of the machine where the mqtt broker is running



String clientName = String("d:quickstart:arduino:");  //client name can be of your choice
String topicName = String("demo/device/");   //similarly topic name can be of your choice but make sure the same topic name is used in the node.js program
dht11 DHT11; // activate the Temp and Humidity sensor
float tempF = 0.0;  // initialise a variable for Temperature in Fahrenheit
float tempC = 0.0;  // initialise a variable for Temperature in Celsius
float humid = 0.0; // initialise a variable for Humidity

PubSubClient client(localserver, 1883, 0, wifiClient); //communicating the LinkIt One with the mosquitto broker (port no. 1883) running on the localserver, LinkIt One communicates to the broker via WiFi hence the WiFiClient

void setup()
{
  Serial.begin(115200);
  DHT11.attach(34);  //Temp and Humidity sensor is attached to the digital pin 3

  // activating the WiFi module of the LinkIt One Board
  LTask.begin();
  LWiFi.begin();
  Serial.println("Temperature sensor on...");
  delay(3000);
  while (!Serial) delay(1000);
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
  {
    delay(1000);
  }
  Serial.println("calling connection");
}


void loop()
{

  char clientStr[34];
  clientName.toCharArray(clientStr, 34);
  char topicStr[26];
  topicName.toCharArray(topicStr, 26);

  getData();

  //checking for client connections
  if (!client.connected()) {
    Serial.print("Trying to connect to: ");
    Serial.println(clientStr);
    client.connect(clientStr);
  }
  if (client.connected() ) {
    String json = buildJson();
    char jsonStr[200];
    json.toCharArray(jsonStr, 200);
    boolean pubresult = client.publish(topicStr, jsonStr);
    Serial.print("attempt to send ");
    Serial.println(jsonStr);
    Serial.print("to ");
    Serial.println(topicStr);
    if (pubresult)
      Serial.println("successfully sent");
    else
      Serial.println("unsuccessfully sent");
  }
  delay(5000);
}



// sending data(Temperature in Celsius and Fahrenheit and also the humidity level) to mqtt server running on port 1883 using ‘json’ format

String buildJson() {
  String data = "{";
  data += "\n";
  data += "\"d\": {";
  data += "\n";
  data += "\"myName\": \"Arduino DHT11\",";
  data += "\n";
  data += "\"temperature (F)\": ";
  data += (int)tempF;
  data += ",";
  data += "\n";
  data += "\"temperature (C)\": ";
  data += (int)tempC;
  data += ",";
  data += "\n";
  data += "\"humidity\": ";
  data += (int)humid;
  data += "\n";
  data += "}";
  data += "\n";
  data += "}";
  return data;

}


//function that reads the DHT 11 Sensor data
void getData() {

  static float tF = 86.0;
  static float tC = 30.0;
  static float tH = 1.0;
  tempF = tF++;
  tempC = tC++;
  humid = tH++;

  int chk = DHT11.read();
  switch (chk)
  {
    case 0:
      Serial.println("Read OK");
      humidity = (float)DHT11.humidity;
      tempF = DHT11.fahrenheit();
      tempC = DHT11.temperature;
      break;
    case -1:
      Serial.println("Checksum error");
      break;
    case -2:
      Serial.println("Time out error");
      break;
    default: Serial.println("Unknown error");
      break;
  }

}
