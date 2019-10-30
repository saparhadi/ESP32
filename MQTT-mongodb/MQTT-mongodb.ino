#include <WiFi.h>
#include <PubSubClient.h>

#define led 2

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

const char* ssid = "Saparhadi";
const char* password = "ahahahaha";
const char* mqtt_server = "192.168.43.142";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;
float temperature = 0;
int hall = 0;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(led, OUTPUT);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
      digitalWrite(led, HIGH);
    } else if (messageTemp == "off") {
      Serial.println("off");
      digitalWrite(led, LOW);
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32-Hadi")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    temperature = (temprature_sens_read() - 32) / 1.8;
    char tempString[8];
    dtostrf(temperature, 1, 2, tempString);
    Serial.print("Temperature: ");
    Serial.println(tempString);
    String payloadStr = buildJson();
    char payload[payloadStr.length() + 1];
    payloadStr.toCharArray(payload, payloadStr.length() + 1);
    Serial.println("Sending payload: ");
    Serial.println(payload);
    client.publish("esp32/temperature", payload);
    hall = hallRead();
    char hallString[8];
    dtostrf(hall, 1, 2, hallString);
    Serial.print("Hall effect: ");
    Serial.println(hallString);
    client.publish("esp32/hall", hallString);
  }
}

String buildJson() {
  String data = "{";
  data += "\n";
  data += "\"timestamp\": \"";
  data += lastMsg;
  data += "\",";
  data += "\n";
  data += "\"Temperature\": ";
  data += (int)temperature;
  data += "\n";
  data += "}";
  return data;
}
