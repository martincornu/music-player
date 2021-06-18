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
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"

#define DEBUG

#define SD_CS_PIN             10    /* Pin sur laquelle est branche la pin CS du module carte SD */
#define SPEAKER_PIN           9     /* Pin sur laquelle est branche le positif du haut parleur */

#define VOLUME      4               /* Volume (best quality at 4) */
#define FILENAME    "test.wav"    /* Wave file name to play */
#define OUTPUT_STATE_ON HIGH

#define INPUT_PIN 5 /* set to 1 to start playing audio */

TMRpcm tmrpcm;

void setup(void) {
  #ifdef DEBUG
  Serial.begin(115200);
  Serial.println("S-CAPE Game Saint-Etienne");
  #endif
  
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);

  pinMode(INPUT_PIN, INPUT);
  digitalWrite(INPUT_PIN, LOW);

  tmrpcm.speakerPin=SPEAKER_PIN;
  if(!SD.begin(SD_CS_PIN))
  {
    #ifdef DEBUG
    Serial.println("SD fail");
    #endif
    return;
  }
  tmrpcm.setVolume(VOLUME);
}


void loop(void) {
    if(digitalRead(INPUT_PIN) == HIGH)
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
}
