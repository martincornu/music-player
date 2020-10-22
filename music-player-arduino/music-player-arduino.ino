/********************************************************
*
* Project: music player
* Filename: music-player-and-ouput.ino
* Description: This program read an input and if it is HIGH then
* it read a mp3 stored on a SD card and play it on external speaker and
* also activate an ouput.
* Revision History:
* 23/09/2020 Rev 01.00 Creation (Martin Cornu)
* 01/10/2020 Rev 1.1 Bugs fixs - exit program too quickly - input RF default state HIGH
* 22/10/2020 Rev 1.2 Bugs fixs - input pull up - bounce effect
* ------------------------------------------------------------------------- */

#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"

#define DEBUG

#define INPUT_1		2   /* entrée qui doit être activée */
#define OUTPUT_1	3

#define SD_CS_PIN   10   /* Pin sur laquelle est branche la pin CS du module carte SD */
#define SPEAKER_PIN 9   /* Pin sur laquelle est branche le positif du haut parleur */
#define VOLUME      4   /* Volume (best quality at 4) */
#define FILENAME    "test.wav" /* Wave file name to play */

// Variables will change:
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

TMRpcm tmrpcm;

void setup()
{
  #ifdef DEBUG
  Serial.begin(9600);
  #endif

  pinMode(INPUT_1,INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(OUTPUT_1, OUTPUT);

  digitalWrite(LED_BUILTIN,LOW);
  digitalWrite(OUTPUT_1,LOW);
  
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
   int reading = digitalRead(INPUT_1);
    // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
        digitalWrite(LED_BUILTIN,HIGH);
        digitalWrite(OUTPUT_1,HIGH);
        #ifdef DEBUG
        Serial.println("start playing");
        #endif
        tmrpcm.play(FILENAME);
        delay(60000);         /* Wait 1min to be sure audio wav finished */
        exit(0);
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
