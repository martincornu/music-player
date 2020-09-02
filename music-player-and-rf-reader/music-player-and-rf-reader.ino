/**************************************************************************/
/*! 
    @file     pn532_reader
    @author   Martin CORNU

This program read in loop RFID reader.
If a tag is present, it checks its ID and if the ID is correct it trigger an output.
*/
/**************************************************************************/
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"

#define DEBUG


// If using the breakout with SPI, define the pins for SPI communication.
#define PN532_SCK           (2)
#define PN532_MOSI          (3)
#define PN532_SS            (4)
#define PN532_MISO          (5)
#define SD_CS_PIN             10   /* Pin sur laquelle est branche la pin CS du module carte SD */
#define SPEAKER_PIN           9   /* Pin sur laquelle est branche le positif du haut parleur */

#define VOLUME      4   /* Volume (best quality at 4) */
#define FILENAME    "test.wav" /* Wave file name to play */
#define CARD_ID         (uint32_t)57499947
#define OUTPUT_STATE_ON HIGH

TMRpcm tmrpcm;

// Use this line for a breakout with a SPI connection:
Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

void setup(void) {
  #ifdef DEBUG
  Serial.begin(115200);
  Serial.println("S-CAPE Game Saint-Etienne");
  #endif
  
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);

  tmrpcm.speakerPin=SPEAKER_PIN;
  if(!SD.begin(SD_CS_PIN))
  {
    #ifdef DEBUG
    Serial.println("SD fail");
    #endif
    return;
  }
  tmrpcm.setVolume(VOLUME);

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    #ifdef DEBUG
    Serial.print("Didn't find PN53x board");
    #endif
    while (1); // halt
  }
  // Got ok data, print it out!
  #ifdef DEBUG
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  #endif
  
  // configure board to read RFID tags
  nfc.SAMConfig();

  #ifdef DEBUG
  Serial.println("Waiting for an ISO14443A Card ...");
  #endif
}


void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 1000);
  
  if (success) {
    if (uidLength == 4)
    {
      // We probably have a Mifare Classic card ... 
      uint32_t cardid = uid[0];
      cardid <<= 8;
      cardid |= uid[1];
      cardid <<= 8;
      cardid |= uid[2];  
      cardid <<= 8;
      cardid |= uid[3]; 
      
      #ifdef DEBUG
      Serial.print("ID #");
      Serial.println(cardid);

      if(cardid == CARD_ID)
      {
        digitalWrite(LED_BUILTIN,HIGH);
        #ifdef DEBUG
        Serial.println("RFID OK! ACTIVATION OF OUTPUT");
        #endif
        /* play sound */
        tmrpcm.play(FILENAME);
        delay(3000);
      }
      else
      {
        digitalWrite(LED_BUILTIN,LOW);
      }
      #endif
    }
    else
    {
      digitalWrite(LED_BUILTIN,LOW);
    }
    #ifdef DEBUG
    Serial.println("");
    #endif
  }
  else
  {
      digitalWrite(LED_BUILTIN,LOW);
  }
}
