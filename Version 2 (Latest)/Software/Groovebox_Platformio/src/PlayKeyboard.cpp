#include "PlayKeyboard.h"
#include "Synth.h"
#include "Sampler.h"
#include "Display.h"
#include "ReadInputs.h"
#include "AudioConfig.h"

extern Synth synth;

byte keystate[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool padState[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
bool controlstate[4] = {0,0,0,0};

void PlayKeyboard::play(){   
  for (byte i = 0; i < 24; i++){
    if (keyboardButtons[i]){
      if (!keystate[i]){
        byte voiceNum = synth.nextAvailableVoice();
        synth.currentFreqs[voiceNum] = i+48;
        synth.polyPlay(voiceNum,i+48);
        mod_env1.noteOn();
        mod_env2.noteOn();
        keystate[i] = voiceNum+1;
      }
    }
    else{
      if (keystate[i]){
        byte voiceNum = keystate[i]-1;
        synth.currentFreqs[voiceNum] = 0;
        synth_envelope_bank[voiceNum]->noteOff();
        mod_env1.noteOff();
        mod_env2.noteOff();
        keystate[i] = 0;
        synth.voiceStates[voiceNum]=0;
      }
    }
  }
  
  for (byte j = 0; j < 8; j++){
    if(!synth_envelope_bank[j]->isActive()){
      a_bank[j]->amplitude(0.0);
      b_bank[j]->amplitude(0.0);
      noise_bank[j]->amplitude(0.0);
    }
  }
  
  for (byte j = 0; j < 12; j++){    
    if (samplePad[j]){
      if (!padState[j]){
        sample_envelope_bank[j]->noteOff();
        flash_players[j]->play(samps[j].fileName);
        sample_envelope_bank[j]->noteOn();
        padState[j] = 1;
      }
    }
    else{
      if (padState[j]){
        sample_envelope_bank[j]->noteOff();
        padState[j] = 0;
      }
      if(!sample_envelope_bank[j]->isActive()){
        flash_players[j]->stop();
      }
    }
  }

  if(synth.enableJoystickMod[0]){
    switch(synth.joyYMod){
      case 0:
      break;
      case 1:
        synth.bendExponent = map(analogRead(joyY),130,820,-bendStFactor,bendStFactor)/(12000.0);
        synth.pitchBend = pow(2,synth.bendExponent);
        synth.updateFreq();
      break;
      case 2:
        synth.filterBend = map(analogRead(joyY),130,820,-bendHz,bendHz);
        if (synth.filterFreq-synth.filterBend < 100) synth.filterBend = synth.filterFreq-100;
        synth.updateFilter();                                      
      break;
    }
  }
  if(synth.enableJoystickMod[1]){
      switch(synth.joyXMod){
        case 0:
        break;
        case 1:
          synth.bendExponent = map(analogRead(joyX),220,870,bendStFactor,-bendStFactor)/(12000.0);
          synth.pitchBend = pow(2,synth.bendExponent);
          synth.updateFreq();
        break;
        case 2:
          synth.filterBend = map(analogRead(joyX),220,870,bendHz,-bendHz);
          if (synth.filterFreq-synth.filterBend < 0) synth.filterBend = synth.filterFreq;
          synth.updateFilter();    
        break;
      }
    }
}