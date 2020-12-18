#include <pcmRF.h>      //Arduino library for asynchronous
#include <pcmConfig.h>  //playback of PCM/WAV files 
#include <TMRpcm.h>     //direct from SD card

#include "SD.h"
#define SD_ChipSelectPin 4    //Define which pin the SD card is connected too
#include "TMRpcm.h"
#include "SPI.h"
 
int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the digital input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

TMRpcm tmrpcm;              //Defining the variable to use within the code
 
void setup() {
  pinMode(inputPin, INPUT);             // declare sensor as input
  tmrpcm.speakerPin = 9;                //Declare which pin the speaker is connected too
  Serial.begin(9600);
if (!SD.begin(SD_ChipSelectPin)) {      // This is to check whether there is a readable micro SD card
Serial.println("SD fail");              // If there is no SD card, this will be printed
return;
}
}
 
void loop(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    if (pirState == LOW) {
      Serial.println("Motion detected!");// Prints out that motion has been detected, lets you know it's working
      pirState = HIGH;
      tmrpcm.setVolume(5);               // Setting the volume that the speaker will output the following file at
      tmrpcm.play("nature.wav");         // This is calling for the WAV file inside the Micro SD card
    }
  } else {
    if (pirState == HIGH){
      Serial.println("Motion ended!");   // Print out that motion has ended, or there is no more motion detected
      pirState = LOW;                    // Change the sensor state back to LOW
    }
  }
}
