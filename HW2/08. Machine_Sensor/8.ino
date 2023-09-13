#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const int trigPin = D4; 
const int echoPin = D3;  
long duration;
int distance;
 
const char* ssid = "Android279";
const char* password = "wxyz1276";
 
const int ledPin = D2;
const int buzzer = D5;

ESP8266WebServer server(80);


float getDistance(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); 
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2; 
  return distance;    
}

void handleRoot() {
  String index = "\
    <html>\
      <head>\
        <script>\
          setInterval(async ()=> {\
            var response = await fetch('/distance');\
            var dist = await response.text();\
            document.getElementById('dis').value = dist;\
            document.getElementById('disVal').innerText = dist;}\
            ,200);\
        </script> \
      </head>\
      <body>\
        <input id='dis' type='range' min='2' max='200' value='this.value' />\
        <p id='disVal'></p>\
      </body>\
    </html>";
  server.send(200, "text/html", index);
}

void handleDistance(){
  float distance = getDistance();
  server.send(200, "text/plain", String(distance));
  if(distance < 5){
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzer, HIGH);
  }else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzer, LOW);
  }  
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  delay(10);
  
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
 
  server.on("/", handleRoot);
  server.on("/distance", handleDistance);
  server.begin();
  Serial.println("HTTP server started");
  
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}


void loop() {
  server.handleClient();
}
 
