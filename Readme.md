# Arduino loud music player on RFID detection

The purpose of the project is to automatically play an mp3 stored in an SD card to a 30W speaker if an RFID tag is detected.

## Goals

A sound is played while the good rfid tag is detected.

## Hardware

[SD card module](https://www.amazon.fr/kwmobile-Module-Carte-Micro-microcontrôleurs/dp/B06XHJTGGC/ref=sr_1_10?dchild=1&keywords=Arduino+Sd+Card+Shield&qid=1589977148&sr=8-10)

[micro SD card](https://www.fnac.com/mp35510158/Carte-memoire-micro-SDHC-8Go-8g-Micro-SD-MicroSD-Card-TF-classe-10-Qumox/w-4)

[ELEEGO UNO](https://www.amazon.fr/Elegoo-ATmega328P-ATMEGA16U2-Controller-Microcontrôleur/dp/B01N91PVIS/ref=sr_1_1_sspa?__mk_fr_FR=ÅMÅŽÕÑ&dchild=1&keywords=elegoo+uno&qid=1589977962&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzUE5BS1dSV1IzWjkxJmVuY3J5cHRlZElkPUEwODM2MzA5NU04UjNKUzJBVVNPJmVuY3J5cHRlZEFkSWQ9QTA4OTkzNDczQ05VV0lNS0pRSkJSJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)

[speaker 30W 4 ohms](https://www.amazon.fr/Pioneer-TS-G1010F-Haut-Parleur-Voiture-Voies/dp/B07573XF5R/ref=mp_s_a_1_7?dchild=1&keywords=haut parleur&qid=1589397568&sr=8-7&fbclid=IwAR3QLalxt8ekfAfP696k5mOZuAC9UxwnIf1I0Pc75a8ZV_NZwJelEaJjB6E#HLCXComparisonWidget_feature_div)[module TDA2050](https://www.amazon.fr/TDA2050-Digital-Audio-Amplifier-Adjustable/dp/B07B2H5CTX/ref=sr_1_1?__mk_fr_FR=ÅMÅŽÕÑ&dchild=1&keywords=audio+amplifier+arduino+30W&qid=1589969698&sr=8-1)

Alim 20-24V DC (for TDA2050)

Alim 5-12V DC (for eleego uno)

## Schematic

![](hw/music_player_rf_reader_circuit.jpg)

## HOW TO

We need to convert an audio file into wave file. We can use this online [converter](https://www.online-convert.com/result#j=4578bc61-0a05-4582-b3d9-cf80588846e6) and the following options:

1. In optional settings, change bit resolution to 8 bit.
2. Change sampling rate to 16000 Hz.
3. Change audio channels to Mono.
4. Click on “Show advanced options”.
5. Set the PCM format as PCM unsigned 8-bit.
6. Click on “Convert” and the files are converted

Formatting Micro-SD Card:

1. Install SD Formatter tool
2. Format card
3. Copy wave file