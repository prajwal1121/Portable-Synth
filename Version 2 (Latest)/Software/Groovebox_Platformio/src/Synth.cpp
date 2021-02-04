#include "Synth.h"
#include "Display.h"
#include "ReadInputs.h"
#include "AudioConfig.h"

const float noteFreqs[] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};
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

float adsr[envParameters] = {10.5,35.0,1.0,300};
char adsrNames[4] = {'A','D','S','R'};

void Synth::init() {
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
}

void Synth::menuCheck() {
  //Menu Changer
  enc4Change = encoders[3]-enc4Change;
  enc4Count = enc4Count + enc4Change;
  if (enc4Count<0) enc4Count= 0;
  if (enc4Count>numSynthMenus) enc4Count= numSynthMenus;
  screen = enc4Count;
  if (screen != screenPrev){
    oled.fillScreen(BLACK);
    enc1Count = 0;
    enc1Change = 0;
    enc2Count = 0;
    enc2Change = 0;
    enc3Count = 0;
    enc3Change = 0;
    encoders[0] = 0;
    encoders[1] = 0;
    encoders[2] = 0;

    if (screen==0)enc2Count = waveAmplitude[0];
    if (screen==1)enc2Count = adsr[0];
    if (screen==2){
      enc1Count = semitonesTune;
      enc2Count = detunePercent;
    }
    if (screen==3){
      enc1Count = filterFreq;
      enc2Count = filterQ;
    }
    if (screen==4){
      enc1Count = joyYMod;
      enc2Count = joyXMod;
    }
  }
  screenPrev = screen;
  enc4Change = encoders[3];

  //Transposer
  if (left and !leftPrev){
    octave = octave - 12;
    if (octave < -24)octave = -24;
  }
  leftPrev = left;
  if (right and !rightPrev){
    octave = octave + 12;
    if (octave > 24)octave = 24;
  }
  rightPrev = right;
  
  switch (screen) {
    case 0: //Oscillator Screen
      enc1Change = encoders[0]-enc1Change;
      enc1Count = enc1Count + enc1Change;
      if (enc1Count<0) enc1Count= 0;
      if (enc1Count>2) enc1Count= 2;
      chosenOscillator = enc1Count;
      if (chosenOscillator != chosenOscPrev){
        enc2Change = 0;
        encoders[1] = 0;
        enc2Count = waveAmplitude[chosenOscillator];
        chosenOscPrev = chosenOscillator; 
      }
      enc1Change = encoders[0];
    
      //Amplitude Scrolling
      enc2Change = encoders[1]-enc2Change;
      enc2Count = enc2Count + 0.1*enc2Change;
      if (enc2Count < 0) enc2Count = 0;
      if (enc2Count > 1.0) enc2Count = 1.0;
      waveAmplitude[chosenOscillator] = enc2Count;
      switch (chosenOscillator){
        case 0:
          for (byte n = 0; n < 8; n++){
            noise_bank[n]->amplitude(waveAmplitude[0]);
          }
          break;
        case 1:
          for (byte a = 0; a < 8; a++){
            a_bank[a]->amplitude(waveAmplitude[1]);
          }
          break;
        case 2:
          for (byte b = 0; b < 8; b++){
            b_bank[b]->amplitude(waveAmplitude[2]);
          }
          break;
      }
      enc2Change = encoders[1];
      
      if (click1 and !click1Prev){
        switchWave(chosenOscillator);
        oled.fillRoundRect(10,(40*chosenOscillator)+18,45,30,5,BLACK);
      }
      click1Prev = click1;
    
      if (click3 and !arbSelectPrev){
        if (arbSelect){
          arbSelect = 0;
          oled.fillScreen(BLACK);
          for (int i=0; i < numled; i++) {
            leds.setPixel(i, BLACK);
            leds.setBrightness(5);
            leds.show();
          }
        }
        else if (!arbSelect and waveformEditEnable){
          arbSelect = 1;
          oled.fillScreen(BLACK);
          for (int i=0; i < numled; i++) {
            leds.setPixel(i, 0xFF1088);
            leds.setBrightness(5);
            leds.show();
          }
        }
      }
      arbSelectPrev = click3;
    
      if (arbSelect){
        if (right and (millis()-waveIdxTimer > 10)){
          waveIdx = waveIdx+1;
          if (waveIdx >= 255)waveIdx = 255;
          waveIdxTimer = millis();
        }
        else if (left and (millis()-waveIdxTimer > 10)){
          waveIdx = waveIdx-1;
          if (waveIdx <= 1)waveIdx = 1;
          waveIdxTimer = millis();
        }
    
        arbWave[waveIdx] = map(analogRead(joyY),130,820,-30000,30000);
        if (arbWave[waveIdx] > 30000) arbWave[waveIdx] = 30000;
        if (arbWave[waveIdx] <-30000) arbWave[waveIdx] = -30000;
      }
    break;

    case 1:
      enc1Change = encoders[0]-enc1Change;
      enc1Count = enc1Count + enc1Change;
      if (enc1Count < 0) enc1Count = 0;
      if (enc1Count > 3) enc1Count = 3;
      chosenParameter = enc1Count;
      if (chosenParameter != chosenParameterPrev){
        enc2Change = 0;
        encoders[1] = 0;
        enc2Count = adsr[chosenParameter];
        chosenParameterPrev = chosenParameter;
      }
      
      enc1Change = encoders[0];
      
      //Parameter Scrolling
      enc2Change = encoders[1]-enc2Change;
      switch (chosenParameter){
        case 0://Attack - 0-3000 in steps of 150
          enc2Count = enc2Count + 150*enc2Change;
          if (enc2Count > 3000) enc2Count = 3000;
          break;
        case 1://Decay - 0-3000 in steps of 150
          enc2Count = enc2Count + 150*enc2Change;
          if (enc2Count > 3000) enc2Count = 3000;
          break;
        case 2://Sustain - 0-1.0 in steps of 0.05
          enc2Count = enc2Count + 0.05*enc2Change;
          if (enc2Count > 1.0) enc2Count = 1.0;
          break;
        case 3://Release - 0-3000 in steps of 150
          enc2Count = enc2Count + 150*enc2Change;
          if (enc2Count > 3000) enc2Count = 3000;
          break;
      }
      if (enc2Count < 0) enc2Count = 0;
      adsr[chosenParameter] = enc2Count;
      updateSynthEnvelope();
      enc2Change = encoders[1];
    break;

    case 2://Osc 2 Tuning
      //Semitone Scrolling
      enc1Change = encoders[0]-enc1Change;
      enc1Count = enc1Count + enc1Change;
      if (enc1Count < -24) enc1Count = -24;
      if (enc1Count > 24) enc1Count = 24;
      semitonesTune = enc1Count;
      enc1Change = encoders[0];
      
      //Detune Scrolling
      enc2Change = encoders[1]-enc2Change;
      enc2Count = enc2Count + enc2Change;
      if (enc2Count < -5) enc2Count = -5;
      if (enc2Count > 5) enc2Count = 5;
      detunePercent = enc2Count;
      detuneFactor = 1.0 + (detunePercent/100.0);
      enc2Change = encoders[1];

    break;

    case 3:
      //Freqency Scrolling
      enc1Change = encoders[0]-enc1Change;
      enc1Count = enc1Count + 50*enc1Change;
      if (enc1Count < 100) enc1Count = 100;
      if (enc1Count > 3000) enc1Count = 3000;
      filterFreq = enc1Count;
      updateFilter();
      enc1Change = encoders[0];

      //Resonance Scrolling
      enc2Change = encoders[1]-enc2Change;
      enc2Count = enc2Count + 0.1*enc2Change;
      if (enc2Count < 0) enc2Count = 0;
      if (enc2Count > 3.0) enc2Count = 3.0;
      filterQ = enc2Count;
      updateFilter();
      enc2Change = encoders[1];
      
      for (int i=0; i < numled; i++) {
        leds.setPixel(i, BLACK);
        leds.setBrightness(0);
        leds.show();
      }
    break;
    
    case 4://Joystick Mod
      circY = map(analogRead(joyY),130,820,22,-22);
      circX = map(analogRead(joyX),220,870,22,-22);

      enc1Change = encoders[0]-enc1Change;
      enc1Count = enc1Count + enc1Change;
      if (enc1Count<0) enc1Count = 0;
      if (enc1Count>2) enc1Count = 2;
      joyYMod = enc1Count;
      if ((joyYMod == joyXMod)&&(joyYMod == i_got_here_first[1])){
        enableJoystickMod[0] = 0;
        i_got_here_first[0] = 255;
        color1 = 0xA514;
      }
      else{
        enableJoystickMod[0] = 1;
        i_got_here_first[0] = joyYMod;
        color1 = RED;
      }
      enc1Change = encoders[0];

      enc2Change = encoders[1]-enc2Change;
      enc2Count = enc2Count + enc2Change;
      if (enc2Count<0) enc2Count = 0;
      if (enc2Count>2) enc2Count = 2;
      joyXMod = enc2Count;
      if ((joyXMod == joyYMod)&&(joyXMod == i_got_here_first[0])){
        enableJoystickMod[1] = 0;
        i_got_here_first[1] = 255;
        color2 = 0xA514;
      }
      else{
        enableJoystickMod[1] = 1;
        i_got_here_first[1] = joyXMod;
        color2 = GREEN;
      }
      enc2Change = encoders[1];

      for (int i=0; i < numled; i++) {
        leds.setPixel(i, 0xFF1088);
        leds.setBrightness(5);
        leds.show();
      }
    break;

    case 5:
      if(optionScreen){
        if (modEditScreen){
          if (chosenModSource == 0 or chosenModSource == 1){
            enc1Change = encoders[0]-enc1Change;
            enc1Count = enc1Count + enc1Change;
            if (enc1Count<0) enc1Count= 8;
            if (enc1Count>8) enc1Count= 0;
            LFOWaveShape[chosenModSource] = enc1Count;  
            enc1Change = encoders[0];
            
            if (LFOWaveShape[chosenModSource] != LFOWaveShapePrev[chosenModSource]){
              oled.fillRect(45,44,35,18,BLACK);
              updateModLFOShape(chosenModSource);
              LFOWaveShapePrev[chosenModSource]=LFOWaveShape[chosenModSource];
            }

            enc2Change = encoders[1]-enc2Change;
            enc2Count = enc2Count + 0.1*enc2Change;
            if (enc2Count<0) enc2Count= 0;
            if (enc2Count>10.0) enc2Count= 10.0;
            LFOFrequency[chosenModSource] = enc2Count;  
            enc2Change = encoders[1];
            if (LFOFrequency[chosenModSource] != LFOFrequencyPrev[chosenModSource]){
              updateModLFO(chosenModSource);
              LFOFrequencyPrev[chosenModSource] = LFOFrequency[chosenModSource];  
            }

            enc3Change = encoders[2]-enc3Change;
            enc3Count = enc3Count + 0.1*enc3Change;
            if (enc3Count<0) enc3Count= 0;
            if (enc3Count>1.0) enc3Count= 1.0;
            LFOAmplitude[chosenModSource] = enc3Count;  
            enc3Change = encoders[2];
            if (LFOAmplitude[chosenModSource] != LFOAmplitudePrev[chosenModSource]){
              updateModLFO(chosenModSource);
              LFOAmplitudePrev[chosenModSource] = LFOAmplitude[chosenModSource];  
            }         
          }
          else{
            enc1Change = encoders[0]-enc1Change;
            enc1Count = enc1Count + enc1Change;
            if (enc1Count < 0) enc1Count = 0;
            if (enc1Count > 3) enc1Count = 3;
            chosenParameter = enc1Count;
            if (chosenParameter != chosenParameterPrev){
              enc2Change = 0;
              encoders[1] = 0;
              enc2Count = modadsr[chosenModSource-2][chosenParameter];
              chosenParameterPrev = chosenParameter;
            }
            enc1Change = encoders[0];
            
            //Parameter Scrolling
            enc2Change = encoders[1]-enc2Change;
            switch (chosenParameter){
              case 0://Attack - 0-3000 in steps of 150
                enc2Count = enc2Count + 150*enc2Change;
                if (enc2Count > 3000) enc2Count = 3000;
                break;
              case 1://Decay - 0-3000 in steps of 150
                enc2Count = enc2Count + 150*enc2Change;
                if (enc2Count > 3000) enc2Count = 3000;
                break;
              case 2://Sustain - 0-1.0 in steps of 0.05
                enc2Count = enc2Count + 0.05*enc2Change;
                if (enc2Count > 1.0) enc2Count = 1.0;
                break;
              case 3://Release - 0-3000 in steps of 150
                enc2Count = enc2Count + 150*enc2Change;
                if (enc2Count > 3000) enc2Count = 3000;
                break;
            }
            if (enc2Count < 0) enc2Count = 0;
            modadsr[chosenModSource-2][chosenParameter] = enc2Count;
            enc2Change = encoders[1];

            enc3Change = encoders[2]-enc3Change;
            enc3Count = enc3Count + 0.1*enc3Change;
            if (enc3Count<-1.0) enc3Count= -1.0;
            if (enc3Count>1.0) enc3Count= 1.0;
            modadsr[chosenModSource-2][4] = enc3Count;  
            enc3Change = encoders[2];

            updateModEnvelope(chosenModSource-2);
          }

          if (click2 and !click2Prev){
            modEditScreen = 0;
            oled.fillScreen(BLACK);
            encoders[0] = 0;
            encoders[1] = 0;
            encoders[2] = 0;
            enc1Change = 0;
            enc2Change = 0;
            enc3Change = 0;
            enc1Count = 0;
            enc2Count = chosenModOption;
            enc3Count = 0;
          }
          click2Prev = click2;
        }
        else if (modAssignScreen){
          enc3Change = encoders[2]-enc3Change;
          enc3Count = enc3Count + enc3Change;
          if (enc3Count<0) enc3Count= 0;
          if (chosenModSource == 0 or chosenModSource == 1){
            if (enc3Count>3) enc3Count= 3;
          }
          else {
            if (enc3Count>4) enc3Count= 4;
          }
          chosenModDestination = enc3Count;  
          enc3Change = encoders[2];

          if (chosenModSource == 0 or chosenModSource == 1){
            if (click3 and !click3Prev){
              LFODest[chosenModSource][chosenModDestination] = !LFODest[chosenModSource][chosenModDestination];
              oled.fillCircle(100,32+chosenModDestination*26,3,BLACK);
              updateModLFODest(chosenModSource);
            }
            click3Prev = click3;
          }
          else{
            if (click3 and !click3Prev){
              envDest[chosenModSource-2][chosenModDestination] = !envDest[chosenModSource-2][chosenModDestination];
              oled.fillCircle(100,32+chosenModDestination*20,3,BLACK);
              updateModEnvDest(chosenModSource-2);
            }
            click3Prev = click3;
          }
          
          if (click2 and !click2Prev){
            modAssignScreen = 0;
            oled.fillScreen(BLACK);
            encoders[0] = 0;
            encoders[1] = 0;
            encoders[2] = 0;
            enc1Change = 0;
            enc2Change = 0;
            enc3Change = 0;
            enc1Count = 0;
            enc2Count = chosenModOption;
            enc3Count = 0;
          }
          click2Prev = click2;

        }
        else{
          enc2Change = encoders[1]-enc2Change;
          enc2Count = enc2Count + enc2Change;
          if (enc2Count<0) enc2Count= 0;
          if (enc2Count>1) enc2Count= 1;
          chosenModOption = enc2Count;  
          enc2Change = encoders[1];
          if (click2 and !click2Prev){
            if (!chosenModOption) {
              modEditScreen = 1;
              if(chosenModSource == 0 or chosenModSource == 1){
                encoders[0] = 0;
                encoders[1] = 0;
                encoders[2] = 0;
                enc1Change = 0;
                enc2Change = 0;
                enc3Change = 0;
                enc1Count = LFOWaveShape[chosenModSource];
                enc2Count = LFOFrequency[chosenModSource];
                enc3Count = LFOAmplitude[chosenModSource];
              }
              else{
                encoders[0] = 0;
                encoders[1] = 0;
                encoders[2] = 0;
                enc1Change = 0;
                enc2Change = 0;
                enc3Change = 0;
                enc1Count = 0;
                enc2Count = modadsr[chosenModSource-2][0];
                enc3Count = modadsr[chosenModSource-2][4];
              }    
            }
            else {
              modAssignScreen = 1;
              encoders[0] = 0;
              encoders[1] = 0;
              encoders[2] = 0;
              enc1Change = 0;
              enc2Change = 0;
              enc3Change = 0;
              enc1Count = 0;
              enc2Count = 0;
              enc3Count = 0;
            }
            
            oled.fillScreen(BLACK);
          }
          click2Prev = click2;
  
          if (click1 and !click1Prev){
            optionScreen = 0;
            oled.fillScreen(BLACK);
            encoders[0] = 0;
            encoders[1] = 0;
            encoders[2] = 0;
            enc1Change = 0;
            enc2Change = 0;
            enc3Change = 0;
            enc1Count = chosenModSource;
            enc2Count = 0;
            enc3Count = 0;
          }
          click1Prev = click1;
        }
      }
      else{
        enc1Change = encoders[0]-enc1Change;
        enc1Count = enc1Count + enc1Change;
        if (enc1Count<0) enc1Count= 0;
        if (enc1Count>3) enc1Count= 3;
        chosenModSource = enc1Count;  
        enc1Change = encoders[0];
  
        if (click1 and !click1Prev){
          optionScreen = 1;
          encoders[0] = 0;
          encoders[1] = 0;
          encoders[2] = 0;
          enc1Change = 0;
          enc2Change = 0;
          enc3Change = 0;
          enc1Count = 0;
          enc2Count = 0;
          enc3Count = 0;
          oled.fillScreen(BLACK);
        }
        click1Prev = click1;
      }
      
      for (int i=0; i < numled; i++) {
        leds.setPixel(i, BLACK);
        leds.setBrightness(0);
        leds.show();
      }
    break;
  }
}

void Synth::staticMenu() {
  switch (screen) {
  case 0: //Oscillator Screen
    if (arbSelect){
      digitalWrite(enc1LED,LOW);
      digitalWrite(enc2LED,LOW);
      digitalWrite(enc4LED,LOW);
       
      oled.setTextSize(1);
      oled.setTextColor(MAGENTA,BLACK);
      oled.setCursor(20, 2);
      oled.print(F("Waveform Editor"));
      oled.drawRoundRect(0,0,127,11,6, MAGENTA);
      oled.drawFastHLine(0,70,127,WHITE);
      for (int s=0; s < 257; s++) {
        if ((s%2)==0){
          int8_t val = 50*(arbWave[s]/32767.0);
          if ((s == waveIdx) or (s == waveIdx-1)){
            waveDrawColor = RED;
          }
          else{
            waveDrawColor = WHITE;
          }
          if (val <=0){
             oled.drawFastVLine(s/2,70+1,-1*val,waveDrawColor);
             oled.drawFastVLine(s/2,70-50,50,BLACK);
             oled.drawLine(s/2,70+50,s/2,70+(-1*val)+1,BLACK);
             
          }
          else{
            oled.drawFastVLine(s/2,70-val,val,waveDrawColor);
            oled.drawFastVLine(s/2,70+1,70+50,BLACK);
            oled.drawLine(s/2,70-50,s/2,70-val-1,BLACK);
          }
        }
      }
    }
    else{
    //Light up active encoders
    digitalWrite(enc1LED,HIGH);
    digitalWrite(enc2LED,HIGH);
    digitalWrite(enc4LED,HIGH);  
    //Write out header
    oled.setTextSize(1);
    oled.setTextColor(WHITE,BLACK);
    oled.setCursor(35, 2);
    oled.print(F("Oscillators"));
    oled.drawFastHLine(0,10,124, WHITE);
    oled.fillTriangle(127,10,124,13,124,7,YELLOW);
  
    //Show octave
    oled.setTextSize(1);
    oled.setCursor(5, 2);
    oled.setTextColor(WHITE,BLACK);
    if(octave>0){
      oled.print(F("+"));
    }
    else if(octave==0){
      oled.print(F("+"));
      oled.fillRect(16,0,19,9,BLACK);
    }
    oled.println(octave);
  
    for (byte i = 0; i<numOscillators; i++){
      oled.setTextColor(WHITE,BLACK);
      oled.setTextSize(1);
      oled.setCursor(100,(40*i)+24);
      oled.print(F("AMP"));
      oled.setCursor(100,(40*i)+36);
      oled.print(waveAmplitude[i]);
      
      uint16_t waveColor = 0;
      if (i == chosenOscillator){
        oled.setTextColor(GREEN,BLACK);
        oled.setCursor(0,(40*i)+25);
        oled.drawRoundRect(10,(40*i)+18,45,30,5,GREEN);
        oled.drawFastHLine(58,(40*i)+34,int(waveAmplitude[i]*40)-1,GREEN);
        oled.drawFastHLine(58+int(waveAmplitude[i]*40),(40*i)+34,98-int(waveAmplitude[i]*40),BLACK);
        oled.drawCircle(0,(40*i)+32,8,RED);
        if (waveShape[i]==4){
          digitalWrite(enc3LED,HIGH);
          oled.drawRoundRect(12,(40*i)+22,41,22,5,BLUE);
          waveformEditEnable = 1;          
        }
        else{
          digitalWrite(enc3LED,LOW);
          oled.drawRoundRect(12,(40*i)+22,41,22,5,BLACK); 
          waveformEditEnable = 0;   
        }
        waveColor = RED;
      }
      else{
        oled.setTextColor(WHITE,BLACK);
        oled.drawRoundRect(10,(40*i)+18,45,30,5,WHITE);
        oled.drawFastHLine(58,(40*i)+34,int(waveAmplitude[i]*40),WHITE);
        oled.drawFastHLine(58+int(waveAmplitude[i]*40)+1,(40*i)+34,98-int(waveAmplitude[i]*40),BLACK);
        oled.drawCircle(0,(40*i)+32,8,BLACK);
        if (waveShape[i]==4){
          oled.drawRoundRect(12,(40*i)+22,41,22,5,BLACK);
          waveformEditEnable = 0;               
        }
        
        oled.drawRoundRect(12,(40*i)+22,41,22,5,BLACK);  
        
        waveColor = WHITE;
      }
  
      oled.setTextSize(1);
      oled.setCursor(0,(40*i)+29);
      if (i == 0){
        oled.print(F("N"));
      }
      else{
        oled.print(i); 
      }
      
      if ((i == 1) or (i == 2)){
        switch(waveShape[i]){
          case 0://SINE
            oled.setCursor(16,(40*i)+26);
            oled.setTextColor(waveColor,BLACK);
            oled.setTextSize(2);
            oled.print(F("SIN"));
            break;
          case 1://SAW
            oled.drawFastHLine(17, (40*i)+40, 8, waveColor);
            oled.drawLine(25, (40*i)+40, 40, (40*i)+24, waveColor);
            oled.drawFastVLine(40, (40*i)+24, 16, waveColor);
            oled.drawFastHLine(40, (40*i)+40, 8, waveColor);
            break;
          case 2://SQUARE
            oled.drawFastHLine(17, (40*i)+40, 8, waveColor);
            oled.drawFastVLine(25, (40*i)+24, 16, waveColor);
            oled.drawFastHLine(25, (40*i)+24, 15, waveColor);
            oled.drawFastVLine(40, (40*i)+24, 16, waveColor);
            oled.drawFastHLine(40, (40*i)+40, 8, waveColor);
            break;
          case 3://TRI
            oled.drawFastHLine(17, (40*i)+40, 8, waveColor);
            oled.drawLine(25, (40*i)+40, 33, (40*i)+24, waveColor);
            oled.drawLine(33, (40*i)+24, 40, (40*i)+40, waveColor);
            oled.drawFastHLine(40, (40*i)+40, 8, waveColor);
            break;
          case 4://ARB
            oled.setCursor(16,(40*i)+26);
            oled.setTextColor(waveColor,BLACK);
            oled.setTextSize(2);
            oled.print(F("ARB"));
            break;
          case 5://PULSE
            oled.drawFastHLine(17, (40*i)+40, 12, waveColor);
            oled.drawFastVLine(29, (40*i)+24, 16, waveColor);
            oled.drawFastHLine(29, (40*i)+24, 7, waveColor);
            oled.drawFastVLine(36, (40*i)+24, 16, waveColor);
            oled.drawFastHLine(36, (40*i)+40, 12, waveColor);
            oled.setCursor(19,(40*i)+24);
            oled.setTextColor(waveColor,BLACK);
            oled.setTextSize(1);
            oled.print(F("P"));
            break;
          case 6://REV SAW
            oled.drawFastHLine(17, (40*i)+40, 8, waveColor);
            oled.drawFastVLine(25, (40*i)+24, 16, waveColor);
            oled.drawLine(25, (40*i)+24, 40, (40*i)+40, waveColor);
            oled.drawFastHLine(40, (40*i)+40, 8, waveColor);
            break;
          case 7://SAMPLEHOLD
            oled.drawFastHLine(17, (40*i)+40, 12, waveColor);
            oled.drawFastVLine(29, (40*i)+24, 16, waveColor);
            oled.drawFastHLine(29, (40*i)+24, 7, waveColor);
            oled.drawFastVLine(36, (40*i)+24, 10, waveColor);
            oled.drawFastHLine(36, (40*i)+34, 5, waveColor);
            oled.drawFastVLine(41, (40*i)+34, 6, waveColor);
            oled.drawFastHLine(41, (40*i)+40, 7, waveColor);
            oled.setTextColor(waveColor,BLACK);
            oled.setTextSize(1);
            oled.setCursor(17,(40*i)+24);
            oled.print(F("S")); 
            oled.setCursor(22,(40*i)+31);
            oled.print(F("H")); 
            break;
          case 8://VAR TRI
            oled.drawFastHLine(17, (40*i)+40, 8, waveColor);
            oled.drawLine(25, (40*i)+40, 33, (40*i)+24, waveColor);
            oled.drawLine(33, (40*i)+24, 40, (40*i)+40, waveColor);
            oled.drawFastHLine(40, (40*i)+40, 8, waveColor);
            oled.setTextColor(waveColor,BLACK);
            oled.setTextSize(1);
            oled.setCursor(19,(40*i)+24);
            oled.print(F("V")); 
            break;
        }
      }
      else{//NOISE
        oled.drawFastHLine(17, 35, 8, WHITE);
        oled.drawLine(25, 35, 27, 26, WHITE);
        oled.drawLine(27, 26, 29, 42, WHITE);
        oled.drawLine(29, 42, 32, 24, WHITE);
        oled.drawLine(32, 24, 36, 41, WHITE);
        oled.drawLine(36, 41, 38, 25, WHITE);
        oled.drawLine(38, 25, 40, 35, WHITE);
        oled.drawFastHLine(40, 35, 8, WHITE);
      }
    }
    }
    break;

    case 1: //Main Envelope Screen
      digitalWrite(enc1LED,HIGH);
      digitalWrite(enc2LED,HIGH);      
      digitalWrite(enc3LED,LOW);
      digitalWrite(enc4LED,HIGH);  
      
      //Write out header
      oled.setTextSize(1);
      oled.setTextColor(WHITE,BLACK);
      oled.setCursor(27, 2);
      oled.print(F("Main Envelope"));
      oled.drawFastHLine(3,10,121, WHITE);
      oled.fillTriangle(0,10,3,13,3,7,YELLOW);
      oled.fillTriangle(127,10,124,13,124,7,YELLOW);

      //Show octave
      oled.setTextSize(1);
      oled.setCursor(5, 2);
      oled.setTextColor(WHITE,BLACK);
      if(octave>0){
        oled.print(F("+"));
      }
      else if(octave==0){
        oled.print(F("+"));
        oled.fillRect(16,0,6,9,BLACK);
      }
      oled.println(octave);

      for (byte i = 0; i<4; i++){
        byte xloc = (2*(i+1))+(30*i);
        if (i == chosenParameter){
          oled.drawRect(xloc-1,100,30,15,RED);
          color1 = RED;
          color2 = GREEN;
        }
        else{
          oled.drawRect(xloc-1,100,30,15,WHITE);
          color1 = WHITE;
          color2 = WHITE;
        }
        oled.setCursor(xloc+12,104);
        oled.setTextColor(color1,BLACK);
        oled.print(adsrNames[i]);

        int8_t circleLoc = 0;
        switch (i){
          case 0://Attack - 0-3000 in steps of 150
            circleLoc = 95-(adsr[i]/3000.0)*75.0;
            break;
          case 1://Decay - 0-3000 in steps of 150
            circleLoc = 95.0-(adsr[i]/3000.0)*75.0;
            break;
          case 2://Sustain - 0-1.0 in steps of 0.05
            circleLoc = 95.0-adsr[i]*75.0;
            break;
          case 3://Release - 0-3000 in steps of 150
            circleLoc = 95.0-(adsr[i]/3000.0)*75.0;
            break;
        }
        
        oled.drawLine(xloc+14, 100, xloc+14, circleLoc, color2);
        oled.fillCircle(xloc+14, circleLoc, 3, color2);

        oled.drawLine(xloc+10,11,xloc+10,circleLoc-1,BLACK);
        oled.drawLine(xloc+11,11,xloc+11,circleLoc-2,BLACK);
        oled.drawLine(xloc+12,11,xloc+12,circleLoc-3,BLACK);
        oled.drawLine(xloc+13,11,xloc+13,circleLoc-4,BLACK);
        oled.drawLine(xloc+14,11,xloc+14,circleLoc-4,BLACK);
        oled.drawLine(xloc+15,11,xloc+15,circleLoc-4,BLACK);
        oled.drawLine(xloc+16,11,xloc+16,circleLoc-3,BLACK);
        oled.drawLine(xloc+17,11,xloc+17,circleLoc-2,BLACK);
        oled.drawLine(xloc+18,11,xloc+18,circleLoc-1,BLACK);

        oled.drawLine(xloc+10,99,xloc+10,circleLoc+1,BLACK);
        oled.drawLine(xloc+11,99,xloc+11,circleLoc+2,BLACK);
        oled.drawLine(xloc+12,99,xloc+12,circleLoc+3,BLACK);
        oled.drawLine(xloc+13,99,xloc+13,circleLoc+4,BLACK);

        oled.drawLine(xloc+15,99,xloc+15,circleLoc+4,BLACK);
        oled.drawLine(xloc+16,99,xloc+16,circleLoc+3,BLACK);
        oled.drawLine(xloc+17,99,xloc+17,circleLoc+2,BLACK);
        oled.drawLine(xloc+18,99,xloc+18,circleLoc+1,BLACK);
      }
    break;

    case 2://Osc 2 Tune
      digitalWrite(enc1LED,HIGH);
      digitalWrite(enc2LED,HIGH);      
      digitalWrite(enc3LED,LOW);
      digitalWrite(enc4LED,HIGH);  
      
      //Write out header
      oled.setTextSize(1);
      oled.setTextColor(WHITE,BLACK);
      oled.setCursor(35, 2);
      oled.print(F("Osc 2 Tune"));
      oled.drawFastHLine(3,10,121, WHITE);
      oled.fillTriangle(0,10,3,13,3,7,YELLOW);
      oled.fillTriangle(127,10,124,13,124,7,YELLOW);

      //Show octave
      oled.setTextSize(1);
      oled.setCursor(5, 2);
      oled.setTextColor(WHITE,BLACK);
      if(octave>0){
        oled.print(F("+"));
      }
      else if(octave==0){
        oled.print(F("+"));
        oled.fillRect(16,0,6,9,BLACK);
      }
      oled.println(octave);

      oled.drawCircle(64,70,34+semitonesTune/2.0+1,RED);
      oled.drawCircle(64,70,34+semitonesTune/2.0-1,RED);
      oled.drawCircle(64,70,34+semitonesTune/2.0+2,RED);
      oled.drawCircle(64,70,34+semitonesTune/2.0-3,RED);
      oled.drawCircle(64,70,34+semitonesTune/2.0,RED);
      oled.drawCircle(64,70,34+semitonesTune/2.0+3,BLACK);
      oled.drawCircle(64,70,34+semitonesTune/2.0-3,BLACK);
      if(semitonesTune<0){
        oled.setCursor(25, 121);
        if(semitonesTune>-10){
          oled.fillRect(97,121,8,8,BLACK);
        }
      }
      else{
        oled.setCursor(30, 121);
        oled.fillRect(25,121,5,8,BLACK);
        if(semitonesTune<10){
          oled.fillRect(95,121,8,8,BLACK);
        }
      }

      oled.setTextColor(RED,BLACK);
      oled.print(F("Semitones:"));
      oled.print(semitonesTune);
      
      oled.drawCircle(64,70,15-1,GREEN);
      oled.drawCircle(64,70,15+1,GREEN);
      oled.drawCircle(64,70,15-3,GREEN);
      oled.drawCircle(64,70,15-3,BLACK);
      oled.drawCircle(64,70,15,GREEN);
      oled.setCursor(0, 18);
      oled.setTextColor(GREEN,BLACK);
      oled.print(F("Detune"));
      oled.drawFastHLine(0,26,35, GREEN);
      oled.drawLine(35,26,52,60, GREEN);
      
      if(detunePercent<0){
        oled.setCursor(56, 67);
      }
      else{
        oled.setCursor(59, 67);
        oled.fillRect(56,67,3,8,BLACK);
        oled.fillRect(70,67,3,8,BLACK);
      }
      oled.print(detunePercent);
      oled.print(F("%"));
      
    break;

    case 3://Filter
      digitalWrite(enc1LED,HIGH);
      digitalWrite(enc2LED,HIGH);      
      digitalWrite(enc3LED,LOW);
      digitalWrite(enc4LED,HIGH);  
      
      //Write out header
      oled.setTextSize(1);
      oled.setTextColor(WHITE,BLACK);
      oled.setCursor(47, 2);
      oled.print(F("Filter"));
      oled.drawFastHLine(3,10,121, WHITE);
      oled.fillTriangle(0,10,3,13,3,7,YELLOW);
      oled.fillTriangle(127,10,124,13,124,7,YELLOW);
  
      //Show octave
      oled.setTextSize(1);
      oled.setCursor(5, 2);
      oled.setTextColor(WHITE,BLACK);
      if(octave>0){
        oled.print(F("+"));
      }
      else if(octave==0){
        oled.print(F("+"));
        oled.fillRect(16,0,6,9,BLACK);
      }
      oled.println(octave);
      
      oled.setCursor(0,30);
      oled.setTextColor(RED,BLACK);
      oled.print(F("F:"));
      oled.print(filterFreq);
      if (filterFreq < 1000)oled.fillRect(30,30,6,7,BLACK);

      oled.setCursor(0,40);
      oled.setTextColor(GREEN,BLACK);
      oled.print(F("Q:"));
      oled.print(filterQ);
      
      hOffset = 67*(filterFreq/3000.0)+56;
      vOffset = 64-filterQ*13;

      oled.fillRoundRect(0,70,hOffset,75,20,RED);
      oled.fillRect(0,70,20,75,RED);
      oled.fillRect(hOffset,70,128-(hOffset),75,BLACK);
      oled.drawFastHLine(hOffset-16,70,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-13,71,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-11,72,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-9,73,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-8,74,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-7,75,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-6,76,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-5,77,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-4,78,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-3,79,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-3,80,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-2,81,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-2,82,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-1,83,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-1,84,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-1,85,128-hOffset,BLACK);

      oled.fillCircle(hOffset-18,vOffset,3,GREEN);
      oled.drawCircle(hOffset-18,vOffset,4,BLACK);
      oled.drawCircle(hOffset-18,vOffset,5,BLACK);
      oled.drawFastHLine(hOffset-21,vOffset+4,6,BLACK);
      oled.drawFastHLine(hOffset-21,vOffset-4,6,BLACK);
      
    break;
    
    case 4://Joystick Assign
      digitalWrite(enc1LED,HIGH);
      digitalWrite(enc2LED,HIGH);      
      digitalWrite(enc3LED,LOW);
      digitalWrite(enc4LED,HIGH);  
      
      //Write out header
      oled.setTextSize(1);
      oled.setTextColor(WHITE,BLACK);
      oled.setCursor(40, 2);
      oled.print(F("Joystick"));
      oled.drawFastHLine(3,10,121, WHITE);
      oled.fillTriangle(0,10,3,13,3,7,YELLOW);
      oled.fillTriangle(127,10,124,13,124,7,YELLOW);
  
      //Show octave
      oled.setTextSize(1);
      oled.setCursor(5, 2);
      oled.setTextColor(WHITE,BLACK);
      if(octave>0){
        oled.print(F("+"));
      }
      else if(octave==0){
        oled.print(F("+"));
        oled.fillRect(16,0,6,9,BLACK);
      }
      oled.println(octave);

      oled.drawFastHLine(20,40,40, WHITE);
      oled.drawFastVLine(10,50,40, WHITE);
      oled.drawFastHLine(20,100,40, WHITE);
      oled.drawFastVLine(70,50,40, WHITE);

      oled.drawLine(60,40,70,50, WHITE);
      oled.drawLine(58,40,70,52, WHITE);
      oled.drawLine(56,40,70,54, WHITE);
      
      oled.drawLine(70,90,60,100, WHITE);
      oled.drawLine(70,88,58,100, WHITE);
      oled.drawLine(70,86,56,100, WHITE);
      
      oled.drawLine(20,100,10,90, WHITE);
      oled.drawLine(22,100,10,88, WHITE);
      oled.drawLine(24,100,10,86, WHITE);
      
      oled.drawLine(10,50,20,40, WHITE);
      oled.drawLine(10,52,22,40, WHITE);
      oled.drawLine(10,54,24,40, WHITE);
      
      oled.fillCircle(40+circX,70+circY,5,MAGENTA);
      if (circYPrev != circY || circXPrev != circX){
        oled.fillCircle(40+circXPrev,70+circYPrev,5,BLACK);
      }

      oled.setTextColor(color1, BLACK);
      switch(joyYMod){
        case 0:
          oled.setCursor(18,32);
          oled.println(F("Disabled"));
        break;
        case 1:
          oled.setCursor(27,32);
          oled.println(F("Pitch"));
          oled.fillRect(15,32,12,7,BLACK);
          oled.fillRect(57,32,12,7,BLACK);
        break;
        case 2:
          oled.setCursor(25,32);
          oled.println(F("Filter"));
        break;
      }
      
      oled.setTextColor(color2, BLACK);
      switch(joyXMod){
        case 0:
          oled.setCursor(72,68);
          oled.println(F("Disabled"));
        break;
        case 1:
          oled.setCursor(72,68);
          oled.println(F("Pitch"));
          oled.fillRect(102,68,18,9,BLACK);
        break;
        case 2:
          oled.setCursor(72,68);
          oled.println(F("Filter"));

        break;
      }
      circYPrev = circY;
      circXPrev = circX;    
    break;

    case 5://Mod Sources
      if(optionScreen){
        if(modEditScreen){
          digitalWrite(enc1LED,HIGH);
          digitalWrite(enc2LED,HIGH);
          digitalWrite(enc3LED,HIGH);
          digitalWrite(enc4LED,LOW); 
          
          oled.setTextSize(1);
          oled.setTextColor(MAGENTA,BLACK);
          oled.setCursor(48, 2);
          oled.println(F("Editor"));
          oled.drawRoundRect(0,0,127,11,6, MAGENTA);

          oled.fillCircle(5,20,2,GREEN);
          
          if (chosenModSource == 0 or chosenModSource == 1){
            oled.drawFastHLine(0,70,128,WHITE);
            oled.drawFastVLine(64,70,60,WHITE);
            
            oled.setCursor(48, 20);
            oled.setTextColor(WHITE,BLACK);
            oled.println(F("SHAPE"));
            oled.drawFastVLine(62,28,12,WHITE);
            oled.fillTriangle(65,38,59,38,62,41,WHITE);

            oled.setTextColor(WHITE,BLACK);
            oled.setCursor(5, 74);
            oled.println(F("FREQUENCY"));
            oled.drawFastVLine(32,82,12,WHITE);
            oled.fillTriangle(32,97,29,94,35,94,WHITE);
            oled.setTextColor(GREEN,BLACK);
            oled.setTextSize(2);
            if(LFOFrequency[chosenModSource]<10.0){
              oled.setCursor(9, 102);
              oled.fillRect(0,102,8,20,BLACK);
              oled.fillRect(55,102,8,20,BLACK);
            }
            else{
              oled.setCursor(0, 102);
            }
            oled.println(LFOFrequency[chosenModSource]);

            oled.setTextColor(WHITE,BLACK);
            oled.setTextSize(1);
            oled.setCursor(70, 74);
            oled.println(F("AMPLITUDE"));
            oled.drawFastVLine(97,82,12,WHITE);
            oled.fillTriangle(97,97,94,94,100,94,WHITE);
            oled.setTextColor(BLUE,BLACK);
            oled.setTextSize(2);
            oled.setCursor(73, 102);
            oled.println(LFOAmplitude[chosenModSource]);
            
            switch(LFOWaveShape[chosenModSource]){
              case 0://SINE
                oled.setCursor(46,46);
                oled.setTextColor(RED,BLACK);
                oled.setTextSize(2);
                oled.print(F("SIN"));
                break;
              case 1://SAW
                oled.drawFastHLine(46, 60, 8, RED);
                oled.drawLine(54, 60, 69, 44, RED);
                oled.drawFastVLine(69, 44, 16, RED);
                oled.drawFastHLine(69, 60, 8, RED);
                break;
              case 2://SQUARE
                oled.drawFastHLine(46, 60, 8, RED);
                oled.drawFastVLine(54, 44, 16, RED);
                oled.drawFastHLine(54, 44, 15, RED);
                oled.drawFastVLine(69, 44, 16, RED);
                oled.drawFastHLine(69, 60, 8, RED);
                break;
              case 3://TRI
                oled.drawFastHLine(46, 60, 8, RED);
                oled.drawLine(54, 60, 62, 44, RED);
                oled.drawLine(62, 44, 69, 60, RED);
                oled.drawFastHLine(69, 60, 8, RED);
                break;
              case 4://ARB
                oled.setCursor(45,46);
                oled.setTextColor(RED,BLACK);
                oled.setTextSize(2);
                oled.print(F("ARB"));
                break;
              case 5://PULSE
                oled.drawFastHLine(46, 60, 12, RED);
                oled.drawFastVLine(59, 44, 16, RED);
                oled.drawFastHLine(59, 44, 7, RED);
                oled.drawFastVLine(65, 44, 16, RED);
                oled.drawFastHLine(65, 60, 12, RED);
                oled.setCursor(49,44);
                oled.setTextColor(RED,BLACK);
                oled.setTextSize(1);
                oled.print(F("P"));
                break;
              case 6://REV SAW
                oled.drawFastHLine(46, 60, 8, RED);
                oled.drawFastVLine(54, 44, 16, RED);
                oled.drawLine(54, 44, 69, 60, RED);
                oled.drawFastHLine(69, 60, 8, RED);
                break;
              case 7://SAMPLEHOLD
                oled.drawFastHLine(46, 60, 12, RED);
                oled.drawFastVLine(59, 44, 16, RED);
                oled.drawFastHLine(59, 44, 7, RED);
                oled.drawFastVLine(66, 44, 10, RED);
                oled.drawFastHLine(66, 54, 5, RED);
                oled.drawFastVLine(70, 54, 6, RED);
                oled.drawFastHLine(70, 60, 7, RED);
                oled.setTextColor(RED,BLACK);
                oled.setTextSize(1);
                oled.setCursor(46,44);
                oled.print(F("S")); 
                oled.setCursor(51,51);
                oled.print(F("H")); 
                break;
              case 8://VAR TRI
                oled.drawFastHLine(46, 60, 8, RED);
                oled.drawLine(54, 60, 62, 44, RED);
                oled.drawLine(62, 44, 69, 60, RED);
                oled.drawFastHLine(69, 60, 8, RED);
                oled.setTextColor(RED,BLACK);
                oled.setTextSize(1);
                oled.setCursor(49,44);
                oled.print(F("V")); 
                break;
            }
          }
          else{
            oled.setCursor(36, 20);
            oled.setTextColor(WHITE,BLACK);
            oled.print(F("Depth:"));
            oled.setTextColor(BLUE,BLACK);
            oled.print(modadsr[chosenModSource-2][4]);
            oled.setTextColor(WHITE,BLACK);
            
            for (byte i = 0; i<4; i++){
              byte xloc = (2*(i+1))+(30*i);
              if (i == chosenParameter){
                oled.drawRect(xloc-1,100,30,15,RED);
                color1 = RED;
                color2 = GREEN;
              }
              else{
                oled.drawRect(xloc-1,100,30,15,WHITE);
                color1 = WHITE;
                color2 = WHITE;
              }
              oled.setCursor(xloc+12,104);
              oled.setTextColor(color1,BLACK);
              oled.print(adsrNames[i]);
      
              int8_t circleLoc = 0;
              switch (i){
                case 0://Attack - 0-3000 in steps of 150
                  circleLoc = 95-(modadsr[chosenModSource-2][i]/3000.0)*60.0;
                  break;
                case 1://Decay - 0-3000 in steps of 150
                  circleLoc = 95.0-(modadsr[chosenModSource-2][i]/3000.0)*60.0;
                  break;
                case 2://Sustain - 0-1.0 in steps of 0.05
                  circleLoc = 95.0-modadsr[chosenModSource-2][i]*60.0;
                  break;
                case 3://Release - 0-3000 in steps of 150
                  circleLoc = 95.0-(modadsr[chosenModSource-2][i]/3000.0)*60.0;
                  break;
              }

              oled.drawLine(xloc+14, 100, xloc+14, circleLoc, color2);
              oled.fillCircle(xloc+14, circleLoc, 3, color2);
      
              oled.drawLine(xloc+10,29,xloc+10,circleLoc-1,BLACK);
              oled.drawLine(xloc+11,29,xloc+11,circleLoc-2,BLACK);
              oled.drawLine(xloc+12,29,xloc+12,circleLoc-3,BLACK);
              oled.drawLine(xloc+13,29,xloc+13,circleLoc-4,BLACK);
              oled.drawLine(xloc+14,29,xloc+14,circleLoc-4,BLACK);
              oled.drawLine(xloc+15,29,xloc+15,circleLoc-4,BLACK);
              oled.drawLine(xloc+16,29,xloc+16,circleLoc-3,BLACK);
              oled.drawLine(xloc+17,29,xloc+17,circleLoc-2,BLACK);
              oled.drawLine(xloc+18,29,xloc+18,circleLoc-1,BLACK);
      
              oled.drawLine(xloc+10,99,xloc+10,circleLoc+1,BLACK);
              oled.drawLine(xloc+11,99,xloc+11,circleLoc+2,BLACK);
              oled.drawLine(xloc+12,99,xloc+12,circleLoc+3,BLACK);
              oled.drawLine(xloc+13,99,xloc+13,circleLoc+4,BLACK);
      
              oled.drawLine(xloc+15,99,xloc+15,circleLoc+4,BLACK);
              oled.drawLine(xloc+16,99,xloc+16,circleLoc+3,BLACK);
              oled.drawLine(xloc+17,99,xloc+17,circleLoc+2,BLACK);
              oled.drawLine(xloc+18,99,xloc+18,circleLoc+1,BLACK);
            }
          }
        }
        else if (modAssignScreen){
          digitalWrite(enc1LED,HIGH);
          digitalWrite(enc2LED,HIGH);
          digitalWrite(enc3LED,HIGH);
          digitalWrite(enc4LED,LOW); 
          
          oled.setTextSize(1);
          oled.setTextColor(MAGENTA,BLACK);
          oled.setCursor(48, 2);
          oled.println(F("Assign"));
          oled.drawRoundRect(0,0,127,11,6, MAGENTA);

          oled.fillCircle(5,20,2,GREEN);

          if (chosenModSource == 0 or chosenModSource == 1){
            for (byte m = 0; m < 4; m++){
              if (m==chosenModDestination) {
                color1 = BLUE;
                color2 = BLUE;
              }
              else {
                color1 = BLACK;
                color2 = WHITE;
              }
      
              oled.drawFastHLine(5,32+m*26,35,color1);
              oled.fillTriangle(43,32+m*26,40,35+m*26,40,29+m*26,color1);
              if(LFODest[chosenModSource][m])oled.fillCircle(100,32+m*26,3,color2);
              else oled.drawCircle(100,32+m*26,3,color2);
              oled.setCursor(50,29+m*26);
              oled.setTextColor(color2,BLACK);
              switch(m){
                case 0:
                  oled.println(F("OSC 1"));
                break;
                case 1:
                  oled.println(F("OSC 2"));
                break;
                case 2:
                  oled.println(F("Filter"));
                break; 
                case 3:
                  if (chosenModSource == 0)oled.println(F("LFO 2"));
                  else oled.println(F("LFO 1"));
                break;
              } 
            }
          }
          else{
            for (byte m = 0; m < 5; m++){
              if (m==chosenModDestination) {
                color1 = BLUE;
                color2 = BLUE;
              }
              else {
                color1 = BLACK;
                color2 = WHITE;
              }
      
              oled.drawFastHLine(5,32+m*20,35,color1);
              oled.fillTriangle(43,32+m*20,40,35+m*20,40,29+m*20,color1);
              if(envDest[chosenModSource-2][m])oled.fillCircle(100,32+m*20,3,color2);
              else oled.drawCircle(100,32+m*20,3,color2);
              oled.setCursor(50,29+m*20);
              oled.setTextColor(color2,BLACK);
              switch(m){
                case 0:
                  oled.println(F("OSC 1"));
                break;
                case 1:
                  oled.println(F("OSC 2"));
                break;
                case 2:
                  oled.println(F("Filter"));
                break; 
                case 3:
                  oled.println(F("LFO 1"));
                break;
                case 4:
                  oled.println(F("LFO 2"));
                break;  
              } 
            }
          }
        }
        else{
          digitalWrite(enc1LED,HIGH);
          digitalWrite(enc2LED,HIGH);
          digitalWrite(enc3LED,LOW);
          digitalWrite(enc4LED,LOW); 

          oled.fillCircle(5,20,2,RED);
          
          oled.setTextSize(1);
          oled.setTextColor(MAGENTA,BLACK);
          oled.setCursor(50, 2);
          switch(chosenModSource){
              case 0:
                oled.println(F("LFO 1"));
              break;
              case 1:
                oled.println(F("LFO 2"));
              break;
              case 2:
                oled.println(F("ENV 1"));
              break; 
              case 3:
                oled.println(F("ENV 2"));
              break;
            } 
          oled.drawRoundRect(0,0,127,11,6, MAGENTA);

          for (byte o=0;o<2;o++){
            if (o==chosenModOption) {
              color1 = GREEN;
              color2 = GREEN;
            }
            else{
              color1 = WHITE;
              color2 = BLACK;
            }
            oled.drawCircle(35+o*58,70,25,color1);
            oled.drawCircle(35+o*58,70,20,color2);
            oled.fillTriangle(35+o*58,97,30+o*58,102,40+o*58,102,color2);
            oled.fillTriangle(35+o*58,43,30+o*58,38,40+o*58,38,color2);

            
            oled.setTextColor(color1,BLACK);
            if(!o){
              oled.setCursor(24,67);
              oled.println(F("Edit"));
            }
            else{
              oled.setCursor(76,67);
              oled.println(F("Assign"));
            }
          }
          
        }
      }
      else{
        digitalWrite(enc1LED,HIGH);
        digitalWrite(enc2LED,LOW);      
        digitalWrite(enc3LED,LOW);
        digitalWrite(enc4LED,HIGH);  
        
        //Write out header
        oled.setTextSize(1);
        oled.setTextColor(WHITE,BLACK);
        oled.setCursor(35, 2);
        oled.print(F("Mod Sources"));
        oled.drawFastHLine(3,10,125, WHITE);
        oled.fillTriangle(0,10,3,13,3,7,YELLOW);
    
        //Show octave
        oled.setTextSize(1);
        oled.setCursor(5, 2);
        oled.setTextColor(WHITE,BLACK);
        if(octave>0){
          oled.print(F("+"));
        }
        else if(octave==0){
          oled.print(F("+"));
          oled.fillRect(16,0,6,9,BLACK);
        }
        oled.println(octave);
  
        for (byte m = 0; m < 4; m++){
          if (m==chosenModSource) color1 = RED;
          else color1 = WHITE;
  
          oled.drawRoundRect(0,23+m*25,127,20,5,color1);
          oled.setCursor(50,29+m*26);
          oled.setTextColor(color1,BLACK);
          switch(m){
            case 0:
              oled.println(F("LFO 1"));
            break;
            case 1:
              oled.println(F("LFO 2"));
            break;
            case 2:
              oled.println(F("ENV 1"));
            break; 
            case 3:
              oled.println(F("ENV 2"));
            break;
          } 
        }
      }
    break;
  }
}

void Synth::switchWave (byte oscillatorNum){
    waveShape[oscillatorNum] += 1;
    if (waveShape[oscillatorNum] > 8) waveShape[oscillatorNum] = 0; 
    
    switch (oscillatorNum){
      case 1:
        for (byte a = 0; a < 8; a++){
          a_bank[a]->begin(waveShape[oscillatorNum]);
        }
        break;
      case 2:
        for (byte b = 0; b < 8; b++){
          b_bank[b]->begin(waveShape[oscillatorNum]);
        }
        break;
    }
}

void Synth::keyBuff(byte note, bool noteState) {
  static byte keybuff[KEY_BUFFER_SIZE];
  static byte buffSize = 0;

  // Add Note
  if (noteState == true and (buffSize < KEY_BUFFER_SIZE) ) {
    oscPlay(note);
    keybuff[buffSize] = note;
    buffSize++;
    return;
  }

  // Remove Note
  else if (noteState == false and (buffSize != 0)) {
    for (byte found = 0; found < buffSize; found++) {
      if (keybuff[found] == note) {
        for (byte gap = found; gap < (buffSize - 1); gap++) {
          keybuff[gap] = keybuff[gap + 1];
        }
        buffSize--;
        keybuff[buffSize] = 255;
        if (buffSize != 0) {
          oscPlay(keybuff[buffSize - 1]);
          return;
        }
        else {
          oscStop();
          return;
        }
      }
    }
  }
}

void Synth::oscPlay(byte note) {
  for (byte n = 0; n < 8; n++){
    noise_bank[n]->amplitude(waveAmplitude[0]);
  }
  for (byte a = 0; a < 8; a++){
    a_bank[a]->amplitude(waveAmplitude[1]);
    a_bank[a]->frequency((noteFreqs[note+octave])*pitchBend);
  }
  for (byte b = 0; b < 8; b++){
    b_bank[b]->amplitude(waveAmplitude[2]);
    b_bank[b]->frequency(noteFreqs[note+semitonesTune]*detuneFactor*pitchBend);
  }
  for (byte e = 0; e < 8; e++){
    synth_envelope_bank[e]->noteOn();
  }
  
}

void Synth::polyPlay(byte voiceNum, byte note){
  AudioNoInterrupts();
  noise_bank[voiceNum]->amplitude(waveAmplitude[0]);

  a_bank[voiceNum]->amplitude(waveAmplitude[1]);
  a_bank[voiceNum]->frequency((noteFreqs[note+octave])*pitchBend);

  b_bank[voiceNum]->amplitude(waveAmplitude[2]);
  b_bank[voiceNum]->frequency(noteFreqs[note+semitonesTune]*detuneFactor*pitchBend);

  synth_envelope_bank[voiceNum]->noteOn();
  AudioInterrupts();
}

void Synth::oscStop() {
  for (byte e = 0; e < 8; e++){
    synth_envelope_bank[e]->noteOff();
  }
}

void Synth::updateFreq(){
  for (byte v = 0; v < 8; v++){
    if (voiceStates[v]){
       AudioNoInterrupts();
       a_bank[v]->frequency((noteFreqs[currentFreqs[v]+octave])*pitchBend);
       b_bank[v]->frequency(noteFreqs[currentFreqs[v]+semitonesTune]*detuneFactor*pitchBend);
       AudioInterrupts();
    }
  }
}

void Synth::updateSynthEnvelope() {
  for (byte e = 0; e < 8; e++){
    synth_envelope_bank[e]->attack(adsr[0]);
    synth_envelope_bank[e]->decay(adsr[1]);
    synth_envelope_bank[e]->sustain(adsr[2]);
    synth_envelope_bank[e]->release(adsr[3]);
  }
}

void Synth::updateFilter(){
    for (byte f = 0; f < 8; f++){
    filter_bank[f]->frequency(filterFreq+filterBend);
    filter_bank[f]->resonance(filterQ);
  }
}

void Synth::updateModLFODest(byte LFOnum){
  if (LFODest[LFOnum][0]) {
    if (LFOnum==0 and (!envDest[0][3] or !envDest[1][3]))osc1_pitch_mod_mixer.gain(0,1.0);
    else if (LFOnum==1 and (!envDest[0][4] or !envDest[1][4]))osc1_pitch_mod_mixer.gain(1,1.0);
  }
  else {
    if (LFOnum==0)osc1_pitch_mod_mixer.gain(0,0.0);
    else if (LFOnum==1)osc1_pitch_mod_mixer.gain(1,0.0);
  }

  if (LFODest[LFOnum][1]) {
    if (LFOnum==0 and (!envDest[0][3] or !envDest[1][3]))osc2_pitch_mod_mixer.gain(0,1.0);
    else if (LFOnum==1 and (!envDest[0][4] or !envDest[1][4]))osc2_pitch_mod_mixer.gain(1,1.0);
  }
  else {
    if (LFOnum==0)osc2_pitch_mod_mixer.gain(0,0.0);
    else if (LFOnum==1)osc2_pitch_mod_mixer.gain(1,0.0);
  }

  if (LFODest[LFOnum][2]) {
    if (LFOnum==0 and (!envDest[0][3] or !envDest[1][3]))filter_cutoff_mod_mixer.gain(0,1.0);
    else if (LFOnum==1 and (!envDest[0][4] or !envDest[1][4]))filter_cutoff_mod_mixer.gain(1,1.0);
  }
  else {
    if (LFOnum==0)filter_cutoff_mod_mixer.gain(0,0.0);
    else if (LFOnum==1)filter_cutoff_mod_mixer.gain(1,0.0);
  }

  if (LFODest[LFOnum][3]) {
    if (LFOnum==0 and (!envDest[0][3] or !envDest[1][3]))LFO2_mixer.gain(0,1.0);
    else if (LFOnum==1 and (!envDest[0][4] or !envDest[1][4]))LFO1_mixer.gain(0,1.0);
  }
  else {
    if (LFOnum==0)LFO2_mixer.gain(0,0.0);
    else if (LFOnum==1)LFO1_mixer.gain(0,0.0);
  }
}

void Synth::updateModLFO(byte LFOnum){
  if (LFOnum==0){
    AudioNoInterrupts();
    mod_LFO1.frequency(LFOFrequency[0]);
    mod_LFO1.amplitude(LFOAmplitude[0]);
    AudioInterrupts();
  }
  else if (LFOnum==1){
    AudioNoInterrupts();
    mod_LFO2.frequency(LFOFrequency[1]);
    mod_LFO2.amplitude(LFOAmplitude[1]);
    AudioInterrupts();
  }
}

void Synth::updateModLFOShape(byte LFOnum){
  if (LFOnum==0){
    AudioNoInterrupts();
    mod_LFO1.begin(LFOWaveShape[0]);
    AudioInterrupts();
  }
  else if (LFOnum==1){
    AudioNoInterrupts();
    mod_LFO2.begin(LFOWaveShape[1]);
    AudioInterrupts();
  }
}

void Synth::updateModEnvDest(byte envnum){
  if (envDest[envnum][0]) {
    if (envnum==0)osc1_pitch_mod_mixer.gain(2,1.0);
    else if (envnum==1)osc1_pitch_mod_mixer.gain(3,1.0);
  }
  else {
    if (envnum==0)osc1_pitch_mod_mixer.gain(2,0.0);
    else if (envnum==1)osc1_pitch_mod_mixer.gain(3,0.0);
  }

  if (envDest[envnum][1]) {
    if (envnum==0)osc2_pitch_mod_mixer.gain(2,1.0);
    else if (envnum==1)osc2_pitch_mod_mixer.gain(3,1.0);
  }
  else {
    if (envnum==0)osc2_pitch_mod_mixer.gain(2,0.0);
    else if (envnum==1)osc2_pitch_mod_mixer.gain(3,0.0);
  }

  if (envDest[envnum][2]) {
    if (envnum==0)filter_cutoff_mod_mixer.gain(2,1.0);
    else if (envnum==1)filter_cutoff_mod_mixer.gain(3,1.0);
  }
  else {
    if (envnum==0)filter_cutoff_mod_mixer.gain(2,0.0);
    else if (envnum==1)filter_cutoff_mod_mixer.gain(3,0.0);
  }

  if (envDest[envnum][3]) {//Enabled LFO1 mod
    if (envnum==0){
      env1_mixer.gain(0,1.0);
      
      //Turn off LFO1 direct connections
      osc1_pitch_mod_mixer.gain(0,0.0);
      osc2_pitch_mod_mixer.gain(0,0.0);
      filter_cutoff_mod_mixer.gain(0,0.0);
      LFO2_mixer.gain(0,0.0);
    }
    else if (envnum==1){
      env2_mixer.gain(0,1.0);

      //Turn off LFO1 direct connections
      osc1_pitch_mod_mixer.gain(0,0.0);
      osc2_pitch_mod_mixer.gain(0,0.0);
      filter_cutoff_mod_mixer.gain(0,0.0);
      LFO2_mixer.gain(0,0.0);
    }
  }
  else {//Disabled LFO1 mod
    if (envnum==0){
      env1_mixer.gain(0,0.0);
      
      //Turn off LFO1 direct connections
      if (LFODest[0][0]) osc1_pitch_mod_mixer.gain(0,1.0);
      if (LFODest[0][1]) osc2_pitch_mod_mixer.gain(0,1.0);
      if (LFODest[0][2]) filter_cutoff_mod_mixer.gain(0,1.0);
      if (LFODest[0][3]) LFO2_mixer.gain(0,1.0);
    }
    else if (envnum==1){
      env2_mixer.gain(0,0.0);
      
      //Turn off LFO1 direct connections
      if (LFODest[0][0]) osc1_pitch_mod_mixer.gain(0,1.0);
      if (LFODest[0][1]) osc2_pitch_mod_mixer.gain(0,1.0);
      if (LFODest[0][2]) filter_cutoff_mod_mixer.gain(0,1.0);
      if (LFODest[0][3]) LFO2_mixer.gain(0,1.0);
    }
  }

  if (envDest[envnum][4]) {//Enabled LFO2 mod
    if (envnum==0){
      env1_mixer.gain(1,1.0);

      //Turn off LFO2 direct connections
      osc1_pitch_mod_mixer.gain(1,0.0);
      osc2_pitch_mod_mixer.gain(1,0.0);
      filter_cutoff_mod_mixer.gain(1,0.0);
      LFO1_mixer.gain(0,0.0);
    }
    else if (envnum==1){
      env2_mixer.gain(1,1.0);

      //Turn off LFO2 direct connections
      osc1_pitch_mod_mixer.gain(1,0.0);
      osc2_pitch_mod_mixer.gain(1,0.0);
      filter_cutoff_mod_mixer.gain(1,0.0);
      LFO1_mixer.gain(0,0.0);
    }
  }
  else {//Disabled LFO2 mod
    if (envnum==0){
      env1_mixer.gain(1,0.0);
  
      //Turn off LFO1 direct connections
      if (LFODest[1][0]) osc1_pitch_mod_mixer.gain(1,1.0);
      if (LFODest[1][1]) osc2_pitch_mod_mixer.gain(1,1.0);
      if (LFODest[1][2]) filter_cutoff_mod_mixer.gain(1,1.0);
      if (LFODest[1][3]) LFO2_mixer.gain(1,1.0);
    }
    else if (envnum==1){
      env2_mixer.gain(1,0.0);
            
      //Turn off LFO1 direct connections
      if (LFODest[1][0]) osc1_pitch_mod_mixer.gain(1,1.0);
      if (LFODest[1][1]) osc2_pitch_mod_mixer.gain(1,1.0);
      if (LFODest[1][2]) filter_cutoff_mod_mixer.gain(1,1.0);
      if (LFODest[1][3]) LFO2_mixer.gain(1,1.0);
    }
  }
}

void Synth::updateModEnvelope(byte envnum) {
  if (envnum==0){
    mod_env1.attack(modadsr[envnum][0]);
    mod_env1.decay(modadsr[envnum][1]);
    mod_env1.sustain(modadsr[envnum][2]);
    mod_env1.release(modadsr[envnum][3]);
    env1_dc.amplitude(modadsr[envnum][4]);
  }
  else if (envnum==1){
    mod_env2.attack(modadsr[envnum][0]);
    mod_env2.decay(modadsr[envnum][1]);
    mod_env2.sustain(modadsr[envnum][2]);
    mod_env2.release(modadsr[envnum][3]);
    env2_dc.amplitude(modadsr[envnum][4]);
  }
}

byte Synth::nextAvailableVoice(){
  byte counter = 0;
  for (byte s = 0; s < 8; s++){
    if (voiceStates[s]){
      counter++;
    }
  }
  if (counter == 8){
    byte minimum = 69;
    byte minidx = 69;
    for (byte s = 0; s < 8; s++){
      if (voiceStates[s] < minimum){
        minidx = s;
        minimum = voiceStates[s];
      }
    }
    for (byte s = 0; s < 8; s++){
      voiceStates[s] = voiceStates[s]-1;
    }
    voiceStates[minidx] = counter;
    return minidx;
  }
  else{
    for (byte s = 0; s < 8; s++){
      if (voiceStates[s] == 0){
        voiceStates[s] = counter+1;
        return s;
      }
    }
  }
}

float Synth::getWaveAmplitude(byte waveNum){
  return waveAmplitude[waveNum];
}