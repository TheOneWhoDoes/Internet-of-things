#include <ESP8266WiFi.h>
 
const char* ssid = "Khoshbin";
const char* password = "wxyz1276";
 
int ledPin = D2;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  analogWriteRange(100);
 
  // Connect to WiFi network
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
  
 
  // Handle request
  String cmd = "";
  float light;
  if (request.indexOf("/") != -1)  {
    int i2 = request.lastIndexOf(" ");
    int i1 = request.indexOf("/");
    int number = request.substring(i1+1, i2).toInt();
    Serial.println(String(number));
    analogWrite(ledPin, number);
  }
  

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<script> function showVal(value){fetch(\"/\" + value);}</script>");
  
  client.println("<br><br>");
  client.println("<input id=\"price\" type=\"range\" min=\"0\" max=\"100\" value=\"\" oninput=\"showVal(this.value);\"/>");
  client.println("</html>");
 
  delay(10);
  Serial.println("Client disonnected");
  Serial.println(""); 
}
 
