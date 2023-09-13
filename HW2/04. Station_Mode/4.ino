#include<ESP8266WiFi.h>

const char* ssid = "Khoshbin";
const char* pass = "wxyz1276";

void setup() {
  Serial.begin(9600);
  Serial.println();

  Serial.println("Starting station mode...");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Scanning networks...");
  int n = WiFi.scanNetworks();
  Serial.println("Available networks are:");
  for(int i = 0; i < n; i++){
    Serial.println(WiFi.SSID(i));
  }

  Serial.println("Connecting to \"Khoshbin\" SSID");
  WiFi.begin(ssid, pass);

   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() { }
