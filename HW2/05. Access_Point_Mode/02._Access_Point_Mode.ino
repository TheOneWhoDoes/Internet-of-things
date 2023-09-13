#include<ESP8266WiFi.h>

IPAddress local_IP(192,168,1,1);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,255,0);

const char* ssid = "Khoshbin-AP";
const char* pass = "wxyz1279";

void setup() {
  Serial.begin(9600);
  Serial.println();

  WiFi.disconnect();

  Serial.println("Starting Soft-AP...");
  delay(10);
  boolean state = WiFi.softAP(ssid, pass);
  if(state){
    Serial.println("Soft-AP is ready now!");
    Serial.print("Soft-AP Automatic IP Address is: ");
    Serial.println(WiFi.softAPIP());
    delay(1000);

    Serial.println();
    Serial.println("changing IP to static value...");
    // 1. first turn Soft-AP off
    Serial.println("Trying to turn off Soft-AP mode");
    while(!WiFi.softAPdisconnect(true)){
      Serial.print(".");
      delay(100);
    }
    Serial.println("Access point turned off.");
    // 2. start Soft-AP mode
    Serial.println("Starting Soft-AP with static IP...");
    delay(100);
    boolean isIPChanged = WiFi.softAPConfig(local_IP, gateway, subnet);
    if(isIPChanged){
      boolean isOn = WiFi.softAP(ssid, pass);
      if(isOn){
        Serial.println("Soft-AP is ready now!");
        Serial.print("new IP(static) is: ");
        Serial.println(WiFi.softAPIP());
      }else{
        Serial.println("Soft-AP starting failed");
      }
      
    }else{
      Serial.println("Setting static IP failed!");
    }
  
  }else{
    Serial.println("Soft-AP starting failed");
  }

}

void loop() { }
