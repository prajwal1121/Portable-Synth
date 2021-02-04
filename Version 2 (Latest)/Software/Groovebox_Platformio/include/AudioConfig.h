#ifndef AUDIO_CONFIG_H
#define AUDIO_CONFIG_H

#include <Arduino.h>
#include <Audio.h>

 /*
 * ASDT Output
 */
#pragma region
// GUItool: begin automatically generated code
extern AudioSynthWaveformDc     env1_dc;        //xy=92.50010299682617,1062.5000228881836
extern AudioSynthWaveformDc     env2_dc;        //xy=95.50010299682617,1144.5000228881836
extern AudioMixer4              LFO2_mixer;     //xy=266.5001029968262,956.5000228881836
extern AudioMixer4              env1_mixer;     //xy=266.5001029968262,1055.5000228881836
extern AudioMixer4              env2_mixer;     //xy=266.5001029968262,1139.5000228881836
extern AudioMixer4              LFO1_mixer;     //xy=269.5001029968262,861.5000228881836
extern AudioSynthWaveformModulated mod_LFO1;       //xy=435.5001029968262,868.5000228881836
extern AudioSynthWaveformModulated mod_LFO2;       //xy=436.5001029968262,964.5000228881836
extern AudioEffectEnvelope      mod_env1;       //xy=449.5001029968262,1052.5000228881836
extern AudioEffectEnvelope      mod_env2;       //xy=452.5001029968262,1139.5000228881836
extern AudioMixer4              osc2_pitch_mod_mixer; //xy=781.5001029968262,1122.5000228881836
extern AudioMixer4              osc1_pitch_mod_mixer; //xy=782.5001029968262,899.5000228881836
extern AudioMixer4              filter_cutoff_mod_mixer; //xy=783.5001029968262,692.5000228881836
extern AudioSynthWaveformModulated wave2a;         //xy=1031.5001029968262,1035.5000228881836
extern AudioSynthWaveformModulated wave2b;         //xy=1031.5001029968262,1069.5000228881836
extern AudioSynthWaveformModulated wave5b;         //xy=1031.5001029968262,1498.5000228881836
extern AudioSynthWaveformModulated wave1a;         //xy=1034.5001029968262,906.5000228881836
extern AudioSynthWaveformModulated wave8a;         //xy=1030.5001029968262,1913.5000228881836
extern AudioSynthWaveformModulated wave3a;         //xy=1033.5001029968262,1173.5000228881836
extern AudioSynthWaveformModulated wave1b;         //xy=1034.5001029968262,940.5000228881836
extern AudioSynthWaveformModulated wave8b;         //xy=1030.5001029968262,1947.5000228881836
extern AudioSynthWaveformModulated wave3b;         //xy=1033.5001029968262,1207.5000228881836
extern AudioSynthWaveformModulated wave4a;         //xy=1035.5001029968262,1319.5000228881836
extern AudioSynthWaveformModulated wave4b;         //xy=1035.5001029968262,1353.5000228881836
extern AudioSynthWaveformModulated wave5a;         //xy=1036.5001029968262,1465.5000228881836
extern AudioSynthWaveformModulated wave6a;         //xy=1036.5001029968262,1602.5000228881836
extern AudioSynthWaveformModulated wave6b;         //xy=1036.5001029968262,1636.5000228881836
extern AudioSynthWaveformModulated wave7a;         //xy=1036.5001029968262,1745.5000228881836
extern AudioSynthWaveformModulated wave7b;         //xy=1036.5001029968262,1779.5000228881836
extern AudioSynthNoisePink      noise2;         //xy=1056.5001029968262,1103.5000228881836
extern AudioSynthNoisePink      noise1;         //xy=1058.5001029968262,974.5000228881836
extern AudioSynthNoisePink      noise3;         //xy=1059.5001029968262,1241.5000228881836
extern AudioSynthNoisePink      noise4;         //xy=1060.5001029968262,1387.5000228881836
extern AudioSynthNoisePink      noise5;         //xy=1061.5001029968262,1532.5000228881836
extern AudioSynthNoisePink      noise6;         //xy=1067.5001029968262,1669.5000228881836
extern AudioSynthNoisePink      noise7;         //xy=1067.5001029968262,1812.5000228881836
extern AudioSynthNoisePink      noise8;         //xy=1072.5001029968262,1980.5000228881836
extern AudioMixer4              wave1mix;       //xy=1201.5001029968262,956.5000228881836
extern AudioMixer4              wave2mix;       //xy=1203.5001029968262,1089.5000228881836
extern AudioMixer4              wave3mix;       //xy=1209.5001029968262,1223.5000228881836
extern AudioMixer4              wave4mix;       //xy=1212.5001029968262,1371.5000228881836
extern AudioMixer4              wave5mix;       //xy=1215.5001029968262,1515.5000228881836
extern AudioMixer4              wave6mix;       //xy=1216.5001029968262,1653.5000228881836
extern AudioMixer4              wave7mix;       //xy=1221.5001029968262,1797.5000228881836
extern AudioMixer4              wave8mix;       //xy=1225.5001029968262,1964.5000228881836
extern AudioEffectEnvelope      synth_envelope_1; //xy=1380.5001029968262,958.5000228881836
extern AudioEffectEnvelope      synth_envelope_2; //xy=1383.5001029968262,1093.5000228881836
extern AudioEffectEnvelope      synth_envelope_3; //xy=1389.5001029968262,1227.5000228881836
extern AudioEffectEnvelope      synth_envelope_4; //xy=1391.5001029968262,1371.5000228881836
extern AudioEffectEnvelope      synth_envelope_6; //xy=1391.5001029968262,1656.5000228881836
extern AudioEffectEnvelope      synth_envelope_7; //xy=1395.5001029968262,1804.5000228881836
extern AudioEffectEnvelope      synth_envelope_8; //xy=1395.5001029968262,1967.5000228881836
extern AudioEffectEnvelope      synth_envelope_5; //xy=1397.5001029968262,1515.5000228881836
extern AudioPlaySerialflashRaw  playFlashRaw12; //xy=1402.5001029968262,824.5000228881836
extern AudioPlaySerialflashRaw  playFlashRaw6;  //xy=1405.5001029968262,617.5000228881836
extern AudioPlaySerialflashRaw  playFlashRaw11; //xy=1405.5001029968262,791.5000228881836
extern AudioPlaySerialflashRaw  playFlashRaw1;  //xy=1407.5001029968262,431.5000228881836
extern AudioPlaySerialflashRaw  playFlashRaw10; //xy=1406.5001029968262,757.5000228881836
extern AudioPlaySerialflashRaw  playFlashRaw5;  //xy=1408.5001029968262,581.5000228881836
extern AudioPlaySerialflashRaw  playFlashRaw3;  //xy=1409.5001029968262,508.5000228881836
extern AudioPlaySerialflashRaw  playFlashRaw7;  //xy=1409.5001029968262,652.5000228881836
extern AudioPlaySerialflashRaw  playFlashRaw8;  //xy=1409.5001029968262,688.5000228881836
extern AudioPlaySerialflashRaw  playFlashRaw2;  //xy=1410.5001029968262,471.5000228881836
extern AudioPlaySerialflashRaw  playFlashRaw4;  //xy=1411.5001029968262,544.5000228881836
extern AudioPlaySerialflashRaw  playFlashRaw9;  //xy=1411.5001029968262,723.5000228881836
extern AudioFilterStateVariable filter1;        //xy=1568.5001029968262,961.5000228881836
extern AudioFilterStateVariable filter2;        //xy=1577.5001029968262,1096.5000228881836
extern AudioFilterStateVariable filter4;        //xy=1584.5001029968262,1379.5000228881836
extern AudioFilterStateVariable filter3;        //xy=1585.5001029968262,1232.5000228881836
extern AudioFilterStateVariable filter5;        //xy=1593.5001029968262,1521.5000228881836
extern AudioFilterStateVariable filter6;        //xy=1593.5001029968262,1659.5000228881836
extern AudioFilterStateVariable filter7;        //xy=1602.5001029968262,1806.5000228881836
extern AudioFilterStateVariable filter8;        //xy=1607.5001029968262,1969.5000228881836
extern AudioEffectEnvelope      sample_envelope_7; //xy=1617.5001029968262,652.5000228881836
extern AudioEffectEnvelope      sample_envelope_11; //xy=1618.5001029968262,790.5000228881836
extern AudioEffectEnvelope      sample_envelope_12; //xy=1618.5001029968262,825.5000228881836
extern AudioEffectEnvelope      sample_envelope_6; //xy=1619.5001029968262,617.5000228881836
extern AudioEffectEnvelope      sample_envelope_8; //xy=1619.5001029968262,689.5000228881836
extern AudioEffectEnvelope      sample_envelope_9; //xy=1619.5001029968262,721.5000228881836
extern AudioEffectEnvelope      sample_envelope_5; //xy=1621.5001029968262,580.5000228881836
extern AudioEffectEnvelope      sample_envelope_1; //xy=1622.5001029968262,430.5000228881836
extern AudioEffectEnvelope      sample_envelope_3; //xy=1622.5001029968262,508.5000228881836
extern AudioEffectEnvelope      sample_envelope_4; //xy=1622.5001029968262,544.5000228881836
extern AudioEffectEnvelope      sample_envelope_2; //xy=1623.5001029968262,470.5000228881836
extern AudioEffectEnvelope      sample_envelope_10; //xy=1622.5001029968262,757.5000228881836
extern AudioPlaySdWav           playSdWav1;     //xy=1662.5001029968262,262.5000228881836
extern AudioInputI2S            i2s2;           //xy=1758.5007781982422,1029.8576383590698
extern AudioMixer4              translator_mixer; //xy=1834.5001029968262,275.5000228881836
extern AudioMixer4              preview_mixer;  //xy=1834.5001029968262,352.5000228881836
extern AudioMixer4              sample_secondary_mixer_3; //xy=1866.5001029968262,781.5000228881836
extern AudioMixer4              sample_secondary_mixer_2; //xy=1868.5001029968262,622.5000228881836
extern AudioMixer4              synth_secondary_mixer_1; //xy=1869.5001029968262,1353.5000228881836
extern AudioMixer4              sample_secondary_mixer_1; //xy=1876.5001029968262,487.5000228881836
extern AudioMixer4              synth_secondary_mixer_2; //xy=1873.5001029968262,1526.5000228881836
extern AudioPlaySdRaw           playSdRec;     //xy=1911.5005531311035,1164.0003128051758
extern AudioMixer4              input_mixer;         //xy=1919.500587463379,1042.0002174377441
extern AudioMixer4              record_mixer;         //xy=1923.500617980957,1110.0003070831299
extern AudioAnalyzePeak         peak_left;          //xy=1925.5005187988281,928.0001611709595
extern AudioAnalyzePeak         peak_right;          //xy=1928.5005149841309,964.0001811981201
extern AudioRecordQueue         queue1; //xy=2023.0006923675537,275.50013732910156
extern AudioRecordQueue         record_queue;         //xy=2087.50048828125,1110.0002737045288
extern AudioMixer4              sample_primary_mixer; //xy=2128.500102996826,618.5000228881836
extern AudioMixer4              synth_primary_mixer; //xy=2141.500102996826,1448.5000228881836
extern AudioMixer4              output_mixer;   //xy=2322.500102996826,1006.5000228881836
extern AudioOutputI2S           i2s1; //xy=2515.500102996826,1006.5000228881836
extern AudioConnection          patchCord1;
extern AudioConnection          patchCord2;
extern AudioConnection          patchCord3;
extern AudioConnection          patchCord4;
extern AudioConnection          patchCord5;
extern AudioConnection          patchCord6;
extern AudioConnection          patchCord7;
extern AudioConnection          patchCord8;
extern AudioConnection          patchCord9;
extern AudioConnection          patchCord10;
extern AudioConnection          patchCord11;
extern AudioConnection          patchCord12;
extern AudioConnection          patchCord13;
extern AudioConnection          patchCord14;
extern AudioConnection          patchCord15;
extern AudioConnection          patchCord16;
extern AudioConnection          patchCord17;
extern AudioConnection          patchCord18;
extern AudioConnection          patchCord19;
extern AudioConnection          patchCord20;
extern AudioConnection          patchCord21;
extern AudioConnection          patchCord22;
extern AudioConnection          patchCord23;
extern AudioConnection          patchCord24;
extern AudioConnection          patchCord25;
extern AudioConnection          patchCord26;
extern AudioConnection          patchCord27;
extern AudioConnection          patchCord28;
extern AudioConnection          patchCord29;
extern AudioConnection          patchCord30;
extern AudioConnection          patchCord31;
extern AudioConnection          patchCord32;
extern AudioConnection          patchCord33;
extern AudioConnection          patchCord34;
extern AudioConnection          patchCord35;
extern AudioConnection          patchCord36;
extern AudioConnection          patchCord37;
extern AudioConnection          patchCord38;
extern AudioConnection          patchCord39;
extern AudioConnection          patchCord40;
extern AudioConnection          patchCord41;
extern AudioConnection          patchCord42;
extern AudioConnection          patchCord43;
extern AudioConnection          patchCord44;
extern AudioConnection          patchCord45;
extern AudioConnection          patchCord46;
extern AudioConnection          patchCord47;
extern AudioConnection          patchCord48;
extern AudioConnection          patchCord49;
extern AudioConnection          patchCord50;
extern AudioConnection          patchCord51;
extern AudioConnection          patchCord52;
extern AudioConnection          patchCord53;
extern AudioConnection          patchCord54;
extern AudioConnection          patchCord55;
extern AudioConnection          patchCord56;
extern AudioConnection          patchCord57;
extern AudioConnection          patchCord58;
extern AudioConnection          patchCord59;
extern AudioConnection          patchCord60;
extern AudioConnection          patchCord61;
extern AudioConnection          patchCord62;
extern AudioConnection          patchCord63;
extern AudioConnection          patchCord64;
extern AudioConnection          patchCord65;
extern AudioConnection          patchCord66;
extern AudioConnection          patchCord67;
extern AudioConnection          patchCord68;
extern AudioConnection          patchCord69;
extern AudioConnection          patchCord70;
extern AudioConnection          patchCord71;
extern AudioConnection          patchCord72;
extern AudioConnection          patchCord73;
extern AudioConnection          patchCord74;
extern AudioConnection          patchCord75;
extern AudioConnection          patchCord76;
extern AudioConnection          patchCord77;
extern AudioConnection          patchCord78;
extern AudioConnection          patchCord79;
extern AudioConnection          patchCord80;
extern AudioConnection          patchCord81;
extern AudioConnection          patchCord82;
extern AudioConnection          patchCord83;
extern AudioConnection          patchCord84;
extern AudioConnection          patchCord85;
extern AudioConnection          patchCord86;
extern AudioConnection          patchCord87;
extern AudioConnection          patchCord88;
extern AudioConnection          patchCord89;
extern AudioConnection          patchCord90;
extern AudioConnection          patchCord91;
extern AudioConnection          patchCord92;
extern AudioConnection          patchCord93;
extern AudioConnection          patchCord94;
extern AudioConnection          patchCord95;
extern AudioConnection          patchCord96;
extern AudioConnection          patchCord97;
extern AudioConnection          patchCord98;
extern AudioConnection          patchCord99;
extern AudioConnection          patchCord100;
extern AudioConnection          patchCord101;
extern AudioConnection          patchCord102;
extern AudioConnection          patchCord103;
extern AudioConnection          patchCord104;
extern AudioConnection          patchCord105;
extern AudioConnection          patchCord106;
extern AudioConnection          patchCord107;
extern AudioConnection          patchCord108;
extern AudioConnection          patchCord109;
extern AudioConnection          patchCord110;
extern AudioConnection          patchCord111;
extern AudioConnection          patchCord112;
extern AudioConnection          patchCord113;
extern AudioConnection          patchCord114;
extern AudioConnection          patchCord115;
extern AudioConnection          patchCord116;
extern AudioConnection          patchCord117;
extern AudioConnection          patchCord118;
extern AudioConnection          patchCord119;
extern AudioConnection          patchCord120;
extern AudioConnection          patchCord121;
extern AudioConnection          patchCord122;
extern AudioConnection          patchCord123;
extern AudioConnection          patchCord124;
extern AudioConnection          patchCord125;
extern AudioConnection          patchCord126;
extern AudioConnection          patchCord127;
extern AudioConnection          patchCord128;
extern AudioConnection          patchCord129;
extern AudioConnection          patchCord130;
extern AudioConnection          patchCord131;
extern AudioConnection          patchCord132;
extern AudioConnection          patchCord133;
extern AudioConnection          patchCord134;
extern AudioConnection          patchCord135;
extern AudioConnection          patchCord136;
extern AudioConnection          patchCord137;
extern AudioConnection          patchCord138;
extern AudioConnection          patchCord139;
extern AudioConnection          patchCord140;
extern AudioConnection          patchCord141;
extern AudioConnection          patchCord142;
extern AudioConnection          patchCord143;
extern AudioControlSGTL5000     codec;     //xy=2489.857521057129,1740.7860898971558
// GUItool: end automatically generated code
#pragma endregion

//Pointer arrays for sampler parameters
extern AudioEffectEnvelope *sample_envelope_bank[12];
extern AudioPlaySerialflashRaw *flash_players[12];

//Pointer arrays for synth parameters
extern AudioSynthWaveformModulated *a_bank[8];
extern AudioSynthWaveformModulated *b_bank[8];
extern AudioSynthNoisePink *noise_bank[8];
extern AudioEffectEnvelope *synth_envelope_bank[8];
extern AudioFilterStateVariable *filter_bank[8];

void initAudio();
#endif