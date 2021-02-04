#ifndef READ_INPUTS_H
#define READ_INPUTS_H

#include <Arduino.h>

extern bool keyboardButtons[24];
extern bool samplePad[12];
extern const byte numButtons;
extern byte buttonStates[8];

extern const byte numEncoders;
extern int encoders[4];
extern bool freshData;

extern bool click1; 
extern bool click2;
extern bool click3;
extern bool click4;

extern bool mainSelect;
extern bool selected;
extern byte menuScreen;
extern bool left;
extern bool right;

//Sampler Controls
extern bool previewButton;
extern bool previewButtonPrev;

//Sequencer Controls
extern bool playSequenceButton;
extern bool eraseSequenceButton;

extern bool synthButton;
extern bool samplerButton;
extern bool sequencerButton;
extern bool audioRecordButton;

//Recorder Controls
extern bool recordButton;
extern bool eraseButton;
extern bool storeButton;
extern bool recordButtonPrev;
extern bool eraseButtonPrev;
extern bool storeButtonPrev;

extern const byte joyX;
extern const byte joyY;

//Shared control variables
extern bool click1Prev;
extern float enc1Count;
extern int8_t enc1CountPrev;
extern int enc1Change;

extern bool click2Prev;
extern float enc2Count;
extern int enc2Change;

extern bool click3Prev;
extern float enc3Count;
extern int enc3Change;

extern float enc4Count;
extern int enc4Change;

extern bool mainSelectPrev;
extern bool rightPrev;
extern bool leftPrev;

extern uint16_t color1;
extern uint16_t color2;

//Switch between different device functions
extern bool synthButtonPrev;
extern bool samplerButtonPrev;
extern bool sequencerButtonPrev;
extern bool audioRecordButtonPrev;

class ReadInputs {
  private:
    void init();
  public:
    ReadInputs()
    {
      init();
    }
    void readInputs();
    void updateEncoders();
};

#endif