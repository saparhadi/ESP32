#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid     = "kondrong";
const char* password = "kondrong123";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://192.168.100.250/dts/add-post.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page.
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key
String apiKeyValue = "tPmAT5Ab3j7F9";

float sensor, temp;

int ledPin = 4; //connected to pin 7 in nodemcu 1.0 esp-12e module
int LM35Pin = 34;

void setup() {
  Serial.begin(115200);

  //defining the pins, i/p and o/p
  pinMode(ledPin, OUTPUT);
  pinMode(LM35Pin, INPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(serverName);

    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    sensor = analogRead(LM35Pin);
    temp = (sensor/4095)*330;
  
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&temp=" + String(temp) + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 50 seconds
  delay(5000);
}
