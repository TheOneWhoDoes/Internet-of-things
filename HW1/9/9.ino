#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <MFRC522.h>

const char *ssid     = "Khoshbin";
const char *password = "wxyz1237";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");


#define RST_PIN         D3          // Configurable, see typical pin layout above
#define SS_PIN          D4         // Configurable, see typical pin layout above

#define LED_PIN         D2
#define LED_PIN_SERVO   D1
#define BUZZER_PIN      D8

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance


void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.println();

  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_SERVO, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // Iran = GMT + 3:30 + [1:00](when daylight we have saving in summer)
  timeClient.setTimeOffset(3.50 * 60 * 60);

  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}


void array_to_string(byte array[], unsigned int len, char buffer[]){
   for (unsigned int i = 0; i < len; i++)
   {
      byte nib1 = (array[i] >> 4) & 0x0F;
      byte nib2 = (array[i] >> 0) & 0x0F;
      buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
      buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
   }
   buffer[len*2] = '\0';
}


void loop() {
  timeClient.update();

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));  

  char uid[32] = "";
  array_to_string(mfrc522.uid.uidByte, 4, uid); //Insert (byte array, length, char array for output)
  Serial.println(uid);
  
  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Time: ");
  Serial.println(formattedTime);  

  int currentHour = timeClient.getHours();

  if(currentHour >= 18 && currentHour < 20 && strcmp(uid, "F9FF44BA") ){
    digitalWrite(LED_PIN_SERVO, HIGH);
    digitalWrite(LED_PIN, HIGH);
    delay(3000);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN_SERVO, LOW);
  }else{
    tone(BUZZER_PIN, 1000);
    delay(3000);
    noTone(BUZZER_PIN);
  }

  delay(1000);
}
