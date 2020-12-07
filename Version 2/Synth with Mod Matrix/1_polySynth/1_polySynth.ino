#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <WS2812Serial.h>
#include <ArduinoTapTempo.h>

/*Pin configurations and settings for
 * SSD1351 Color OLED Display
 */
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>

#define OLED_RESET -1 
// Screen dimensions
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128 

//Extra pins for SPI
#define DC_PIN   40
#define CS_PIN   38
#define RST_PIN  41

Adafruit_SSD1351 oled = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI1, CS_PIN, DC_PIN, RST_PIN);

// Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xFA20
#define GREEN           0x47E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFD60  
#define WHITE           0xFFFF
#define LAVENDER        0xfcebff

/*Pin configurations and settings for
 * Neopi
 */
const int numled = 10;
const int pin = 17;

byte drawingMemory[numled*3];         //  3 bytes per LED
DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED

WS2812Serial leds(numled, displayMemory, drawingMemory, pin, WS2812_GRB);

/*Pin configurations and settings for
 * LEDs
 */
#define enc1LED 32
#define enc2LED 31
#define enc3LED 30
#define enc4LED 29

/*
 * Audio System Design Tool Output
 */
// GUItool: begin automatically generated code
AudioSynthWaveformDc     env1_dc;            //xy=230.42852783203125,448.0000305175781
AudioSynthWaveformDc     env2_dc; //xy=233.5714111328125,530.2857055664062
AudioMixer4              LFO2_mixer; //xy=404.2857418060303,342.8571548461914
AudioMixer4              env1_mixer;         //xy=404,441
AudioMixer4              env2_mixer;         //xy=404,525
AudioMixer4              LFO1_mixer; //xy=407.28570556640625,247.28573608398438
AudioSynthWaveformModulated mod_LFO1;   //xy=573.2938232421875,254.00814819335938
AudioSynthWaveformModulated mod_LFO2;   //xy=574.2938766479492,350.0081424713135
AudioEffectEnvelope      mod_env1; //xy=587.1509399414062,438.5795650482178
AudioEffectEnvelope      mod_env2; //xy=590.0081405639648,525.7224168777466
AudioMixer4              osc2_pitch_mod_mixer;         //xy=919.0056762695312,508.7199401855469
AudioMixer4              osc1_pitch_mod_mixer;         //xy=920.0057373046875,285.719970703125
AudioMixer4              filter_cutoff_mod_mixer;         //xy=921.0057373046875,78.71427917480469
AudioSynthWaveformModulated wave2a; //xy=1169.005729675293,421.71996116638184
AudioSynthWaveformModulated wave2b; //xy=1169.0114421844482,455.71998262405396
AudioSynthWaveformModulated wave5b; //xy=1169.0114421844482,884.719982624054
AudioSynthWaveformModulated wave1a;   //xy=1172.0000171661377,292.7199249267578
AudioSynthWaveformModulated wave8a; //xy=1168.005729675293,1299.3563747406006
AudioSynthWaveformModulated wave3a; //xy=1171.005729675293,559.7199611663818
AudioSynthWaveformModulated wave1b; //xy=1172.005729675293,326.71994638442993
AudioSynthWaveformModulated wave8b; //xy=1168.0114421844482,1333.3563961982727
AudioSynthWaveformModulated wave3b; //xy=1171.0114421844482,593.719982624054
AudioSynthWaveformModulated wave4a; //xy=1173.005729675293,705.7199611663818
AudioSynthWaveformModulated wave4b; //xy=1173.0114421844482,739.719982624054
AudioSynthWaveformModulated wave5a; //xy=1174.0057067871094,851.7199697494507
AudioSynthWaveformModulated wave6a; //xy=1174.005729675293,988.7199611663818
AudioSynthWaveformModulated wave6b; //xy=1174.0114421844482,1022.719982624054
AudioSynthWaveformModulated wave7a; //xy=1174.005729675293,1131.7199611663818
AudioSynthWaveformModulated wave7b; //xy=1174.0114421844482,1165.719982624054
AudioSynthNoisePink      noise2;         //xy=1194.0000534057617,489.7142848968506
AudioSynthNoisePink      noise1;         //xy=1196.0000534057617,360.7142848968506
AudioSynthNoisePink      noise3;         //xy=1197.0000534057617,627.7142848968506
AudioSynthNoisePink      noise4;         //xy=1198.0000534057617,773.7142848968506
AudioSynthNoisePink      noise5;         //xy=1199.0000534057617,918.7142848968506
AudioSynthNoisePink      noise6;         //xy=1205.0000534057617,1055.7142848968506
AudioSynthNoisePink      noise7;         //xy=1205.0000534057617,1198.7142848968506
AudioSynthNoisePink      noise8;         //xy=1210.0000534057617,1366.7142848968506
AudioMixer4              wave1mix;       //xy=1339.0000534057617,342.7142848968506
AudioMixer4              wave2mix;       //xy=1341.0000534057617,475.7142848968506
AudioMixer4              wave3mix;       //xy=1347.0000534057617,609.7142848968506
AudioMixer4              wave4mix;       //xy=1350.0000534057617,757.7142848968506
AudioMixer4              wave5mix;       //xy=1353.0000534057617,901.7142848968506
AudioMixer4              wave6mix;       //xy=1354.0000534057617,1039.7142848968506
AudioMixer4              wave7mix;       //xy=1359.0000534057617,1183.7142848968506
AudioMixer4              wave8mix;       //xy=1363.0000534057617,1350.7142848968506
AudioEffectEnvelope      envelope1;      //xy=1483.0000534057617,341.7142848968506
AudioEffectEnvelope      envelope2;      //xy=1491.0000534057617,476.7142848968506
AudioEffectEnvelope      envelope4;      //xy=1499.0000534057617,757.7142848968506
AudioEffectEnvelope      envelope3;      //xy=1507.0000534057617,610.7142848968506
AudioEffectEnvelope      envelope6;      //xy=1506.0000534057617,1039.7142848968506
AudioEffectEnvelope      envelope5;      //xy=1507.0000534057617,901.7142848968506
AudioEffectEnvelope      envelope7;      //xy=1515.0000534057617,1185.7142848968506
AudioEffectEnvelope      envelope8;      //xy=1523.0000534057617,1350.7142848968506
AudioFilterStateVariable filter1;        //xy=1636.0000534057617,347.7142848968506
AudioFilterStateVariable filter2;        //xy=1645.0000534057617,482.7142848968506
AudioFilterStateVariable filter4;        //xy=1652.0000534057617,765.7142848968506
AudioFilterStateVariable filter3;        //xy=1653.0000534057617,618.7142848968506
AudioFilterStateVariable filter5;        //xy=1661.0000534057617,907.7142848968506
AudioFilterStateVariable filter6;        //xy=1661.0000534057617,1045.7142848968506
AudioFilterStateVariable filter7;        //xy=1670.0000534057617,1192.7142848968506
AudioFilterStateVariable filter8;        //xy=1675.0000534057617,1355.7142848968506
AudioMixer4              secondary_mixer1; //xy=1937.0000534057617,739.7142848968506
AudioMixer4              secondary_mixer2; //xy=1941.0000534057617,912.7142848968506
AudioMixer4              primary_mixer;  //xy=2189.0000534057617,826.7142848968506
AudioOutputI2S           i2s1;           //xy=2413.0000534057617,825.7142848968506
AudioConnection          patchCord1(env1_dc, 0, env1_mixer, 2);
AudioConnection          patchCord2(env2_dc, 0, env2_mixer, 2);
AudioConnection          patchCord3(LFO2_mixer, 0, mod_LFO2, 0);
AudioConnection          patchCord4(env1_mixer, mod_env1);
AudioConnection          patchCord5(env2_mixer, mod_env2);
AudioConnection          patchCord6(LFO1_mixer, 0, mod_LFO1, 0);
AudioConnection          patchCord7(mod_LFO1, 0, osc1_pitch_mod_mixer, 0);
AudioConnection          patchCord8(mod_LFO1, 0, filter_cutoff_mod_mixer, 0);
AudioConnection          patchCord9(mod_LFO1, 0, osc2_pitch_mod_mixer, 0);
AudioConnection          patchCord10(mod_LFO1, 0, LFO2_mixer, 0);
AudioConnection          patchCord11(mod_LFO1, 0, env1_mixer, 0);
AudioConnection          patchCord12(mod_LFO1, 0, env2_mixer, 0);
AudioConnection          patchCord13(mod_LFO2, 0, osc1_pitch_mod_mixer, 1);
AudioConnection          patchCord14(mod_LFO2, 0, osc2_pitch_mod_mixer, 1);
AudioConnection          patchCord15(mod_LFO2, 0, LFO1_mixer, 0);
AudioConnection          patchCord16(mod_LFO2, 0, filter_cutoff_mod_mixer, 1);
AudioConnection          patchCord17(mod_LFO2, 0, env1_mixer, 1);
AudioConnection          patchCord18(mod_LFO2, 0, env2_mixer, 1);
AudioConnection          patchCord19(mod_env1, 0, osc2_pitch_mod_mixer, 2);
AudioConnection          patchCord20(mod_env1, 0, filter_cutoff_mod_mixer, 2);
AudioConnection          patchCord21(mod_env1, 0, osc1_pitch_mod_mixer, 2);
AudioConnection          patchCord22(mod_env2, 0, filter_cutoff_mod_mixer, 3);
AudioConnection          patchCord23(mod_env2, 0, osc1_pitch_mod_mixer, 3);
AudioConnection          patchCord24(mod_env2, 0, osc2_pitch_mod_mixer, 3);
AudioConnection          patchCord25(osc2_pitch_mod_mixer, 0, wave1b, 0);
AudioConnection          patchCord26(osc2_pitch_mod_mixer, 0, wave2b, 0);
AudioConnection          patchCord27(osc2_pitch_mod_mixer, 0, wave3b, 0);
AudioConnection          patchCord28(osc2_pitch_mod_mixer, 0, wave4b, 0);
AudioConnection          patchCord29(osc2_pitch_mod_mixer, 0, wave5b, 0);
AudioConnection          patchCord30(osc2_pitch_mod_mixer, 0, wave7b, 0);
AudioConnection          patchCord31(osc2_pitch_mod_mixer, 0, wave8b, 0);
AudioConnection          patchCord32(osc1_pitch_mod_mixer, 0, wave1a, 0);
AudioConnection          patchCord33(osc1_pitch_mod_mixer, 0, wave2a, 0);
AudioConnection          patchCord34(osc1_pitch_mod_mixer, 0, wave3a, 0);
AudioConnection          patchCord35(osc1_pitch_mod_mixer, 0, wave4a, 0);
AudioConnection          patchCord36(osc1_pitch_mod_mixer, 0, wave5a, 0);
AudioConnection          patchCord37(osc1_pitch_mod_mixer, 0, wave6a, 0);
AudioConnection          patchCord38(osc1_pitch_mod_mixer, 0, wave7a, 0);
AudioConnection          patchCord39(osc1_pitch_mod_mixer, 0, wave8a, 0);
AudioConnection          patchCord40(filter_cutoff_mod_mixer, 0, filter1, 1);
AudioConnection          patchCord41(filter_cutoff_mod_mixer, 0, filter2, 1);
AudioConnection          patchCord42(filter_cutoff_mod_mixer, 0, filter3, 1);
AudioConnection          patchCord43(filter_cutoff_mod_mixer, 0, filter4, 1);
AudioConnection          patchCord44(filter_cutoff_mod_mixer, 0, filter5, 1);
AudioConnection          patchCord45(filter_cutoff_mod_mixer, 0, filter6, 1);
AudioConnection          patchCord46(filter_cutoff_mod_mixer, 0, filter7, 1);
AudioConnection          patchCord47(filter_cutoff_mod_mixer, 0, filter8, 1);
AudioConnection          patchCord48(wave2a, 0, wave2mix, 0);
AudioConnection          patchCord49(wave2b, 0, wave2mix, 1);
AudioConnection          patchCord50(wave5b, 0, wave5mix, 1);
AudioConnection          patchCord51(wave1a, 0, wave1mix, 0);
AudioConnection          patchCord52(wave8a, 0, wave8mix, 0);
AudioConnection          patchCord53(wave3a, 0, wave3mix, 0);
AudioConnection          patchCord54(wave1b, 0, wave1mix, 1);
AudioConnection          patchCord55(wave8b, 0, wave8mix, 1);
AudioConnection          patchCord56(wave3b, 0, wave3mix, 1);
AudioConnection          patchCord57(wave4a, 0, wave4mix, 0);
AudioConnection          patchCord58(wave4b, 0, wave4mix, 1);
AudioConnection          patchCord59(wave5a, 0, wave5mix, 0);
AudioConnection          patchCord60(wave6a, 0, wave6mix, 0);
AudioConnection          patchCord61(wave6b, 0, wave6mix, 1);
AudioConnection          patchCord62(wave7a, 0, wave7mix, 0);
AudioConnection          patchCord63(wave7b, 0, wave7mix, 1);
AudioConnection          patchCord64(noise2, 0, wave2mix, 2);
AudioConnection          patchCord65(noise1, 0, wave1mix, 2);
AudioConnection          patchCord66(noise3, 0, wave3mix, 2);
AudioConnection          patchCord67(noise4, 0, wave4mix, 2);
AudioConnection          patchCord68(noise5, 0, wave5mix, 2);
AudioConnection          patchCord69(noise6, 0, wave6mix, 2);
AudioConnection          patchCord70(noise7, 0, wave7mix, 2);
AudioConnection          patchCord71(noise8, 0, wave8mix, 2);
AudioConnection          patchCord72(wave1mix, envelope1);
AudioConnection          patchCord73(wave2mix, envelope2);
AudioConnection          patchCord74(wave3mix, envelope3);
AudioConnection          patchCord75(wave4mix, envelope4);
AudioConnection          patchCord76(wave5mix, envelope5);
AudioConnection          patchCord77(wave6mix, envelope6);
AudioConnection          patchCord78(wave7mix, envelope7);
AudioConnection          patchCord79(wave8mix, envelope8);
AudioConnection          patchCord80(envelope1, 0, filter1, 0);
AudioConnection          patchCord81(envelope2, 0, filter2, 0);
AudioConnection          patchCord82(envelope4, 0, filter4, 0);
AudioConnection          patchCord83(envelope3, 0, filter3, 0);
AudioConnection          patchCord84(envelope6, 0, filter6, 0);
AudioConnection          patchCord85(envelope5, 0, filter5, 0);
AudioConnection          patchCord86(envelope7, 0, filter7, 0);
AudioConnection          patchCord87(envelope8, 0, filter8, 0);
AudioConnection          patchCord88(filter1, 0, secondary_mixer1, 0);
AudioConnection          patchCord89(filter2, 0, secondary_mixer1, 1);
AudioConnection          patchCord90(filter4, 0, secondary_mixer1, 3);
AudioConnection          patchCord91(filter3, 0, secondary_mixer1, 2);
AudioConnection          patchCord92(filter5, 0, secondary_mixer2, 0);
AudioConnection          patchCord93(filter6, 0, secondary_mixer2, 1);
AudioConnection          patchCord94(filter7, 0, secondary_mixer2, 2);
AudioConnection          patchCord95(filter8, 0, secondary_mixer2, 3);
AudioConnection          patchCord96(secondary_mixer1, 0, primary_mixer, 0);
AudioConnection          patchCord97(secondary_mixer2, 0, primary_mixer, 1);
AudioConnection          patchCord98(primary_mixer, 0, i2s1, 0);
AudioConnection          patchCord99(primary_mixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2193.0000534057617,1129.7142848968506
// GUItool: end automatically generated code

//Set up pointer arrays for easy addressing
AudioSynthWaveformModulated *a_bank[8] = {&wave1a,&wave2a,&wave3a,&wave4a,&wave5a,&wave6a,&wave7a,&wave8a};
AudioSynthWaveformModulated *b_bank[8] = {&wave1b,&wave2b,&wave3b,&wave4b,&wave5b,&wave6b,&wave7b,&wave8b};
AudioSynthNoisePink *noise_bank[8] = {&noise1,&noise2,&noise3,&noise4,&noise5,&noise6,&noise7,&noise8};
AudioEffectEnvelope *envelope_bank[8] = {&envelope1,&envelope2,&envelope3,&envelope4,&envelope5,&envelope6,&envelope7,&envelope8};
AudioFilterStateVariable *filter_bank[8] = {&filter1,&filter2,&filter3,&filter4,&filter5,&filter6,&filter7,&filter8};


/*
 * Initializing parameter variables
 */
//start off with a sinewave in arbitrary waveform
EXTMEM int16_t arbWave[257];
PROGMEM const int16_t sineWave[257] = {   
       0,   804,  1608,  2410,  3212,  4011,  4808,  5602,  6393,  7179,
    7962,  8739,  9512, 10278, 11039, 11793, 12539, 13279, 14010, 14732,
   15446, 16151, 16846, 17530, 18204, 18868, 19519, 20159, 20787, 21403,
   22005, 22594, 23170, 23731, 24279, 24811, 25329, 25832, 26319, 26790,
   27245, 27683, 28105, 28510, 28898, 29268, 29621, 29956, 30273, 30571,
   30852, 31113, 31356, 31580, 31785, 31971, 32137, 32285, 32412, 32521,
   32609, 32678, 32728, 32757, 32767, 32757, 32728, 32678, 32609, 32521,
   32412, 32285, 32137, 31971, 31785, 31580, 31356, 31113, 30852, 30571,
   30273, 29956, 29621, 29268, 28898, 28510, 28105, 27683, 27245, 26790,
   26319, 25832, 25329, 24811, 24279, 23731, 23170, 22594, 22005, 21403,
   20787, 20159, 19519, 18868, 18204, 17530, 16846, 16151, 15446, 14732,
   14010, 13279, 12539, 11793, 11039, 10278,  9512,  8739,  7962,  7179,
    6393,  5602,  4808,  4011,  3212,  2410,  1608,   804,     0,  -804,
   -1608, -2410, -3212, -4011, -4808, -5602, -6393, -7179, -7962, -8739,
   -9512,-10278,-11039,-11793,-12539,-13279,-14010,-14732,-15446,-16151,
  -16846,-17530,-18204,-18868,-19519,-20159,-20787,-21403,-22005,-22594,
  -23170,-23731,-24279,-24811,-25329,-25832,-26319,-26790,-27245,-27683,
  -28105,-28510,-28898,-29268,-29621,-29956,-30273,-30571,-30852,-31113,
  -31356,-31580,-31785,-31971,-32137,-32285,-32412,-32521,-32609,-32678,
  -32728,-32757,-32767,-32757,-32728,-32678,-32609,-32521,-32412,-32285,
  -32137,-31971,-31785,-31580,-31356,-31113,-30852,-30571,-30273,-29956,
  -29621,-29268,-28898,-28510,-28105,-27683,-27245,-26790,-26319,-25832,
  -25329,-24811,-24279,-23731,-23170,-22594,-22005,-21403,-20787,-20159,
  -19519,-18868,-18204,-17530,-16846,-16151,-15446,-14732,-14010,-13279,
  -12539,-11793,-11039,-10278, -9512, -8739, -7962, -7179, -6393, -5602,
   -4808, -4011, -3212, -2410, -1608,  -804,     0
  }; 

int vol = 50;

#define numOscillators 3 
byte waveShape[numOscillators] = {0,0,0};
float waveFrequency[numOscillators] = {2.0,2.0,2.0};
float waveAmplitude[numOscillators] = {0.0,1.0,1.0};
byte voiceStates[8] = {0,0,0,0,0,0,0};
byte currentFreqs[8] = {0,0,0,0,0,0,0,0};

float LFOFrequency[2] = {0,0};
float LFOFrequencyPrev[2] = {0,0};
float LFOAmplitude[2] = {0,0};
float LFOAmplitudePrev[2] = {0,0};
float modadsr[2][5] = {{0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0}};
bool LFODest[2][4] = {{0,0,0,0},{0,0,0,0}};
bool envDest[2][5] = {{0,0,0,0,0},{0,0,0,0,0}};

int semitonesTune = 12;
int detunePercent = 0;
float detuneFactor = 1;

int filterFreq = 1000;
float filterQ = 1.0;

#define numModOctaves 2

#define envParameters 4 
float adsr[envParameters] = {10.5,35.0,1.0,300};
char adsrNames[envParameters] = {'A','D','S','R'};

/*
 * Setup function. Everything is initialized   
 */
void setup() {  
  Wire.begin();
  leds.begin();
  oled.begin();

  //Fill arb waveform with sinewave
  memcpy(arbWave, sineWave, sizeof sineWave);
  
  // Initialize the Display
  oled.fillScreen(BLACK);
  oled.setTextSize(3);      
  oled.setTextColor(MAGENTA); 
  oled.setCursor(20, 54);     
  oled.println(F("SYNTH"));
  oled.drawRoundRect(15,50,97,30,5,MAGENTA);

  //Give audio library some memory (determined by diagnostic functions)
  AudioMemory(30);

  pinMode(enc1LED, OUTPUT);
  pinMode(enc2LED, OUTPUT);
  pinMode(enc3LED, OUTPUT);
  pinMode(enc4LED, OUTPUT);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.2);

  //Initialize oscillator 1s
  for (byte a = 0; a < 8; a++){
    a_bank[a]->begin(WAVEFORM_SINE);
    a_bank[a]->amplitude(0.75);
    a_bank[a]->frequency(82.41);
    a_bank[a]->frequencyModulation(numModOctaves);
    a_bank[a]->arbitraryWaveform(arbWave,170);
  }

  //Initialize oscillator 2s
  for (byte b = 0; b < 8; b++){
    b_bank[b]->begin(WAVEFORM_SINE);
    b_bank[b]->amplitude(0.75);
    b_bank[b]->frequency(123);
    b_bank[b]->frequencyModulation(numModOctaves);
    b_bank[b]->arbitraryWaveform(arbWave,170);
  }

  //Initialize pink noise
  for (byte n = 0; n < 8; n++){
    noise_bank[n]->amplitude(0.75);
  }

  //Initialize envelopes
  for (byte n = 0; n < 8; n++){
    envelope_bank[n]->noteOff();
  }

  //Initialize filters
  for (byte n = 0; n < 8; n++){
    filter_bank[n]->octaveControl(7);
    filter_bank[n]->frequency(filterFreq);
    filter_bank[n]->resonance(filterQ);
  }

  //Initialize LFO1
  mod_LFO1.frequency(LFOFrequency[0]);
  mod_LFO1.amplitude(LFOAmplitude[0]);
  mod_LFO1.frequencyModulation(numModOctaves);
  mod_LFO1.arbitraryWaveform(arbWave,170);
  mod_LFO1.begin(0.0);

  //Initialize LFO2
  mod_LFO2.frequency(LFOFrequency[1]);
  mod_LFO2.amplitude(LFOAmplitude[1]);
  mod_LFO2.frequencyModulation(numModOctaves);
  mod_LFO2.arbitraryWaveform(arbWave,170);
  mod_LFO2.begin(0.0);

  //Initialize ENV1
  env1_dc.amplitude(1.0);
  mod_env1.attack(0.0);
  mod_env1.decay(0.0);
  mod_env1.sustain(0.0);
  mod_env1.release(0.0);
  mod_env1.noteOff();

  //Initialize ENV1
  env2_dc.amplitude(1.0);
  mod_env2.attack(0.0);
  mod_env2.decay(0.0);
  mod_env2.sustain(0.0);
  mod_env2.release(0.0);
  mod_env2.noteOff();

  //Adjust gain for all mixers so no clipping at max throughput
  for (byte ch = 0; ch < 4; ch++){
    secondary_mixer1.gain(ch,0.25);
    secondary_mixer2.gain(ch,0.25);
    primary_mixer.gain(ch,0.5);
    env1_mixer.gain(ch,0);
    env2_mixer.gain(ch,0);
    LFO1_mixer.gain(ch,0);
    LFO2_mixer.gain(ch,0);
    osc2_pitch_mod_mixer.gain(ch,0);
    osc1_pitch_mod_mixer.gain(ch,0);
    filter_cutoff_mod_mixer.gain(ch,0); 
  }
  env1_mixer.gain(2,1.0);
  env2_mixer.gain(2,1.0);

  //Display a fun animation
  delay(1000);
  oled.drawRoundRect(15,50,97,30,5,BLACK);
  
  oled.drawRoundRect(0,0,127,127,5,MAGENTA);
  oled.setTextColor(RED); 
  oled.setCursor(20, 54);     
  oled.println(F("SYNTH"));
  delay(100);
  
  oled.drawRoundRect(15,15,98,98,5,MAGENTA);
  oled.setTextColor(GREEN); 
  oled.setCursor(20, 54);     
  oled.println(F("SYNTH"));
  delay(100);
  
  oled.drawRoundRect(30,30,68,68,5,MAGENTA);
  oled.setTextColor(BLUE); 
  oled.setCursor(20, 54);     
  oled.println(F("SYNTH"));
  delay(100);
  
  oled.drawRoundRect(45,45,38,38,5,MAGENTA);
  oled.setTextColor(YELLOW); 
  oled.setCursor(20, 54);     
  oled.println(F("SYNTH"));
  delay(100);
  
  oled.drawRoundRect(60,60,8,8,5,MAGENTA);
  oled.setTextColor(WHITE); 
  oled.setCursor(20, 54);     
  oled.println(F("SYNTH"));
  delay(100);
  
  oled.fillScreen(BLACK);

  //Turn off all neopixels to start
  for (int i=0; i < numled; i++) {
    leds.setPixel(i, BLACK);
    leds.setBrightness(5);
    leds.show();
  }
  
}

//Timing Variables
unsigned long last_time_input = millis();
unsigned long last_time_display = millis();
unsigned long last_time_print = millis();

/*
 * Main Loop 
 */
void loop() {
  //Update volume 
  int n = analogRead(15);
  if (n != vol) {
    vol = n;
    sgtl5000_1.volume((float)n / 1023);
  }
  
  //Update every 10ms
  if (millis()-last_time_display > 10){
    menuCheck();  //See if menu needs updating
    staticMenu(); //Refresh display
    last_time_display = millis();
  }

  //Update every 25ms
  if (millis()-last_time_input > 25){
    readInputs(); //Request fresh user input data
    last_time_input = millis();
  }

  //Update as fast as possible
  updateEncoders();//Update encoder counts
  playKeyboard();//Play sounds

//  //Enable for memory and processor  diagnostics
//  if (millis()-last_time_print > 100){
//    Serial.print("all=");
//    Serial.print(AudioProcessorUsage());
//    Serial.print(",");
//    Serial.print(AudioProcessorUsageMax());
//    Serial.print("    ");
//    Serial.print("Memory: ");
//    Serial.print(AudioMemoryUsage());
//    Serial.print(",");
//    Serial.println(AudioMemoryUsageMax());
//    last_time_print = millis();
//  }
}
