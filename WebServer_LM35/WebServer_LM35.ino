#include <WiFi.h>
#include <WebServer.h>
/*Put your SSID & Password*/
const char* ssid = "WiFi Gratis";
// Enter SSID here
const char* password = "tapibohong";
//Enter Password here
WebServer server(80);
// LM35 Sensor
uint8_t LM35 = 4;
float Temperature;

void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(LM35, INPUT);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  //connect to your local wi-fi network
  WiFi.begin(ssid, password);
  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
void handle_OnConnect() {
  Temperature = analogRead(LM35);
  // Gets the values of the temperature
  server.send(200, "text/html",
              SendHTML(Temperature));
}
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<title>ESP32 Weather Report</title>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>ESP32 Weather Report</h1>\n";
  ptr += "<p>Temperature: ";
  ptr += (int)Temperaturestat;
  ptr += "°C</p>";
  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
