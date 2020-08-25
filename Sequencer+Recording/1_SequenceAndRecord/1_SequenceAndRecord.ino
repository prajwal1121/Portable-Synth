//
// Sequencer With Record
// Written by Prajwal Tumkur Mahesh
//

#include "Pizzicato_samples.h"
#include "piano_samples.h"
#include "standard_DRUMS_samples.h"
#include "distortiongt_samples.h"
#include "Ocarina_samples.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WS2812Serial.h>
#define OLED_RESET -1 

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

AudioControlSGTL5000 sgtl5000_1;

//Audio Network for Wavetable Synthesis
#define TOTAL_VOICES 32
#define TOTAL_SYNTH_MIXERS 11
#define SECONDARY_SYNTH_MIXERS 3
AudioSynthWavetable wavetable[TOTAL_VOICES];
AudioMixer4 synth_mixer[TOTAL_SYNTH_MIXERS];
AudioOutputI2S i2s1;
AudioConnection patchCord[] = {
  {wavetable[0], 0, synth_mixer[0], 0}, {wavetable[1], 0, synth_mixer[0], 1}, {wavetable[2], 0, synth_mixer[0],  2}, {wavetable[3], 0, synth_mixer[0],  3}, {synth_mixer[0], 0, synth_mixer[TOTAL_SYNTH_MIXERS - 2], 0},
  {wavetable[4], 0, synth_mixer[1], 0}, {wavetable[5], 0, synth_mixer[1], 1}, {wavetable[6], 0, synth_mixer[1],  2}, {wavetable[7], 0, synth_mixer[1],  3}, {synth_mixer[1], 0, synth_mixer[TOTAL_SYNTH_MIXERS - 2], 1},
  {wavetable[8], 0, synth_mixer[2], 0}, {wavetable[9], 0, synth_mixer[2], 1}, {wavetable[10], 0, synth_mixer[2],  2}, {wavetable[11], 0, synth_mixer[2],  3}, {synth_mixer[2], 0, synth_mixer[TOTAL_SYNTH_MIXERS - 2], 2},
  {wavetable[12], 0, synth_mixer[3], 0}, {wavetable[13], 0, synth_mixer[3], 1}, {wavetable[14], 0, synth_mixer[3],  2}, {wavetable[15], 0, synth_mixer[3],  3}, {synth_mixer[3], 0, synth_mixer[TOTAL_SYNTH_MIXERS - 2], 3},
  {wavetable[16], 0, synth_mixer[4], 0}, {wavetable[17], 0, synth_mixer[4], 1}, {wavetable[18], 0, synth_mixer[4],  2}, {wavetable[19], 0, synth_mixer[4],  3}, {synth_mixer[4], 0, synth_mixer[TOTAL_SYNTH_MIXERS - 3], 0},
  {wavetable[20], 0, synth_mixer[5], 0}, {wavetable[21], 0, synth_mixer[5], 1}, {wavetable[22], 0, synth_mixer[5],  2}, {wavetable[23], 0, synth_mixer[5],  3}, {synth_mixer[5], 0, synth_mixer[TOTAL_SYNTH_MIXERS - 3], 1},
  {wavetable[24], 0, synth_mixer[6], 0}, {wavetable[25], 0, synth_mixer[6], 1}, {wavetable[26], 0, synth_mixer[6],  2}, {wavetable[27], 0, synth_mixer[6],  3}, {synth_mixer[6], 0, synth_mixer[TOTAL_SYNTH_MIXERS - 3], 2},
  {wavetable[28], 0, synth_mixer[7], 0}, {wavetable[29], 0, synth_mixer[7], 1}, {wavetable[30], 0, synth_mixer[7],  2}, {wavetable[31], 0, synth_mixer[7],  3}, {synth_mixer[7], 0, synth_mixer[TOTAL_SYNTH_MIXERS - 3], 3},
  {synth_mixer[TOTAL_SYNTH_MIXERS - 2], 0, synth_mixer[TOTAL_SYNTH_MIXERS - 1], 0},
  {synth_mixer[TOTAL_SYNTH_MIXERS - 3], 0, synth_mixer[TOTAL_SYNTH_MIXERS - 1], 1},
  {synth_mixer[TOTAL_SYNTH_MIXERS - 1], 0, i2s1, 0},
  {synth_mixer[TOTAL_SYNTH_MIXERS - 1], 0, i2s1, 1},
};

//Audio Network for Recorder
AudioInputI2S            i2s2;        
AudioMixer4              record_input_mixer;
AudioAnalyzePeak         record_input_peak;               
AudioRecordQueue         record_input_queue;         
AudioPlaySdRaw           playRaw1;       
AudioMixer4              record_output_mixer;
AudioAnalyzePeak         record_output_peak;
AudioRecordQueue         internal_recording_queue; 
AudioConnection          patchCord1(i2s2, 0, record_input_mixer, 0);
AudioConnection          patchCord2(i2s2, 1, record_input_mixer, 1);
AudioConnection          patchCord3(record_input_mixer, 0, record_input_queue, 0);
AudioConnection          patchCord4(record_input_mixer, 0, record_input_peak, 0);
AudioConnection          patchCord5(record_input_mixer, 0, record_output_mixer, 1);
AudioConnection          patchCord6(playRaw1, 0, record_output_mixer, 0);
AudioConnection          patchCord7(record_output_mixer, 0, record_output_peak, 0);
AudioConnection          patchCord8(record_output_mixer, 0, synth_mixer[TOTAL_SYNTH_MIXERS - 1], 2);
AudioConnection          patchCord9(synth_mixer[TOTAL_SYNTH_MIXERS - 1], 0, internal_recording_queue, 0);

/*
 * Wavetable Globals
 */
struct voice_t {
  int wavetable_id;
  byte channel;
  byte note;
};
voice_t voices[TOTAL_VOICES];

byte chan = 1;
int8_t octave = 48;

/*
 * Sequencer Globals
 */
#define numSequences 4
#define numSequenceNotes 40
#define numTSigs 6

struct sequences {
  byte timeSignature;
  byte instrument;
  byte notes[numSequenceNotes];
};
sequences seqs[numSequences];
byte currentSequence = 0;
byte sequenceCounter[numSequences];
byte sequenceLength[numSequences];
bool playSequenceNum[numSequences];
bool sequencePlaying[numSequences];
bool holdSequence[numSequences];
bool eraseSequence[numSequences];
byte sequencePlayingCheck = 0;

float tSigs[numTSigs] = {1,2,4,8,16,32};
byte currentSignature = 0;
long seqTimers[numSequences];
float bpm = 120;
long ms_per_beat = 1.0/(bpm/60000.0);

bool recordSequenceSelect = 0;
bool addRest;
bool addHold;
bool bpmSelect = false;
bool holdSequenceSelect = false;
bool eraseSequenceSelect = false;

/*
 * Recorder Globals
 */
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  
#define SDCARD_SCK_PIN   13

#define numRecordFiles 10
struct recordings {
  File file;
  char fileName[12];
  unsigned long fileSize;
  byte sourceType;
};
recordings recs[numRecordFiles];
byte currentRecording = 0;
unsigned long currentStartTime = 0;
unsigned long currentEndTime = 0;
byte recordMode = 0;  
bool showPlaying = 0;

struct playerKeys {
  byte fileNum;
  unsigned long startTime;
  unsigned long endTime;
  float mixerGain;
};
playerKeys pk[24];
byte playerKeyMode[24];

bool recordButton = 0;
bool recordSelect = 0;
bool previewSelect = 0;
bool keyBindSelect = 0;
bool keyUnbindSelect = 0;
byte startOrEndSelect = 0;

byte currentScreen_Recorder = 0;

float outputGain = 1.0;
int8_t microphoneGain = 36;

/*
 * General Control Globals
 */
bool click1 = false; 
bool click2 = false;
bool click3 = false;
bool menuSelect = false;
bool selected = false;
byte menuScreen = 1;
bool left = false;
bool right = false;

int vol = 50;

/*
 * LED Setup
 */
const int numled = 10;
const int pin = 29;
byte drawingMemory[numled*3];         //  3 bytes per LED
DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED
WS2812Serial leds(numled, displayMemory, drawingMemory, pin, WS2812_GRB);

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Initialize the Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(2);
  display.clearDisplay();
  display.setTextSize(3);      
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(20, 15);     
  display.println(F("SYNTH"));
  display.display();

  //Give Audio Library a lot of memory to work with
  AudioMemory(120);

  // Initialize the Codec
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.volume(0.5);
  sgtl5000_1.micGain(microphoneGain);

  // Initialize the SD card
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      //Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  //Initialize LEDs
  leds.begin();
  leds.setBrightness(1);
  turnOffLEDs();

  //Initialize Wavetable Voices
  for (int i = 0; i < TOTAL_VOICES; ++i) {
    wavetable[i].setInstrument(distortiongt);
    wavetable[i].amplitude(1);
    voices[i].wavetable_id = i;
    voices[i].channel = voices[i].note = 0xFF;
  }

  //Initialize Wavetable Mixers
  for (int i = 0; i < TOTAL_SYNTH_MIXERS - 1; ++i)
    for (int j = 0; j < 4; ++j)
      synth_mixer[i].gain(j, 0.50);
  for (int i = 0; i < 4; ++i)
    synth_mixer[TOTAL_SYNTH_MIXERS - 1].gain(i, i < SECONDARY_SYNTH_MIXERS ? 1.0 / SECONDARY_SYNTH_MIXERS : 0.0);

  //Initialize Sequences
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

  //Initialize Recording Playback Keys
  for (byte i = 0; i<24; i++){
    playerKeyMode[i] = 0;
    pk[i].fileNum = 255;
    pk[i].startTime = 0;
    pk[i].endTime = 0;
    pk[i].mixerGain = outputGain;
  }
  record_output_mixer.gain(0,outputGain);
  record_output_mixer.gain(1,0);

  //Initialize Record File Names
  for (int i = 0; i < numRecordFiles; i++){
    sprintf(recs[i].fileName, "REC%d.RAW", i+1);
  }

  AudioInterrupts();
  display.clearDisplay();
}

//Update Timer
unsigned long last_time = millis();

void loop() {
  //Read and set volume
  int n = analogRead(15);
  if (n != vol) {
    vol = n;
    sgtl5000_1.volume((float)n / 1023);
  }

  //Update every 50ms
  if (millis()-last_time > 50){
    readInputs(); //Read keypad
    menuCheck();  //See if menu needs updating
    staticMenu(); //Refresh display
    doLEDs();     //Refresh LEDs
    last_time = millis();
  }

  updateEncoders();
  recordAndStore();
  checkAndPlaySequence();
  playKeyboard();
}
