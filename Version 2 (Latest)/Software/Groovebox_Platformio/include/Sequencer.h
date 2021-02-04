#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <Arduino.h>

//Sequencer Stuff
extern EXTMEM bool stepSequence[32][12];
extern EXTMEM bool stepSynth[32][24];
extern EXTMEM byte sampleIsPlaying[12];
extern EXTMEM byte assigningNotPlaying[12];
extern uint32_t bpm;
extern uint32_t bpmPrev;

class Sequencer {
  private:
    const byte numStepsInSequence = 32;
    const byte numStepsOnScreen = 16;
    uint32_t ms_per_step;
    uint32_t tempoMillis;
    int sequenceLoc;
    byte prevSequenceLoc;
    bool playSequence;
    bool playSequenceButtonPrev;
    bool eraseSequenceButtonPrev;
    byte seqSection;
    byte seqSectionPrev;
    byte seqDirection;
    byte seqDirectionPrev;
    
    void init();
  public:
    Sequencer()
      :ms_per_step{uint32_t(1.0)/(uint32_t(4.0)*(bpm/uint32_t(60000.0)))},//1.0/(bpm/60000.0)ms/beat divided by 4steps/beat
      tempoMillis{millis()},
      prevSequenceLoc{255}
    {
      init();
    }
    void menuCheck();
    void staticMenu();
};

#endif