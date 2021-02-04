 //
// Combined Sequencer/Synthesizer/Sampler
// Written by Prajwal Tumkur Mahesh
//
#define USE_SdFat_ 

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <WS2812Serial.h>

#ifdef USE_SdFat_
  #include <SdFat.h>
  SdFat SD; 
#else
  #include <SD.h>
#endif

/*Pin configurations and settings for
 * SSD1351 Color OLED Display
 */
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>

PROGMEM const int8_t OLED_RESET = -1; 
// Screen dimensions
PROGMEM const byte SCREEN_WIDTH = 128;
PROGMEM const byte SCREEN_HEIGHT = 128;

//Extra pins for SPI
PROGMEM const byte DC_PIN = 40;
PROGMEM const byte CS_PIN = 38;
PROGMEM const byte RST_PIN = 41;

Adafruit_SSD1351 oled = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI1, CS_PIN, DC_PIN, RST_PIN);

// Color definitions
PROGMEM const uint16_t BLACK = 0x0000;
PROGMEM const uint16_t BLUE = 0x001F;
PROGMEM const uint16_t RED = 0xFA20;
PROGMEM const uint16_t GREEN = 0x47E0;
PROGMEM const uint16_t CYAN = 0x07FF;
PROGMEM const uint16_t MAGENTA = 0xF81F;
PROGMEM const uint16_t PURPLE = 0x6011;
PROGMEM const uint16_t YELLOW = 0xFD60;
PROGMEM const uint16_t WHITE = 0xFFFF;
PROGMEM const uint16_t DARKGREY = 0x39C7;
PROGMEM const uint16_t LIGHTGREY = 0x6B6D;

/*Pin configurations and settings for
 * Neopixels
 */
const int numled = 10;
const int pin = 17;

DMAMEM byte drawingMemory[numled*3];  //  3 bytes per LED
DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED

WS2812Serial leds(numled, displayMemory, drawingMemory, pin, WS2812_GRB);

/*Pin configurations and settings for
 * LEDs
 */
PROGMEM const byte enc1LED = 32;
PROGMEM const byte enc2LED = 31;
PROGMEM const byte enc3LED = 30;
PROGMEM const byte enc4LED = 29;

/*Pin configurations SD and Flash
 * Memory
 */
PROGMEM const byte FLASHCHIP_CS_PIN = 6;
PROGMEM const byte SDCARD_MOSI_PIN = 11;  
PROGMEM const byte SDCARD_SCK_PIN = 13;

/*
 * ASDT Output
 */
// GUItool: begin automatically generated code
AudioSynthWaveformDc     env1_dc;        //xy=56.5,1863.6734619140625
AudioSynthWaveformDc     env2_dc;        //xy=59.5,1945.6734619140625
AudioMixer4              LFO2_mixer;     //xy=230.5,1757.6734619140625
AudioMixer4              env1_mixer;     //xy=230.5,1856.6734619140625
AudioMixer4              env2_mixer;     //xy=230.5,1940.6734619140625
AudioMixer4              LFO1_mixer;     //xy=233.5,1662.6734619140625
AudioSynthWaveformModulated mod_LFO1;       //xy=399.5,1669.6734619140625
AudioSynthWaveformModulated mod_LFO2;       //xy=400.5,1765.6734619140625
AudioEffectEnvelope      mod_env1;       //xy=413.5,1853.6734619140625
AudioEffectEnvelope      mod_env2;       //xy=416.5,1940.6734619140625
AudioMixer4              osc2_pitch_mod_mixer; //xy=745.5,1923.6734619140625
AudioMixer4              osc1_pitch_mod_mixer; //xy=746.5,1700.6734619140625
AudioMixer4              filter_cutoff_mod_mixer; //xy=747.5,1493.6734619140625
AudioSynthWaveformModulated wave2a;         //xy=995.5,1836.6734619140625
AudioSynthWaveformModulated wave2b;         //xy=995.5,1870.6734619140625
AudioSynthWaveformModulated wave5b;         //xy=995.5,2299.6734619140625
AudioSynthWaveformModulated wave1a;         //xy=998.5,1707.6734619140625
AudioSynthWaveformModulated wave8a;         //xy=994.5,2714.6734619140625
AudioSynthWaveformModulated wave3a;         //xy=997.5,1974.6734619140625
AudioSynthWaveformModulated wave1b;         //xy=998.5,1741.6734619140625
AudioSynthWaveformModulated wave8b;         //xy=994.5,2748.6734619140625
AudioSynthWaveformModulated wave3b;         //xy=997.5,2008.6734619140625
AudioSynthWaveformModulated wave4a;         //xy=999.5,2120.6734619140625
AudioSynthWaveformModulated wave4b;         //xy=999.5,2154.6734619140625
AudioSynthWaveformModulated wave5a;         //xy=1000.5,2266.6734619140625
AudioSynthWaveformModulated wave6a;         //xy=1000.5,2403.6734619140625
AudioSynthWaveformModulated wave6b;         //xy=1000.5,2437.6734619140625
AudioSynthWaveformModulated wave7a;         //xy=1000.5,2546.6734619140625
AudioSynthWaveformModulated wave7b;         //xy=1000.5,2580.6734619140625
AudioSynthNoisePink      noise2;         //xy=1020.5,1904.6734619140625
AudioSynthNoisePink      noise1;         //xy=1022.5,1775.6734619140625
AudioSynthNoisePink      noise3;         //xy=1023.5,2042.6734619140625
AudioSynthNoisePink      noise4;         //xy=1024.5,2188.6734619140625
AudioSynthNoisePink      noise5;         //xy=1025.5,2333.6734619140625
AudioSynthNoisePink      noise6;         //xy=1031.5,2470.6734619140625
AudioSynthNoisePink      noise7;         //xy=1031.5,2613.6734619140625
AudioSynthNoisePink      noise8;         //xy=1036.5,2781.6734619140625
AudioMixer4              wave1mix;       //xy=1165.5,1757.6734619140625
AudioMixer4              wave2mix;       //xy=1167.5,1890.6734619140625
AudioMixer4              wave3mix;       //xy=1173.5,2024.6734619140625
AudioMixer4              wave4mix;       //xy=1176.5,2172.6734619140625
AudioMixer4              wave5mix;       //xy=1179.5,2316.6734619140625
AudioMixer4              wave6mix;       //xy=1180.5,2454.6734619140625
AudioMixer4              wave7mix;       //xy=1185.5,2598.6734619140625
AudioMixer4              wave8mix;       //xy=1189.5,2765.6734619140625
AudioEffectEnvelope      synth_envelope_1; //xy=1344.500373840332,1759.173496246338
AudioEffectEnvelope      synth_envelope_2;      //xy=1347.5000915527344,1894.1735038757324
AudioEffectEnvelope      synth_envelope_3;      //xy=1353.5000915527344,2028.173511505127
AudioEffectEnvelope      synth_envelope_4;      //xy=1355.5000915527344,2172.673538208008
AudioEffectEnvelope      synth_envelope_6;      //xy=1355.0000915527344,2457.1735553741455
AudioEffectEnvelope      synth_envelope_7;      //xy=1359.0000915527344,2605.6735649108887
AudioEffectEnvelope      synth_envelope_5;      //xy=1361.0000915527344,2316.6735467910767
AudioEffectEnvelope      synth_envelope_8;      //xy=1359.5000915527344,2768.1735734939575
AudioPlaySerialflashRaw  playFlashRaw12; //xy=1366.5718078613281,1625.4288016110659
AudioPlaySerialflashRaw  playFlashRaw6; //xy=1369.1432189941406,1418.0002127438784
AudioPlaySerialflashRaw  playFlashRaw11; //xy=1369.57177734375,1592.4290457516909
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=1371.1431579589844,1232.1435232907534
AudioPlaySerialflashRaw  playFlashRaw10; //xy=1370.2861022949219,1558.5716238766909
AudioPlaySerialflashRaw  playFlashRaw5; //xy=1372.1431884765625,1382.0004568845034
AudioPlaySerialflashRaw  playFlashRaw3; //xy=1373.1431884765625,1309.2862234860659
AudioPlaySerialflashRaw  playFlashRaw2;  //xy=1374.1431884765625,1272.1432791501284
AudioPlaySerialflashRaw  playFlashRaw7; //xy=1373.7146301269531,1453.2862234860659
AudioPlaySerialflashRaw  playFlashRaw8; //xy=1373.7146606445312,1489.2859793454409
AudioPlaySerialflashRaw  playFlashRaw4; //xy=1375.1432189941406,1345.2859793454409
AudioPlaySerialflashRaw  playFlashRaw9; //xy=1375.2860717773438,1524.5718680173159
AudioFilterStateVariable filter1;        //xy=1532.5001182556152,1762.6735363006592
AudioFilterStateVariable filter2;        //xy=1541.5001182556152,1897.6735363006592
AudioFilterStateVariable filter4;        //xy=1548.5001182556152,2180.673536300659
AudioFilterStateVariable filter3;        //xy=1549.5001182556152,2033.6735363006592
AudioFilterStateVariable filter5;        //xy=1557.5001182556152,2322.673536300659
AudioFilterStateVariable filter6;        //xy=1557.5001182556152,2460.673536300659
AudioFilterStateVariable filter7;        //xy=1566.5001182556152,2607.673536300659
AudioFilterStateVariable filter8;        //xy=1571.5001182556152,2770.673536300659
AudioEffectEnvelope      sample_envelope_7; //xy=1581.0002670288086,1453.0003939419985
AudioEffectEnvelope      sample_envelope_11; //xy=1582.0002670288086,1591.0003939419985
AudioEffectEnvelope      sample_envelope_12; //xy=1582.0002670288086,1626.0003939419985
AudioEffectEnvelope      sample_envelope_6; //xy=1583.0002670288086,1418.0003939419985
AudioEffectEnvelope      sample_envelope_8; //xy=1583.0002670288086,1490.0003939419985
AudioEffectEnvelope      sample_envelope_9; //xy=1583.0002670288086,1522.0003939419985
AudioEffectEnvelope      sample_envelope_5; //xy=1585.0002670288086,1381.0003939419985
AudioEffectEnvelope      sample_envelope_1;      //xy=1586.0002670288086,1231.0003939419985
AudioEffectEnvelope      sample_envelope_3; //xy=1586.0002670288086,1309.0003939419985
AudioEffectEnvelope      sample_envelope_4; //xy=1586.0002670288086,1345.0003939419985
AudioEffectEnvelope      sample_envelope_2; //xy=1587.0002670288086,1271.0003939419985
AudioEffectEnvelope      sample_envelope_10; //xy=1586.0002670288086,1558.0003939419985
AudioPlaySdWav           playSdWav1;     //xy=1626.7145652770996,1063.9288215637207
AudioMixer4              translator_mixer; //xy=1798.1431732177734,1076.7860679626465
AudioMixer4              preview_mixer; //xy=1798.7145385742188,1153.500244140625
AudioMixer4              sample_secondary_mixer_3; //xy=1830.7145538330078,1582.5003108978271
AudioMixer4              sample_secondary_mixer_2; //xy=1832.143081665039,1423.9288311004639
AudioMixer4              synth_secondary_mixer_1; //xy=1833.5001182556152,2154.673536300659
AudioMixer4              sample_secondary_mixer_1;         //xy=1840.714485168457,1288.2144966125488
AudioMixer4              synth_secondary_mixer_2; //xy=1837.5001182556152,2327.673536300659
AudioRecordQueue         queue1;         //xy=1959.4288597106934,1076.7861347198486
AudioMixer4              sample_primary_mixer; //xy=2092.7859420776367,1419.2858963012695
AudioMixer4              synth_primary_mixer;  //xy=2105.5001525878906,2249.173542022705
AudioMixer4              output_mixer;         //xy=2286.071434020996,1807.8570232391357
AudioOutputI2S           i2s1;           //xy=2479.6431770324707,1807.214464187622
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
AudioConnection          patchCord72(wave1mix, synth_envelope_1);
AudioConnection          patchCord73(wave2mix, synth_envelope_2);
AudioConnection          patchCord74(wave3mix, synth_envelope_3);
AudioConnection          patchCord75(wave4mix, synth_envelope_4);
AudioConnection          patchCord76(wave5mix, synth_envelope_5);
AudioConnection          patchCord77(wave6mix, synth_envelope_6);
AudioConnection          patchCord78(wave7mix, synth_envelope_7);
AudioConnection          patchCord79(wave8mix, synth_envelope_8);
AudioConnection          patchCord80(synth_envelope_1, 0, filter1, 0);
AudioConnection          patchCord81(synth_envelope_2, 0, filter2, 0);
AudioConnection          patchCord82(synth_envelope_3, 0, filter3, 0);
AudioConnection          patchCord83(synth_envelope_4, 0, filter4, 0);
AudioConnection          patchCord84(synth_envelope_6, 0, filter6, 0);
AudioConnection          patchCord85(synth_envelope_7, 0, filter7, 0);
AudioConnection          patchCord86(synth_envelope_5, 0, filter5, 0);
AudioConnection          patchCord87(synth_envelope_8, 0, filter8, 0);
AudioConnection          patchCord88(playFlashRaw12, sample_envelope_12);
AudioConnection          patchCord89(playFlashRaw6, sample_envelope_6);
AudioConnection          patchCord90(playFlashRaw11, sample_envelope_11);
AudioConnection          patchCord91(playFlashRaw1, sample_envelope_1);
AudioConnection          patchCord92(playFlashRaw10, sample_envelope_10);
AudioConnection          patchCord93(playFlashRaw5, sample_envelope_5);
AudioConnection          patchCord94(playFlashRaw3, sample_envelope_3);
AudioConnection          patchCord95(playFlashRaw2, sample_envelope_2);
AudioConnection          patchCord96(playFlashRaw7, sample_envelope_7);
AudioConnection          patchCord97(playFlashRaw8, sample_envelope_8);
AudioConnection          patchCord98(playFlashRaw4, sample_envelope_4);
AudioConnection          patchCord99(playFlashRaw9, sample_envelope_9);
AudioConnection          patchCord100(filter1, 0, synth_secondary_mixer_1, 0);
AudioConnection          patchCord101(filter2, 0, synth_secondary_mixer_1, 1);
AudioConnection          patchCord102(filter4, 0, synth_secondary_mixer_1, 3);
AudioConnection          patchCord103(filter3, 0, synth_secondary_mixer_1, 2);
AudioConnection          patchCord104(filter5, 0, synth_secondary_mixer_2, 0);
AudioConnection          patchCord105(filter6, 0, synth_secondary_mixer_2, 1);
AudioConnection          patchCord106(filter7, 0, synth_secondary_mixer_2, 2);
AudioConnection          patchCord107(filter8, 0, synth_secondary_mixer_2, 3);
AudioConnection          patchCord108(sample_envelope_7, 0, sample_secondary_mixer_2, 2);
AudioConnection          patchCord109(sample_envelope_11, 0, sample_secondary_mixer_3, 2);
AudioConnection          patchCord110(sample_envelope_12, 0, sample_secondary_mixer_3, 3);
AudioConnection          patchCord111(sample_envelope_6, 0, sample_secondary_mixer_2, 1);
AudioConnection          patchCord112(sample_envelope_8, 0, sample_secondary_mixer_2, 3);
AudioConnection          patchCord113(sample_envelope_9, 0, sample_secondary_mixer_3, 0);
AudioConnection          patchCord114(sample_envelope_5, 0, sample_secondary_mixer_2, 0);
AudioConnection          patchCord115(sample_envelope_1, 0, sample_secondary_mixer_1, 0);
AudioConnection          patchCord116(sample_envelope_3, 0, sample_secondary_mixer_1, 2);
AudioConnection          patchCord117(sample_envelope_4, 0, sample_secondary_mixer_1, 3);
AudioConnection          patchCord118(sample_envelope_2, 0, sample_secondary_mixer_1, 1);
AudioConnection          patchCord119(sample_envelope_10, 0, sample_secondary_mixer_3, 1);
AudioConnection          patchCord120(playSdWav1, 0, translator_mixer, 0);
AudioConnection          patchCord121(playSdWav1, 0, preview_mixer, 0);
AudioConnection          patchCord122(playSdWav1, 1, translator_mixer, 1);
AudioConnection          patchCord123(playSdWav1, 1, preview_mixer, 1);
AudioConnection          patchCord124(translator_mixer, queue1);
AudioConnection          patchCord125(preview_mixer, 0, sample_primary_mixer, 3);
AudioConnection          patchCord126(sample_secondary_mixer_3, 0, sample_primary_mixer, 2);
AudioConnection          patchCord127(sample_secondary_mixer_2, 0, sample_primary_mixer, 1);
AudioConnection          patchCord128(synth_secondary_mixer_1, 0, synth_primary_mixer, 0);
AudioConnection          patchCord129(sample_secondary_mixer_1, 0, sample_primary_mixer, 0);
AudioConnection          patchCord130(synth_secondary_mixer_2, 0, synth_primary_mixer, 1);
AudioConnection          patchCord131(sample_primary_mixer, 0, output_mixer, 0);
AudioConnection          patchCord132(synth_primary_mixer, 0, output_mixer, 1);
AudioConnection          patchCord133(output_mixer, 0, i2s1, 0);
AudioConnection          patchCord134(output_mixer, 0, i2s1, 1);
AudioControlSGTL5000     codec;     //xy=2489.857521057129,1740.7860898971558
// GUItool: end automatically generated code

//Pointer arrays for sampler parameters
AudioEffectEnvelope *sample_envelope_bank[12] = {&sample_envelope_1,&sample_envelope_2,&sample_envelope_3,&sample_envelope_4,&sample_envelope_5,&sample_envelope_6,&sample_envelope_7,&sample_envelope_8,&sample_envelope_9,&sample_envelope_10,&sample_envelope_11,&sample_envelope_12};
AudioPlaySerialflashRaw *flash_players[12] = {&playFlashRaw1,&playFlashRaw2,&playFlashRaw3,&playFlashRaw4,&playFlashRaw5,&playFlashRaw6,&playFlashRaw7,&playFlashRaw8,&playFlashRaw9,&playFlashRaw10,&playFlashRaw11,&playFlashRaw12};

//Pointer arrays for synth parameters
AudioSynthWaveformModulated *a_bank[8] = {&wave1a,&wave2a,&wave3a,&wave4a,&wave5a,&wave6a,&wave7a,&wave8a};
AudioSynthWaveformModulated *b_bank[8] = {&wave1b,&wave2b,&wave3b,&wave4b,&wave5b,&wave6b,&wave7b,&wave8b};
AudioSynthNoisePink *noise_bank[8] = {&noise1,&noise2,&noise3,&noise4,&noise5,&noise6,&noise7,&noise8};
AudioEffectEnvelope *synth_envelope_bank[8] = {&synth_envelope_1,&synth_envelope_2,&synth_envelope_3,&synth_envelope_4,&synth_envelope_5,&synth_envelope_6,&synth_envelope_7,&synth_envelope_8};
AudioFilterStateVariable *filter_bank[8] = {&filter1,&filter2,&filter3,&filter4,&filter5,&filter6,&filter7,&filter8};

/*
 * Navigation Globals
 */
byte screen = 0;
byte screenPrev = 0;
byte function = 0;

/*
 * Sampler Stuff
 */
PROGMEM const byte numSampleFiles = 12;
PROGMEM const long maxSampleLength = 1200000;
struct samples {
  char fileName[20];
};
EXTMEM samples samps[numSampleFiles];

File currentDirectory;
EXTMEM char fileNameBuff[80];
EXTMEM char newfileNameBuff[80];
EXTMEM char previewfileNameBuff[80];
EXTMEM char rootSampleDir[25];
int numItems = 0;
bool directoryDisplayed = 0;

float sampleadsr[12][5];
char adsrNames[4] = {'A','D','S','R'};

//Sequencer Stuff
EXTMEM bool stepSequence[32][12];
EXTMEM bool stepSynth[32][24];
EXTMEM byte sampleIsPlaying[12];
EXTMEM byte assigningNotPlaying[12];
float bpm = 120;
float bpmPrev = bpm;
PROGMEM const byte numStepsInSequence = 32;
PROGMEM const byte numStepsOnScreen = 16;

/*
 * Synth Stuff
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

PROGMEM const byte numOscillators = 3; 
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

PROGMEM const byte numModOctaves = 2;

PROGMEM const byte envParameters = 4; 
float adsr[envParameters] = {10.5,35.0,1.0,300};

/*
 * Output Stuff
 */
float outputVolume[2] = {1.0,0.2};//{sampler,synth}

/*
 * A thing for volume
 */
int vol = 50;

/*
 * Setup function. Everything is initialized   
 */
void setup() {
  Wire.begin();
  leds.begin();
  oled.begin();
  
  // Initialize the Codec  
  codec.enable();
  codec.inputSelect(AUDIO_INPUT_MIC);
  codec.dacVolumeRamp();
  codec.lineOutLevel(13);
  codec.volume(0.45);
  
  // Initialize the SD card
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  SD.begin(SdioConfig(FIFO_SDIO));
  SerialFlash.begin(FLASHCHIP_CS_PIN);
  
  // Initialize the Display
  oled.fillScreen(BLACK);
  oled.setTextSize(3);
  oled.setTextColor(MAGENTA); 
  oled.setCursor(20, 54);     
  oled.println(F("SYNTH"));
  oled.drawRoundRect(15,50,97,30,5,MAGENTA);

  //Give Audio Library a lot of memory to work with
  AudioMemory(24);

  pinMode(enc1LED, OUTPUT);
  pinMode(enc2LED, OUTPUT);
  pinMode(enc3LED, OUTPUT);
  pinMode(enc4LED, OUTPUT);
  
  //Initialize LEDs
  leds.begin();
  leds.setBrightness(5);
  
  //Turn off all neopixels to start
  for (int i=0; i < numled; i++) {
    leds.setPixel(i, BLACK);
    leds.setBrightness(5);
    leds.show();
  }

  /*
   * Synth Setup   
   */
  //Fill arb waveform with sinewave
  memcpy(arbWave, sineWave, sizeof sineWave);

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
    noise_bank[n]->amplitude(0.0);
  }

  //Initialize envelopes
  for (byte n = 0; n < 8; n++){
    synth_envelope_bank[n]->noteOff();
  }

  //Initialize filters
  for (byte n = 0; n < 8; n++){
    filter_bank[n]->octaveControl(7);
    filter_bank[n]->frequency(filterFreq);
    filter_bank[n]->resonance(filterQ);
  }

  //Adjust gain for all mixers so no clipping at max throughput
  for (byte ch = 0; ch < 4; ch++){
    synth_secondary_mixer_1.gain(ch,0.25);
    synth_secondary_mixer_2.gain(ch,0.25);
    synth_primary_mixer.gain(ch,0.5);
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
  
  /*
   * Sampler Setup   
   */
  //Initialize Sample File Names
  for (int i = 0; i < numSampleFiles; i++){
    sprintf(samps[i].fileName, "S%d.RAW", i+1);
    if (!SerialFlash.exists(samps[i].fileName)){
      SerialFlash.createErasable(samps[i].fileName, maxSampleLength);
    }
  }
  
  //See what's in our root Sample directory
  sprintf(fileNameBuff, "/Samples");
  sprintf(rootSampleDir, "/Samples");
  currentDirectory = SD.open(fileNameBuff);
  while(true) {
     File entry =  currentDirectory.openNextFile();
     if (!entry) {
       currentDirectory.rewindDirectory();
       break;
     }
     else{
       numItems = numItems+1;
     }
     delay(1);
     entry.close();
     delay(1);
   }
  
  //Initialize envelopes and samplers
  for (byte n = 0; n < 12; n++){
    sample_envelope_bank[n]->noteOff();
    flash_players[n]->stop();
  }

  //Adjust gain for all mixers so no clipping at max throughput
  for (byte ch = 0; ch < 4; ch++){
    sample_secondary_mixer_1.gain(ch,0.25);
    sample_secondary_mixer_2.gain(ch,0.25);
    sample_secondary_mixer_3.gain(ch,0.25);
    sample_primary_mixer.gain(ch,0.33);
    translator_mixer.gain(ch,0.5);
    preview_mixer.gain(ch,0.25);
  }

  for (byte e = 0; e < 12; e++){
    sampleadsr[e][0] = 10.5;
    sample_envelope_bank[e]->attack(10.5);
    sampleadsr[e][1] = 35;
    sample_envelope_bank[e]->decay(35);
    sampleadsr[e][2] = 1.0;
    sample_envelope_bank[e]->sustain(1.0);
    sampleadsr[e][3] = 300;
    sample_envelope_bank[e]->release(300);
    sampleadsr[e][4] = 0.25;
  }

  /*
   * Sequencer Setup   
   */
  for (byte n = 0; n < numStepsInSequence; n++){
    for (byte e = 0; e < 12; e++){
      stepSequence[n][e] = 0;
    }
    for (byte e = 0; e < 24; e++){
      stepSynth[n][e] = 0;
    }
  }
  for (byte n = 0; n < 12; n++){
    sampleIsPlaying[n] = 255;
    assigningNotPlaying[n] = 255;
  }
  /*
   * Audio Output Setup   
   */
//  output_mixer.gain(0,outputVolume[0]);
//  output_mixer.gain(1,outputVolume[1]);
  output_mixer.gain(0,outputVolume[0]);
  output_mixer.gain(1,outputVolume[1]);
  AudioInterrupts();
  
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
}

//Timing Variables
unsigned long last_time_input = millis();
unsigned long last_time_display = millis();
unsigned long last_time_print = millis();

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
      menuCheckSynth();  //See if menu needs updating
      if (millis()-last_time_display > 10){
        staticMenuSynth(); //Refresh display
        last_time_display = millis();
      }
    break;
    case 1://Sampler
      menuCheckSampler();  //See if menu needs updating
      //Update every 10ms
      if (millis()-last_time_display > 10){
        staticMenuSampler(); //Refresh display
        last_time_display = millis();
      }
    break;
    case 2://Sequencer
      menuCheckSequencer();  //See if menu needs updating
      //Update every 10ms
      if (millis()-last_time_display > 10){
        staticMenuSequencer(); //Refresh display
        last_time_display = millis();
      }
    break;
    case 3://Mixer
      menuCheckMixer();  //See if menu needs updating
      //Update every 10ms
      if (millis()-last_time_display > 10){
        staticMenuMixer(); //Refresh display
        last_time_display = millis();
      }
    break;
  }
      
  //Update every 25ms
  if (millis()-last_time_input > 25){
    readInputs(); //Request fresh user input data
    last_time_input = millis();
    switcher();
  }

  //Update as fast as possible
  updateEncoders();
  playKeyboard();
  
//  //Enable for memory and processor  diagnostics
//  if (millis()-last_time_print > 100){
//    Serial.print(F("all="));
//    Serial.print(AudioProcessorUsage());
//    Serial.print(F(","));
//    Serial.print(AudioProcessorUsageMax());
//    Serial.print(F("    "));
//    Serial.print(F("Memory: "));
//    Serial.print(AudioMemoryUsage());
//    Serial.print(F(","));
//    Serial.println(AudioMemoryUsageMax());
//    last_time_print = millis();
//  }
}
