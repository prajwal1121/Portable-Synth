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
#include <Si4703_Breakout.h>

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

const int8_t OLED_RESET = -1; 
// Screen dimensions
const byte SCREEN_WIDTH = 128;
const byte SCREEN_HEIGHT = 128;

//Extra pins for SPI
const byte DC_PIN = 40;
const byte CS_PIN = 38;
const byte RST_PIN = 41;

Adafruit_SSD1351 oled = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI1, CS_PIN, DC_PIN, RST_PIN);

// Color definitions
const uint16_t BLACK = 0x0000;
const uint16_t BLUE = 0x001F;
const uint16_t RED = 0xFA20;
const uint16_t GREEN = 0x47E0;
const uint16_t CYAN = 0x07FF;
const uint16_t MAGENTA = 0xF81F;
const uint16_t PURPLE = 0x6011;
const uint16_t YELLOW = 0xFD60;
const uint16_t WHITE = 0xFFFF;
const uint16_t DARKGREY = 0x39C7;
const uint16_t LIGHTGREY = 0x6B6D;
const uint16_t PURERED = 0xF800;
const uint16_t MAROON = 0xBAEB;
const uint16_t DARKGREEN = 0x03A0;
/*Pin configurations and settings for
 * Neopixels
 */
const int numled = 10;
const int pin = 17;

DMAMEM byte drawingMemory[numled*3];         //  3 bytes per LED
DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED

WS2812Serial leds(numled, displayMemory, drawingMemory, pin, WS2812_GRB);

/*Pin configurations and settings for
 * LEDs
 */
const byte enc1LED = 32;
const byte enc2LED = 31;
const byte enc3LED = 30;
const byte enc4LED = 29;

/*Pin configurations SD and Flash
 * Memory
 */
const byte FLASHCHIP_CS_PIN = 6;
const byte SDCARD_MOSI_PIN = 11;  
const byte SDCARD_SCK_PIN = 13;

/*
 * ASDT Output
 */
// GUItool: begin automatically generated code
AudioSynthWaveformDc     env1_dc;        //xy=92.50010299682617,1062.5000228881836
AudioSynthWaveformDc     env2_dc;        //xy=95.50010299682617,1144.5000228881836
AudioMixer4              LFO2_mixer;     //xy=266.5001029968262,956.5000228881836
AudioMixer4              env1_mixer;     //xy=266.5001029968262,1055.5000228881836
AudioMixer4              env2_mixer;     //xy=266.5001029968262,1139.5000228881836
AudioMixer4              LFO1_mixer;     //xy=269.5001029968262,861.5000228881836
AudioSynthWaveformModulated mod_LFO1;       //xy=435.5001029968262,868.5000228881836
AudioSynthWaveformModulated mod_LFO2;       //xy=436.5001029968262,964.5000228881836
AudioEffectEnvelope      mod_env1;       //xy=449.5001029968262,1052.5000228881836
AudioEffectEnvelope      mod_env2;       //xy=452.5001029968262,1139.5000228881836
AudioMixer4              osc2_pitch_mod_mixer; //xy=781.5001029968262,1122.5000228881836
AudioMixer4              osc1_pitch_mod_mixer; //xy=782.5001029968262,899.5000228881836
AudioMixer4              filter_cutoff_mod_mixer; //xy=783.5001029968262,692.5000228881836
AudioSynthWaveformModulated wave2a;         //xy=1031.5001029968262,1035.5000228881836
AudioSynthWaveformModulated wave2b;         //xy=1031.5001029968262,1069.5000228881836
AudioSynthWaveformModulated wave5b;         //xy=1031.5001029968262,1498.5000228881836
AudioSynthWaveformModulated wave1a;         //xy=1034.5001029968262,906.5000228881836
AudioSynthWaveformModulated wave8a;         //xy=1030.5001029968262,1913.5000228881836
AudioSynthWaveformModulated wave3a;         //xy=1033.5001029968262,1173.5000228881836
AudioSynthWaveformModulated wave1b;         //xy=1034.5001029968262,940.5000228881836
AudioSynthWaveformModulated wave8b;         //xy=1030.5001029968262,1947.5000228881836
AudioSynthWaveformModulated wave3b;         //xy=1033.5001029968262,1207.5000228881836
AudioSynthWaveformModulated wave4a;         //xy=1035.5001029968262,1319.5000228881836
AudioSynthWaveformModulated wave4b;         //xy=1035.5001029968262,1353.5000228881836
AudioSynthWaveformModulated wave5a;         //xy=1036.5001029968262,1465.5000228881836
AudioSynthWaveformModulated wave6a;         //xy=1036.5001029968262,1602.5000228881836
AudioSynthWaveformModulated wave6b;         //xy=1036.5001029968262,1636.5000228881836
AudioSynthWaveformModulated wave7a;         //xy=1036.5001029968262,1745.5000228881836
AudioSynthWaveformModulated wave7b;         //xy=1036.5001029968262,1779.5000228881836
AudioSynthNoisePink      noise2;         //xy=1056.5001029968262,1103.5000228881836
AudioSynthNoisePink      noise1;         //xy=1058.5001029968262,974.5000228881836
AudioSynthNoisePink      noise3;         //xy=1059.5001029968262,1241.5000228881836
AudioSynthNoisePink      noise4;         //xy=1060.5001029968262,1387.5000228881836
AudioSynthNoisePink      noise5;         //xy=1061.5001029968262,1532.5000228881836
AudioSynthNoisePink      noise6;         //xy=1067.5001029968262,1669.5000228881836
AudioSynthNoisePink      noise7;         //xy=1067.5001029968262,1812.5000228881836
AudioSynthNoisePink      noise8;         //xy=1072.5001029968262,1980.5000228881836
AudioMixer4              wave1mix;       //xy=1201.5001029968262,956.5000228881836
AudioMixer4              wave2mix;       //xy=1203.5001029968262,1089.5000228881836
AudioMixer4              wave3mix;       //xy=1209.5001029968262,1223.5000228881836
AudioMixer4              wave4mix;       //xy=1212.5001029968262,1371.5000228881836
AudioMixer4              wave5mix;       //xy=1215.5001029968262,1515.5000228881836
AudioMixer4              wave6mix;       //xy=1216.5001029968262,1653.5000228881836
AudioMixer4              wave7mix;       //xy=1221.5001029968262,1797.5000228881836
AudioMixer4              wave8mix;       //xy=1225.5001029968262,1964.5000228881836
AudioEffectEnvelope      synth_envelope_1; //xy=1380.5001029968262,958.5000228881836
AudioEffectEnvelope      synth_envelope_2; //xy=1383.5001029968262,1093.5000228881836
AudioEffectEnvelope      synth_envelope_3; //xy=1389.5001029968262,1227.5000228881836
AudioEffectEnvelope      synth_envelope_4; //xy=1391.5001029968262,1371.5000228881836
AudioEffectEnvelope      synth_envelope_6; //xy=1391.5001029968262,1656.5000228881836
AudioEffectEnvelope      synth_envelope_7; //xy=1395.5001029968262,1804.5000228881836
AudioEffectEnvelope      synth_envelope_8; //xy=1395.5001029968262,1967.5000228881836
AudioEffectEnvelope      synth_envelope_5; //xy=1397.5001029968262,1515.5000228881836
AudioPlaySerialflashRaw  playFlashRaw12; //xy=1402.5001029968262,824.5000228881836
AudioPlaySerialflashRaw  playFlashRaw6;  //xy=1405.5001029968262,617.5000228881836
AudioPlaySerialflashRaw  playFlashRaw11; //xy=1405.5001029968262,791.5000228881836
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=1407.5001029968262,431.5000228881836
AudioPlaySerialflashRaw  playFlashRaw10; //xy=1406.5001029968262,757.5000228881836
AudioPlaySerialflashRaw  playFlashRaw5;  //xy=1408.5001029968262,581.5000228881836
AudioPlaySerialflashRaw  playFlashRaw3;  //xy=1409.5001029968262,508.5000228881836
AudioPlaySerialflashRaw  playFlashRaw7;  //xy=1409.5001029968262,652.5000228881836
AudioPlaySerialflashRaw  playFlashRaw8;  //xy=1409.5001029968262,688.5000228881836
AudioPlaySerialflashRaw  playFlashRaw2;  //xy=1410.5001029968262,471.5000228881836
AudioPlaySerialflashRaw  playFlashRaw4;  //xy=1411.5001029968262,544.5000228881836
AudioPlaySerialflashRaw  playFlashRaw9;  //xy=1411.5001029968262,723.5000228881836
AudioFilterStateVariable filter1;        //xy=1568.5001029968262,961.5000228881836
AudioFilterStateVariable filter2;        //xy=1577.5001029968262,1096.5000228881836
AudioFilterStateVariable filter4;        //xy=1584.5001029968262,1379.5000228881836
AudioFilterStateVariable filter3;        //xy=1585.5001029968262,1232.5000228881836
AudioFilterStateVariable filter5;        //xy=1593.5001029968262,1521.5000228881836
AudioFilterStateVariable filter6;        //xy=1593.5001029968262,1659.5000228881836
AudioFilterStateVariable filter7;        //xy=1602.5001029968262,1806.5000228881836
AudioFilterStateVariable filter8;        //xy=1607.5001029968262,1969.5000228881836
AudioEffectEnvelope      sample_envelope_7; //xy=1617.5001029968262,652.5000228881836
AudioEffectEnvelope      sample_envelope_11; //xy=1618.5001029968262,790.5000228881836
AudioEffectEnvelope      sample_envelope_12; //xy=1618.5001029968262,825.5000228881836
AudioEffectEnvelope      sample_envelope_6; //xy=1619.5001029968262,617.5000228881836
AudioEffectEnvelope      sample_envelope_8; //xy=1619.5001029968262,689.5000228881836
AudioEffectEnvelope      sample_envelope_9; //xy=1619.5001029968262,721.5000228881836
AudioEffectEnvelope      sample_envelope_5; //xy=1621.5001029968262,580.5000228881836
AudioEffectEnvelope      sample_envelope_1; //xy=1622.5001029968262,430.5000228881836
AudioEffectEnvelope      sample_envelope_3; //xy=1622.5001029968262,508.5000228881836
AudioEffectEnvelope      sample_envelope_4; //xy=1622.5001029968262,544.5000228881836
AudioEffectEnvelope      sample_envelope_2; //xy=1623.5001029968262,470.5000228881836
AudioEffectEnvelope      sample_envelope_10; //xy=1622.5001029968262,757.5000228881836
AudioPlaySdWav           playSdWav1;     //xy=1662.5001029968262,262.5000228881836
AudioInputI2S            i2s2;           //xy=1758.5007781982422,1029.8576383590698
AudioMixer4              translator_mixer; //xy=1834.5001029968262,275.5000228881836
AudioMixer4              preview_mixer;  //xy=1834.5001029968262,352.5000228881836
AudioMixer4              sample_secondary_mixer_3; //xy=1866.5001029968262,781.5000228881836
AudioMixer4              sample_secondary_mixer_2; //xy=1868.5001029968262,622.5000228881836
AudioMixer4              synth_secondary_mixer_1; //xy=1869.5001029968262,1353.5000228881836
AudioMixer4              sample_secondary_mixer_1; //xy=1876.5001029968262,487.5000228881836
AudioMixer4              synth_secondary_mixer_2; //xy=1873.5001029968262,1526.5000228881836
AudioPlaySdRaw           playSdRec;     //xy=1911.5005531311035,1164.0003128051758
AudioMixer4              input_mixer;         //xy=1919.500587463379,1042.0002174377441
AudioMixer4              record_mixer;         //xy=1923.500617980957,1110.0003070831299
AudioAnalyzePeak         peak_left;          //xy=1925.5005187988281,928.0001611709595
AudioAnalyzePeak         peak_right;          //xy=1928.5005149841309,964.0001811981201
AudioRecordQueue         queue1; //xy=2023.0006923675537,275.50013732910156
AudioRecordQueue         record_queue;         //xy=2087.50048828125,1110.0002737045288
AudioMixer4              sample_primary_mixer; //xy=2128.500102996826,618.5000228881836
AudioMixer4              synth_primary_mixer; //xy=2141.500102996826,1448.5000228881836
AudioMixer4              output_mixer;   //xy=2322.500102996826,1006.5000228881836
AudioOutputI2S           i2s1; //xy=2515.500102996826,1006.5000228881836
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
AudioConnection          patchCord86(synth_envelope_8, 0, filter8, 0);
AudioConnection          patchCord87(synth_envelope_5, 0, filter5, 0);
AudioConnection          patchCord88(playFlashRaw12, sample_envelope_12);
AudioConnection          patchCord89(playFlashRaw6, sample_envelope_6);
AudioConnection          patchCord90(playFlashRaw11, sample_envelope_11);
AudioConnection          patchCord91(playFlashRaw1, sample_envelope_1);
AudioConnection          patchCord92(playFlashRaw10, sample_envelope_10);
AudioConnection          patchCord93(playFlashRaw5, sample_envelope_5);
AudioConnection          patchCord94(playFlashRaw3, sample_envelope_3);
AudioConnection          patchCord95(playFlashRaw7, sample_envelope_7);
AudioConnection          patchCord96(playFlashRaw8, sample_envelope_8);
AudioConnection          patchCord97(playFlashRaw2, sample_envelope_2);
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
AudioConnection          patchCord124(i2s2, 0, input_mixer, 0);
AudioConnection          patchCord125(i2s2, 0, peak_left, 0);
AudioConnection          patchCord126(i2s2, 0, record_mixer, 0);
AudioConnection          patchCord127(i2s2, 1, input_mixer, 1);
AudioConnection          patchCord128(i2s2, 1, peak_right, 0);
AudioConnection          patchCord129(i2s2, 1, record_mixer, 1);
AudioConnection          patchCord130(translator_mixer, queue1);
AudioConnection          patchCord131(preview_mixer, 0, sample_primary_mixer, 3);
AudioConnection          patchCord132(sample_secondary_mixer_3, 0, sample_primary_mixer, 2);
AudioConnection          patchCord133(sample_secondary_mixer_2, 0, sample_primary_mixer, 1);
AudioConnection          patchCord134(synth_secondary_mixer_1, 0, synth_primary_mixer, 0);
AudioConnection          patchCord135(sample_secondary_mixer_1, 0, sample_primary_mixer, 0);
AudioConnection          patchCord136(synth_secondary_mixer_2, 0, synth_primary_mixer, 1);
AudioConnection          patchCord137(playSdRec, 0, output_mixer, 3);
AudioConnection          patchCord138(input_mixer, 0, output_mixer, 2);
AudioConnection          patchCord139(record_mixer, record_queue);
AudioConnection          patchCord140(sample_primary_mixer, 0, output_mixer, 0);
AudioConnection          patchCord141(synth_primary_mixer, 0, output_mixer, 1);
AudioConnection          patchCord142(output_mixer, 0, i2s1, 0);
AudioConnection          patchCord143(output_mixer, 0, i2s1, 1);
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
const byte numSampleFiles = 12;
const long maxSampleLength = 1200000;
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
const byte numStepsInSequence = 32;
const byte numStepsOnScreen = 16;

/*
 * Synth Stuff
 */
//start off with a sinewave in arbitrary waveform
EXTMEM int16_t arbWave[257];
const int16_t sineWave[257] = {   
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

const byte numOscillators = 3; 
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

const byte numModOctaves = 2;

const byte envParameters = 4; 
float adsr[envParameters] = {10.5,35.0,1.0,300};

/*
 *Radio Module Config 
 */
#define radioReset  14
#define radioSdio  18
#define radioSclk  19
Si4703_Breakout radio(radioReset, radioSdio, radioSclk);
int radioChannel = 987;

/*
 *Recorder Stuff 
 */
float inputGain = 0.0;

EXTMEM char recNameBuff[15];
EXTMEM char previewNameBuff[15];
EXTMEM char entryNameBuff[15];
int numRecFiles = 0;
byte recordStatus = 0;

File recFile;

bool draw = 1;
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
  currentDirectory.close();
  
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
   *Record Setup 
   */
   //Radio setup
  radio.powerOn();
  radio.setVolume(0);
  radio.setChannel(radioChannel);
  
  input_mixer.gain(0,inputGain);
  input_mixer.gain(1,inputGain);
  record_mixer.gain(0,0.25);
  record_mixer.gain(1,0.25);
  
  if (!SD.exists("/Recs")){
    SD.mkdir("/Recs");
  }
  
  //See what's in our root Recordings directory
  currentDirectory = SD.open("/Recs");
  while(true) {
     File entry =  currentDirectory.openNextFile();
     if (!entry) {
       currentDirectory.rewindDirectory();
       break;
     }
     else{
       numRecFiles = numRecFiles+1;
     }
     delay(1);
     entry.close();
     delay(1);
   }
   sprintf(recNameBuff,"/Recs/R%d.RAW",numRecFiles);
   currentDirectory.close();
  /*
   * Audio Output Setup   
   */
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
    case 4://Recorder
      menuCheckRecorder();  //See if menu needs updating
      //Update every 10ms
      if (millis()-last_time_display > 10){
        staticMenuRecorder(); //Refresh display
        last_time_display = millis();
      }
    break;
  }
      
  //Update every 25ms
  if (millis()-last_time_input > 25){
    readInputs(); //Request fresh user input data
    last_time_input = millis();
    switcher();
    if (function==4 and !recordStatus==1)showRMS();
  }

  //Update as fast as possible
  updateEncoders();
  playKeyboard();
  recordAndPlayback();
  
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
}
