//
// Combined Sequencer/Synthesizer/Sampler/Recorder
// Written by Prajwal Tumkur Mahesh
//
#include <Arduino.h>

#include "Audio.h"
#include <SPI.h>
#include <Si4703_Breakout.h>

/*
 *Include and define all the functional parts
 */
#include "SDHeader.h"
SdFat SD;
#include "Display.h"
Display display;
#include "AudioConfig.h"
#include "ReadInputs.h"
ReadInputs inputs;
#include "Switcher.h"
Switcher switcher;
#include "Mixer.h"
Mixer mixer;
#include "Synth.h"
Synth synth;
#include "Sampler.h"
Sampler sampler;
#include "Sequencer.h"
Sequencer sequencer;
#include "Recorder.h"
Recorder recorder;
#include "PlayKeyboard.h"
PlayKeyboard keyboard;

void setup() {
  initAudio();
  display.startup();
}

//Timing Variables
uint32_t last_time_input = millis();
uint32_t last_time_display = millis();
uint32_t last_time_print = millis();

// A thing for volume
int vol = 50;

void loop() {
  //Read and set volume
  int n = analogRead(15);
  if (n != vol) {
    vol = n;
    codec.volume((float)n / 1023);
  }

  switch(function){
   case 0://Synth
      //Update every 10ms
      synth.menuCheck();  //See if menu needs updating
      if (millis()-last_time_display > 10){
        synth.staticMenu(); //Refresh display
        last_time_display = millis();
      }
    break;
    case 1://Sampler
      sampler.menuCheck();  //See if menu needs updating
      //Update every 10ms
      if (millis()-last_time_display > 10){
        sampler.staticMenu (); //Refresh display
        last_time_display = millis();
      }
    break;
    case 2://Sequencer
      sequencer.menuCheck();  //See if menu needs updating
      //Update every 10ms
      if (millis()-last_time_display > 10){
        sequencer.staticMenu(); //Refresh display
        last_time_display = millis();
      }
    break;
    case 3://Mixer
      mixer.menuCheck();  //See if menu needs updating
      //Update every 10ms
      if (millis()-last_time_display > 10){
        mixer.staticMenu(); //Refresh display
        last_time_display = millis();
      }
    break;
    case 4://Recorder
      recorder.menuCheck();  //See if menu needs updating
      //Update every 10ms
      if (millis()-last_time_display > 10){
        recorder.staticMenu(); //Refresh display
        last_time_display = millis();
      }
    break;
  }
      
  //Update every 25ms
  if (millis()-last_time_input > 25){
    inputs.readInputs(); //Request fresh user input data
    last_time_input = millis();
    switcher.switchMode();
    if (function==4 and !(recordStatus==1))recorder.showRMS();
  }

  //Update as fast as possible
  inputs.updateEncoders();
  keyboard.play();
  recorder.recordAndPlayback();
  
  /*
  //Enable for memory and processor  diagnostics
  if (millis()-last_time_print > 100){
    Serial.print(F("all="));
    Serial.print(AudioProcessorUsage());
    Serial.print(F(","));
    Serial.print(AudioProcessorUsageMax());
    Serial.print(F("    "));
    Serial.print(F("Memory: "));
    Serial.print(AudioMemoryUsage());
    Serial.print(F(","));
    Serial.println(AudioMemoryUsageMax());
    last_time_print = millis();
  }
  */
}
