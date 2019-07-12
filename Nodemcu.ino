//This code goes to Nodemcu
#include <ESP8266WiFi.h>
#include <Wire.h>
const char* ssid = "GREENLAN";
const char* password = "green0912";
 
int ledPin = 14; // GPIO13---D7 of NodeMCU
WiFiServer server(80);
 
void setup() {
  Wire.begin(D1, D2);
  Serial.begin(9600);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
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
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  
 

 
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
  if (request.indexOf("/komunikatON") != -1)  {
    Wire.beginTransmission(8); /* begin with device address 8 */
    Wire.write(65);  /* sends hello string */
    Wire.endTransmission();    /* stop transmitting */
 }
 if (request.indexOf("/komunikatOFF") != -1)  {
    Wire.beginTransmission(8); /* begin with device address 8 */
    Wire.write(60);  /* sends hello string */
    Wire.endTransmission();    /* stop transmitting */
 }
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led is now: ");
 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Off </button></a><br />"); 
  
  client.println("<a href=\"/komunikatON\"\"><button>Zapal diode </button></a><br />");
  client.println("<a href=\"/komunikatOFF\"\"><button>Zgas Diode </button></a><br />");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
  }
//  Wire.beginTransmission(8); /* begin with device address 8 */
// Wire.write("Hello Arduino");  /* sends hello string */
// Wire.endTransmission();    /* stop transmitting */
//
// Wire.requestFrom(8, 13); /* request & read data of size 13 from slave */
// while(Wire.available()){
//    char c = Wire.read();
//  Serial.print(c);
// }
// Serial.println();
// delay(1000);
//}
