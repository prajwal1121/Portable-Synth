#ifndef SYNTH_H
#define SYNTH_H

#include <Arduino.h>
#include "Display.h"
/*
 * Synth Stuff
 */
//start off with a sinewave in arbitrary waveform
extern EXTMEM int16_t arbWave[257];
extern const int16_t sineWave[257]; 

#define numOscillators 3 
#define numModOctaves 2

#define bendStFactor 8000 //number of semitones to bend * 1000
#define bendHz 800

#define envParameters 4 
extern float adsr[envParameters];
extern char adsrNames[4];
extern const float noteFreqs[128];
#define numSynthMenus 5

class Synth {
  private:
    int8_t octave;
    bool arbSelectPrev;
    bool arbSelect;
    bool waveformEditEnable;
    byte chosenOscillator;
    byte chosenOscPrev;
    byte chosenParameter;
    byte chosenParameterPrev;
    int waveIdx;
    unsigned long waveIdxTimer;
    uint16_t waveDrawColor;
    int hOffset;
    int vOffset;
    int8_t circY;
    int8_t circX;
    int8_t circYPrev;
    int8_t circXPrev;
    byte i_got_here_first[2];
    byte chosenModSource;
    bool optionScreen;
    bool chosenModOption;
    bool modEditScreen;
    bool modAssignScreen;
    byte LFOWaveShape[2];
    byte LFOWaveShapePrev[2];
    byte chosenModDestination;
    byte isAnythingPlaying;
    static const byte KEY_BUFFER_SIZE = 8;
    int semitonesTune;
    int detunePercent;
    float detuneFactor;
    float filterQ;
    byte waveShape[numOscillators];
    float waveFrequency[numOscillators];
    float waveAmplitude[numOscillators];
    float LFOFrequency[2];
    float LFOFrequencyPrev[2];
    float LFOAmplitude[2];
    float LFOAmplitudePrev[2];
    float modadsr[2][5];
    bool LFODest[2][4];
    bool envDest[2][5];

    void switchWave(byte oscillatorNum);
    void keyBuff(byte note, bool noteState);
    void oscPlay(byte note); 
    void oscStop();
    void updateSynthEnvelope();
    void updateModLFODest(byte LFOnum);
    void updateModLFO(byte LFOnum);
    void updateModLFOShape(byte LFOnum);
    void updateModEnvDest(byte envnum);
    void updateModEnvelope(byte envnum);
    void init();
  public:
    byte joyYMod;
    byte joyXMod;
    bool enableJoystickMod[2];
    float pitchBend;
    float bendExponent;
    float filterBend;
    int filterFreq;
    byte voiceStates[8];
    byte currentFreqs[8];
    
    Synth()
      : waveIdx{1},
      waveIdxTimer{millis()},
      waveDrawColor{WHITE},
      i_got_here_first{1,0},
      semitonesTune{12},
      detunePercent{0},
      detuneFactor{1},
      filterQ{1.0},
      waveFrequency{2.0,2.0,2.0},
      waveAmplitude{0.0,1.0,1.0},
      
      joyYMod{1},
      joyXMod{0},
      enableJoystickMod{1,1},
      pitchBend{1.0},
      filterFreq{1000}
    {
      init();
    }
    
    void menuCheck();
    void staticMenu();
    byte nextAvailableVoice();
    void polyPlay(byte voiceNum, byte note);
    void updateFreq();
    void updateFilter();
    float getWaveAmplitude(byte waveNum);
};

#endif