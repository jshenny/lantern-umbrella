/*
 * 
 * All the resources for this project: https://randomnerdtutorials.com/
 * Modified by Rui Santos
 * 
 * Created by FILIPEFLOP
 * 
 */
 
#include <SPI.h>
#include <MFRC522.h>
#include <FastLED.h>

#define NUM_LEDS 60
#define DATA_PIN 4
CRGB leds[NUM_LEDS];
 
#define SS_PIN 10
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
  for (int x = 0; x < 60; x++){
    leds[x] = CRGB:: Black;
  }
  FastLED.show(); 

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "D0 ED 92 10") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    for (int x = 7; x < 41; x++){
      leds[x] = CRGB:: Red;
    }
    FastLED.show(); 
    delay(3000);
  }
  else if (content.substring(1) == "0C 40 75 32") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    for (int x = 7; x < 41; x++){
      leds[x] = CRGB:: CornflowerBlue;
    }
    FastLED.show(); 
    delay(3000);
  }
  else if (content.substring(1) == "BC 96 74 33") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    for (int x = 7; x < 41; x++){
      leds[x] = CRGB:: DarkViolet;
    }
    FastLED.show(); 
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
    for (int x = 7; x < 41; x++){
      leds[x] = CRGB:: Black;
    }
    FastLED.show(); 
    delay(3000);
  }
}