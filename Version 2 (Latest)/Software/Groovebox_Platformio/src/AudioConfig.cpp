#include <AudioConfig.h>

/*
 * ASDT Output
 */
#pragma region
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
#pragma endregion

//Pointer arrays for sampler parameters
AudioEffectEnvelope *sample_envelope_bank[12] = {&sample_envelope_1,&sample_envelope_2,&sample_envelope_3,&sample_envelope_4,&sample_envelope_5,&sample_envelope_6,&sample_envelope_7,&sample_envelope_8,&sample_envelope_9,&sample_envelope_10,&sample_envelope_11,&sample_envelope_12};
AudioPlaySerialflashRaw *flash_players[12] = {&playFlashRaw1,&playFlashRaw2,&playFlashRaw3,&playFlashRaw4,&playFlashRaw5,&playFlashRaw6,&playFlashRaw7,&playFlashRaw8,&playFlashRaw9,&playFlashRaw10,&playFlashRaw11,&playFlashRaw12};
//Pointer arrays for synth parameters
AudioSynthWaveformModulated *a_bank[8] = {&wave1a,&wave2a,&wave3a,&wave4a,&wave5a,&wave6a,&wave7a,&wave8a};
AudioSynthWaveformModulated *b_bank[8] = {&wave1b,&wave2b,&wave3b,&wave4b,&wave5b,&wave6b,&wave7b,&wave8b};
AudioSynthNoisePink *noise_bank[8] = {&noise1,&noise2,&noise3,&noise4,&noise5,&noise6,&noise7,&noise8};
AudioEffectEnvelope *synth_envelope_bank[8] = {&synth_envelope_1,&synth_envelope_2,&synth_envelope_3,&synth_envelope_4,&synth_envelope_5,&synth_envelope_6,&synth_envelope_7,&synth_envelope_8};
AudioFilterStateVariable *filter_bank[8] = {&filter1,&filter2,&filter3,&filter4,&filter5,&filter6,&filter7,&filter8};

void initAudio(){
    // Initialize the Codec  
    codec.enable();
    codec.inputSelect(AUDIO_INPUT_MIC);
    codec.dacVolumeRamp();
    codec.lineOutLevel(13);
    codec.volume(0.45);
    
    //Give Audio Library a lot of memory to work with
    AudioMemory(24);
    AudioInterrupts();
}