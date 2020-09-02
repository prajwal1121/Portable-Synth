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

// GUItool: begin automatically generated code
AudioSynthWaveform       lfo;           

AudioSynthWaveform       wave1a;        
AudioSynthWaveform       wave1b;        
AudioSynthNoisePink      noise1;        

AudioSynthWaveform       wave2a;        
AudioSynthWaveform       wave2b;        
AudioSynthNoisePink      noise2;        

AudioSynthWaveform       wave3a; 
AudioSynthWaveform       wave3b;        
AudioSynthNoisePink      noise3;        
       
AudioSynthWaveform       wave4a;        
AudioSynthWaveform       wave4b;        
AudioSynthNoisePink      noise4;        

AudioSynthWaveform       wave5a;        
AudioSynthWaveform       wave5b;        
AudioSynthNoisePink      noise5;        

AudioSynthWaveform       wave6a;        
AudioSynthWaveform       wave6b;        
AudioSynthNoisePink      noise6;        

AudioSynthWaveform       wave7a;        
AudioSynthWaveform       wave7b;        
AudioSynthNoisePink      noise7;        

AudioSynthWaveform       wave8a;        
AudioSynthWaveform       wave8b;        
AudioSynthNoisePink      noise8;

AudioEffectEnvelope      envelope1; 
AudioEffectEnvelope      envelope2; 
AudioEffectEnvelope      envelope3; 
AudioEffectEnvelope      envelope4; 
AudioEffectEnvelope      envelope5; 
AudioEffectEnvelope      envelope6; 
AudioEffectEnvelope      envelope7;
AudioEffectEnvelope      envelope8;

AudioMixer4              wave1mix;      
AudioMixer4              wave2mix;      
AudioMixer4              wave3mix;      
AudioMixer4              wave4mix;      
AudioMixer4              wave5mix;      
AudioMixer4              wave6mix;      
AudioMixer4              wave7mix;      
AudioMixer4              wave8mix;      

AudioFilterStateVariable filter1;
AudioFilterStateVariable filter2;
AudioFilterStateVariable filter3; 
AudioFilterStateVariable filter4;
AudioFilterStateVariable filter5;
AudioFilterStateVariable filter6;
AudioFilterStateVariable filter7;
AudioFilterStateVariable filter8;

AudioMixer4              secondary_mixer1;
AudioMixer4              secondary_mixer2;

AudioMixer4              primary_mixer;

AudioOutputI2S           i2s1;

AudioConnection          patchCord1(lfo, 0, filter1, 1);
AudioConnection          patchCord2(lfo, 0, filter2, 1);
AudioConnection          patchCord3(lfo, 0, filter3, 1);
AudioConnection          patchCord4(lfo, 0, filter4, 1);
AudioConnection          patchCord5(lfo, 0, filter5, 1);
AudioConnection          patchCord6(lfo, 0, filter6, 1);
AudioConnection          patchCord7(lfo, 0, filter7, 1);
AudioConnection          patchCord8(lfo, 0, filter8, 1);

AudioConnection          patchCord9(wave1a, 0, wave1mix, 0);
AudioConnection          patchCord10(wave1b, 0, wave1mix, 1);
AudioConnection          patchCord11(noise1, 0, wave1mix, 2);

AudioConnection          patchCord12(wave2a, 0, wave2mix, 0);
AudioConnection          patchCord13(wave2b, 0, wave2mix, 1);
AudioConnection          patchCord14(noise2, 0, wave2mix, 2);

AudioConnection          patchCord15(wave3a, 0, wave3mix, 0);
AudioConnection          patchCord16(wave3b, 0, wave3mix, 1);
AudioConnection          patchCord17(noise3, 0, wave3mix, 2);

AudioConnection          patchCord18(wave4a, 0, wave4mix, 0);
AudioConnection          patchCord19(wave4b, 0, wave4mix, 1);
AudioConnection          patchCord20(noise4, 0, wave4mix, 2);

AudioConnection          patchCord21(wave5a, 0, wave5mix, 0);
AudioConnection          patchCord22(wave5b, 0, wave5mix, 1);
AudioConnection          patchCord23(noise5, 0, wave5mix, 2);

AudioConnection          patchCord24(wave6a, 0, wave6mix, 0);
AudioConnection          patchCord25(wave6b, 0, wave6mix, 1);
AudioConnection          patchCord26(noise6, 0, wave6mix, 2);

AudioConnection          patchCord27(wave7a, 0, wave7mix, 0);
AudioConnection          patchCord28(wave7b, 0, wave7mix, 1);
AudioConnection          patchCord29(noise7, 0, wave7mix, 2);

AudioConnection          patchCord30(wave8a, 0, wave8mix, 0);
AudioConnection          patchCord31(wave8b, 0, wave8mix, 1);
AudioConnection          patchCord32(noise8, 0, wave8mix, 2);

AudioConnection          patchCord33(wave1mix, envelope1);
AudioConnection          patchCord34(wave2mix, envelope2);
AudioConnection          patchCord35(wave3mix, envelope3);
AudioConnection          patchCord36(wave4mix, envelope4);
AudioConnection          patchCord37(wave5mix, envelope5);
AudioConnection          patchCord38(wave6mix, envelope6);
AudioConnection          patchCord39(wave7mix, envelope7);
AudioConnection          patchCord40(wave8mix, envelope8);

AudioConnection          patchCord41(envelope1, 0, filter1, 0);
AudioConnection          patchCord42(envelope2, 0, filter2, 0);
AudioConnection          patchCord43(envelope3, 0, filter3, 0);
AudioConnection          patchCord44(envelope4, 0, filter4, 0);
AudioConnection          patchCord45(envelope5, 0, filter5, 0);
AudioConnection          patchCord46(envelope6, 0, filter6, 0);
AudioConnection          patchCord47(envelope7, 0, filter7, 0);
AudioConnection          patchCord48(envelope8, 0, filter8, 0);

AudioConnection          patchCord49(filter1, 0, secondary_mixer1, 0);
AudioConnection          patchCord50(filter2, 0, secondary_mixer1, 1);
AudioConnection          patchCord51(filter3, 0, secondary_mixer1, 2);
AudioConnection          patchCord52(filter4, 0, secondary_mixer1, 3);
AudioConnection          patchCord53(filter5, 0, secondary_mixer2, 0);
AudioConnection          patchCord54(filter6, 0, secondary_mixer2, 1);
AudioConnection          patchCord55(filter7, 0, secondary_mixer2, 2);
AudioConnection          patchCord56(filter8, 0, secondary_mixer2, 3);

AudioConnection          patchCord57(secondary_mixer1, 0, primary_mixer, 0);
AudioConnection          patchCord58(secondary_mixer2, 0, primary_mixer, 1);

AudioConnection          patchCord59(primary_mixer, 0, i2s1, 0);
AudioConnection          patchCord60(primary_mixer, 0, i2s1, 1);

AudioControlSGTL5000     sgtl5000_1;     
// GUItool: end automatically generated code

AudioSynthWaveform *a_bank[8] = {&wave1a,&wave2a,&wave3a,&wave4a,&wave5a,&wave6a,&wave7a,&wave8a};
AudioSynthWaveform *b_bank[8] = {&wave1b,&wave2b,&wave3b,&wave4b,&wave5b,&wave6b,&wave7b,&wave8b};
AudioSynthNoisePink *noise_bank[8] = {&noise1,&noise2,&noise3,&noise4,&noise5,&noise6,&noise7,&noise8};
AudioEffectEnvelope *envelope_bank[8] = {&envelope1,&envelope2,&envelope3,&envelope4,&envelope5,&envelope6,&envelope7,&envelope8};
AudioFilterStateVariable *filter_bank[8] = {&filter1,&filter2,&filter3,&filter4,&filter5,&filter6,&filter7,&filter8};

bool click1 = 0; 
bool click2 = 0;
bool click3 = 0;

byte screen = 2;

int vol = 50;

int8_t octave = 0;
bool left = false;
bool right = false;

#define numOscillators 3 
byte waveShape[numOscillators] = {0,0,0};
float waveFrequency[numOscillators] = {2.0,2.0,2.0};
float waveAmplitude[numOscillators] = {1.0,1.0,1.0};
byte voiceStates[8] = {0,0,0,0,0,0,0};

byte lfoShape = 0;
float lfoFrequency = 0;
float lfoAmplitude = 0;

int semitonesTune = 12;
int detunePercent = 0;
float detuneFactor = 1;

int filterFreq = 1000;
float filterQ = 1.0;

#define envParameters 4 
float adsr[envParameters] = {10.5,35.0,1.0,300};
char adsrNames[envParameters] = {'A','D','S','R'};
void setup() {
  //Serial.begin(9600);
  
  Wire.begin();

  AudioMemory(60);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.2);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(2);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  for (byte a = 0; a < 8; a++){
    a_bank[a]->begin(WAVEFORM_SINE);
    a_bank[a]->amplitude(0.75);
    a_bank[a]->frequency(82.41);
    a_bank[a]->pulseWidth(0.15);
  }

  for (byte b = 0; b < 8; b++){
    b_bank[b]->begin(WAVEFORM_SINE);
    b_bank[b]->amplitude(0.75);
    b_bank[b]->frequency(123);
    b_bank[b]->pulseWidth(0.15);
  }

  for (byte n = 0; n < 8; n++){
    noise_bank[n]->amplitude(0.75);
  }

  for (byte n = 0; n < 8; n++){
    envelope_bank[n]->noteOff();
  }

  for (byte n = 0; n < 8; n++){
    filter_bank[n]->octaveControl(7);
    filter_bank[n]->frequency(filterFreq);
    filter_bank[n]->resonance(filterQ);
  }

  lfo.frequency(lfoFrequency);
  lfo.amplitude(lfoAmplitude);
  lfo.begin(0);
}

unsigned long last_time = millis(); 

void loop() {
  int n = analogRead(15);
  if (n != vol) {
    vol = n;
    sgtl5000_1.volume((float)n / 1023);
  }
  
  if (millis()-last_time > 50){
    readInputs();
    menuCheck();
    staticMenu();
    last_time = millis();
  }
  
  updateEncoders();
  playKeyboard();
}
