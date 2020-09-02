/********************************************************
*
* Project: music player
* Filename: music-player-arduino.ino
* Description: This program read a mp3 stored on a SD card and play it on external speaker.
* It plays the music if all inputs are in ON.
* Revision History:
* 10/06/2020 Rev 01.00 Creation (Martin Cornu)
* 
* ------------------------------------------------------------------------- */

#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"

#define DEBUG

#define INPUT_RF_1  2   // entrées des lecteurs rfid

#define SD_CS_PIN   10   /* Pin sur laquelle est branche la pin CS du module carte SD */
#define SPEAKER_PIN 9   /* Pin sur laquelle est branche le positif du haut parleur */
#define VOLUME      4   /* Volume (best quality at 4) */
#define FILENAME    "test.wav" /* Wave file name to play */

TMRpcm tmrpcm;

void setup()
{
  #ifdef DEBUG
  Serial.begin(9600);
  #endif

  pinMode(INPUT_RF_1,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

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
}

void loop() {
  // put your main code here, to run repeatedly:
  //tmrpcm.play("tinkerbell_test.wav");
  if ((digitalRead(INPUT_RF_1) == 1))
  {
    digitalWrite(LED_BUILTIN,HIGH);
    #ifdef DEBUG
    Serial.println("start playing");
    #endif
    tmrpcm.play(FILENAME);
    delay(3000);
  }
  else
  {
    digitalWrite(LED_BUILTIN,LOW);
  }
}
