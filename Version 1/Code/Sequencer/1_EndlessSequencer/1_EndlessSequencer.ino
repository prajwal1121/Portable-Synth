//
// 'Endless' Sequencer
// Written by Prajwal Tumkur Mahesh
//

#include "Pizzicato_samples.h"
#include "piano_samples.h"
#include "standard_DRUMS_samples.h"
#include "distortiongt_samples.h"
#include "Ocarina_samples.h"

#include <Audio.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WS2812Serial.h>
#define OLED_RESET -1 

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

const byte TOTAL_VOICES = 32;
const byte TOTAL_MIXERS = 11;
const byte SECONDARY_MIXERS = 2;

AudioControlSGTL5000 sgtl5000_1;
AudioSynthWavetable wavetable[TOTAL_VOICES];
AudioMixer4 mixer[TOTAL_MIXERS];
AudioOutputI2S i2s1;
AudioConnection patchCord[] = {
  {wavetable[0], 0, mixer[0], 0}, {wavetable[1], 0, mixer[0], 1}, {wavetable[2], 0, mixer[0],  2}, {wavetable[3], 0, mixer[0],  3}, {mixer[0], 0, mixer[TOTAL_MIXERS - 2], 0},
  {wavetable[4], 0, mixer[1], 0}, {wavetable[5], 0, mixer[1], 1}, {wavetable[6], 0, mixer[1],  2}, {wavetable[7], 0, mixer[1],  3}, {mixer[1], 0, mixer[TOTAL_MIXERS - 2], 1},
  {wavetable[8], 0, mixer[2], 0}, {wavetable[9], 0, mixer[2], 1}, {wavetable[10], 0, mixer[2],  2}, {wavetable[11], 0, mixer[2],  3}, {mixer[2], 0, mixer[TOTAL_MIXERS - 2], 2},
  {wavetable[12], 0, mixer[3], 0}, {wavetable[13], 0, mixer[3], 1}, {wavetable[14], 0, mixer[3],  2}, {wavetable[15], 0, mixer[3],  3}, {mixer[3], 0, mixer[TOTAL_MIXERS - 2], 3},
  {wavetable[16], 0, mixer[4], 0}, {wavetable[17], 0, mixer[4], 1}, {wavetable[18], 0, mixer[4],  2}, {wavetable[19], 0, mixer[4],  3}, {mixer[4], 0, mixer[TOTAL_MIXERS - 3], 0},
  {wavetable[20], 0, mixer[5], 0}, {wavetable[21], 0, mixer[5], 1}, {wavetable[22], 0, mixer[5],  2}, {wavetable[23], 0, mixer[5],  3}, {mixer[5], 0, mixer[TOTAL_MIXERS - 3], 1},
  {wavetable[24], 0, mixer[6], 0}, {wavetable[25], 0, mixer[6], 1}, {wavetable[26], 0, mixer[6],  2}, {wavetable[27], 0, mixer[6],  3}, {mixer[6], 0, mixer[TOTAL_MIXERS - 3], 2},
  {wavetable[28], 0, mixer[7], 0}, {wavetable[29], 0, mixer[7], 1}, {wavetable[30], 0, mixer[7],  2}, {wavetable[31], 0, mixer[7],  3}, {mixer[7], 0, mixer[TOTAL_MIXERS - 3], 3},
  {mixer[TOTAL_MIXERS - 2], 0, mixer[TOTAL_MIXERS - 1], 0},
  {mixer[TOTAL_MIXERS - 3], 0, mixer[TOTAL_MIXERS - 1], 1},
  {mixer[TOTAL_MIXERS - 1], 0, i2s1, 0},
  {mixer[TOTAL_MIXERS - 1], 0, i2s1, 1},
};

struct voice_t {
  int wavetable_id;
  byte channel;
  byte note;
};
voice_t voices[TOTAL_VOICES];

#define numSequences 4
#define numSequenceNotes 40
#define numTSigs 6

byte currentSequence = 0;
bool recordSelect = false;
byte sequenceCounter[numSequences];
byte sequenceLength[numSequences];

float tSigs[numTSigs] = {1,2,4,8,16,32};
byte currentSignature = 0;
struct sequences {
  byte timeSignature;
  byte instrument;
  byte notes[numSequenceNotes];
};
sequences seqs[numSequences];
long seqTimers[numSequences];
bool playSequenceNum[numSequences];
bool addRest;
bool addHold;

bool sequencePlaying[numSequences];

float bpm = 120;
long ms_per_beat = 1.0/(bpm/60000.0);

byte chan = 1;
bool click1 = false; 
bool click2 = false;
bool click3 = false;
bool menuSelect = false;
bool selected = false;
byte menuScreen = 1;
bool left = false;
bool right = false;
bool bpmSelect = false;
bool holdSequenceSelect = false;
bool holdSequence[numSequences];

bool eraseSequenceSelect = false;
bool eraseSequence[numSequences];

byte sequencePlayingCheck = 0;

int vol = 50;

int8_t octave = 48;

void setup() { 
  Wire.begin();
  
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(2);
  display.clearDisplay();
  display.setTextSize(3);      
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(30, 25);     
  display.println(F("WAV"));
  display.display();
  
  AudioMemory(120);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(1.0);
  
  for (int i = 0; i < TOTAL_VOICES; ++i) {
    wavetable[i].setInstrument(distortiongt);
    wavetable[i].amplitude(1);
    voices[i].wavetable_id = i;
    voices[i].channel = voices[i].note = 0xFF;
  }

  for (int i = 0; i < TOTAL_MIXERS - 1; ++i)
    for (int j = 0; j < 4; ++j)
      mixer[i].gain(j, 0.50);
  for (int i = 0; i < 4; ++i)
    mixer[TOTAL_MIXERS - 1].gain(i, i < SECONDARY_MIXERS ? 1.0 / SECONDARY_MIXERS : 0.0);
  
  for (byte s = 0; s < numSequences; s++){
    for (byte n = 0; n < numSequenceNotes; n++){
      seqs[s].notes[n] = 0;
    }
    sequenceCounter[s] = 0;
    sequenceLength[s] = 0;
    sequencePlaying[s] = 0;
    seqTimers[s] = 0;
    holdSequence[s] = 0;
    playSequenceNum[s] = 0;
    eraseSequence[s] = 0;
  }
  
  AudioInterrupts();
  display.clearDisplay();
}

unsigned long last_time = millis();

void loop() {
  int n = analogRead(15);
  if (n != vol) {
    vol = n;
    sgtl5000_1.volume((float)n / 1023);
  }

  if (millis()-last_time > 25){
    readInputs();
    menuCheck();
    staticMenu();
    last_time = millis();
  }
  
  playKeyboard();
  updateEncoders();
  checkAndPlaySequence();
}
