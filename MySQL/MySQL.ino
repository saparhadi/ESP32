//include libraries
#include <HTTPClient.h>
#include <WiFi.h>

//Access point credentials
const char* ssid = "kondrong";
const char* pwd = "kondrong123";

float sensor, temp;

int ledPin = 4; //connected to pin 7 in nodemcu 1.0 esp-12e module
int LM35Pin = 34;

WiFiServer server(80);  // open port 80 for server connection
const char* serverName = "http://192.168.100.250/dts/add.php";

void setup()
{
  Serial.begin(115200); //initialise the serial communication
  delay(10);

  //defining the pins, i/p and o/p
  pinMode(ledPin, OUTPUT);
  pinMode(LM35Pin, INPUT);
  digitalWrite(ledPin, LOW);

  //connecting to wifi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to wifi ");
  Serial.println(ssid);

  WiFi.begin(ssid, pwd);

  //attempt to connect to wifi
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("."); //progress with dots until the wifi is connected
  }
  Serial.println("");

  //while connected print this
  Serial.println("Wifi connected");

  //starting the server
  server.begin();
  Serial.println("Server started.");

  //get the ip address and print it
  Serial.print("This is your ip address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  //wait for the data to be sent from client
  Serial.println("New client connection");
  while (!client.available())
  {
    delay(1);
  }

  //Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  int value = LOW; // set the thermometer off initially
  sensor = analogRead(LM35Pin);
  temp = (sensor/4095.0)*330.0; //converting degree to celcius

  //check the index of the browser and act accordingly
  if (request.indexOf("/Thermo=ON") != -1)
  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
    sensor = analogRead(LM35Pin);
    temp = (sensor/4095.0)*330.0; //converting degree to celcius

    HTTPClient http;
    http.begin(serverName);

    //save the data to mysql, access the php file to write
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String url = "temp=" + String(temp) + "";
    Serial.print(serverName);
    Serial.print("?");
    Serial.println(url);

    //GET method
    int httpCode = http.GET();
    if (httpCode > 0)
    {
      Serial.printf("[HTTP] GET...code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK)
      {
        String payload = http.getString();
        Serial.println(payload);
      }
    }
    else
    {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    delay(3000);
  }

  if (request.indexOf("/Thermo=OFF") != -1)
  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }

  //Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");

  if (request.indexOf("/AlwaysOn") != -1)
  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
    sensor = analogRead(LM35Pin);
    temp = (sensor/4095.0)*330.0; //converting degree to celcius
    client.println("Refresh: 5");
  }

  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<body style=background-color:skyblue> </body>");
  client.println("<style> h1 {text-align: center}</style>");
  client.println("<style> h3 {text-align: center}</style>");
  client.println("<style> b {text-align: center}</style>");
  client.println("<style> p {text-align: center}</style>");
  client.println("<head><style>div.relative{position:relative; left:200px; height:20px; width:350px; border:2px solid #73AD21;}</style></head>");
  client.println();

  client.println("<div class=relative>  <b> UNIVERSITY OF GADJAH MADA  </b> </div>");
  client.println("<div class=relative> Ashish Shrestha  </div>");
  client.println("<div class = relative>  Rituraj Nepal </div>");

  //client.println("<br>");
  client.println("<br><br><h1>IOT Final Project: THERMOMETER</h1><br><br>");
  //client.println("<h3>Probable LM35 analog reading: <h3>");
  //client.print(sensor); //analog reading of the sensor
  //client.print("<br>");

  client.print("<h3>Thermometer's current status: </h3>");

  if (request.indexOf("/AlwaysOn") != -1)
  {
    client.print("<h3>Always On<h3>");
    client.print("(Temperature updated every 5 seconds.)");
    client.println("<h3>Current Temperature: <h3>");
    client.print(temp);
    client.print("<b> deg C.</b>");

    //save the data to mysql, with http client
    HTTPClient http;
    http.begin(serverName);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String url = "temp=" + String(temp) + ""; //access the php file to write data
    Serial.println(url);

    //using GET method to write to sql
    int httpCode = http.GET();
    if (httpCode > 0)
    {
      Serial.printf("[HTTP] GET...code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK)
      {
        String payload = http.getString();
        Serial.println(payload);
      }
    }
    else
    {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    //delay(3000);
  }

  else if (value == HIGH)
  {
    client.print("<h3>On Once<h3>");
    //client.println("<br>");
    client.println("<h3>Current Temperature: <h3>");
    client.print(temp);
    client.print("<b> deg C.</b>");
  }
  else if (value == LOW)
  {
    client.print("<h3>Off<h3>");
    // client.println("<br>");
    client.println("<h3>Last measured temperature: <h3>"); //print the last value of temp
    client.print(temp);
    client.print("<b> deg C.</b>");
  }

  client.println("<br><br>");
  //create buttons
  client.println("<a href=\"/Thermo=ON\"\"><button>Turn On Once </button></a>");
  client.println("<a href=\"/AlwaysOn\"\"><button>Keep It On </button></a>");
  client.println("<a href=\"/Thermo=OFF\"\"><button>Turn Off </button></a><br />");

  client.println("<h3>Check the Temperature records by following the below link: <h3>");
  client.println("<p>http://localhost/dts/show.php</p>");

  // if there are incoming bytes available from the server, read them and print them:
  if (client.available())
  {
    char c = client.read();
    client.print(c);
  }

  client.println("</html>");

  client.println();
  delay(1);
  Serial.println("Client disconnected!");
  Serial.println("");
}
