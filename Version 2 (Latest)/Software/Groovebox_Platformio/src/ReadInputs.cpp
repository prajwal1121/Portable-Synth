#include "ReadInputs.h"
#include "Display.h"
#include <Wire.h>

bool keyboardButtons[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool samplePad[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
const byte numButtons = 24;
byte buttonStates[8] = {0,0,0,0,0,0,0,0};

const byte numEncoders = 4;
int encoders[numEncoders] = {0,0,0,0};
bool freshData = 0;

bool click1 = 0; 
bool click2 = 0;
bool click3 = 0;
bool click4 = 0;

bool mainSelect = 0;
bool selected = 0;
byte menuScreen = 1;
bool left = 0;
bool right = 0;

//Sampler Controls
bool previewButton = 0;
bool previewButtonPrev = 0;

//Sequencer Controls
bool playSequenceButton = 0;
bool eraseSequenceButton = 0;

bool synthButton = 0;
bool samplerButton = 0;
bool sequencerButton = 0;
bool audioRecordButton = 0;

//Recorder Controls
bool recordButton = 0;
bool eraseButton = 0;
bool storeButton = 0;
bool recordButtonPrev = 0;
bool eraseButtonPrev = 0;
bool storeButtonPrev = 0;

const byte joyX = 25;
const byte joyY = 24;

//Shared control variables
bool click1Prev = 0;
float enc1Count = 0;
int8_t enc1CountPrev = 0;
int enc1Change = 0;

bool click2Prev = 0;
float enc2Count = 0;
int enc2Change = 0;

bool click3Prev = 0;
float enc3Count = 0;
int enc3Change = 0;

float enc4Count = 0;
int enc4Change = 0;

bool mainSelectPrev = 0;
bool rightPrev = 0;
bool leftPrev = 0;

uint16_t color1 = WHITE;
uint16_t color2 = WHITE;

//Switch between different device functions
bool synthButtonPrev = 0;
bool samplerButtonPrev = 0;
bool sequencerButtonPrev = 0;
bool audioRecordButtonPrev = 0;

void ReadInputs::init(){
  Wire.begin();
}

void ReadInputs::readInputs(){   
  Wire.requestFrom(9, 8);
  
  while(Wire.available()) { 
    buttonStates[0] = Wire.read();
    buttonStates[1] = Wire.read();
    buttonStates[2] = Wire.read();
    buttonStates[3] = Wire.read();
    buttonStates[4] = Wire.read();
    buttonStates[5] = Wire.read();
    buttonStates[6] = Wire.read();
    buttonStates[7] = Wire.read();
  }
  freshData = true;
  
  mainSelect = bitRead(buttonStates[5],5);
  left = bitRead(buttonStates[5],4);
  right = bitRead(buttonStates[5],6);  

  keyboardButtons[0] = bitRead(buttonStates[3],0);//SW25
  keyboardButtons[1] = bitRead(buttonStates[2],1);//SW18
  keyboardButtons[2] = bitRead(buttonStates[3],1);//SW26
  keyboardButtons[3] = bitRead(buttonStates[2],2);//SW19
  keyboardButtons[4] = bitRead(buttonStates[3],2);//SW27
  keyboardButtons[5] = bitRead(buttonStates[3],3);//SW28
  keyboardButtons[6] = bitRead(buttonStates[2],3);//SW20
  keyboardButtons[7] = bitRead(buttonStates[4],3);//SW36
  keyboardButtons[8] = bitRead(buttonStates[2],4);//SW21
  keyboardButtons[9] = bitRead(buttonStates[4],4);//SW37
  keyboardButtons[10] = bitRead(buttonStates[3],4);//SW29
  keyboardButtons[11] = bitRead(buttonStates[4],5);//SW38
  keyboardButtons[12] = bitRead(buttonStates[4],6);//SW39
  keyboardButtons[13] = bitRead(buttonStates[3],5);//SW30
  keyboardButtons[14] = bitRead(buttonStates[4],7);//SW40
  keyboardButtons[15] = bitRead(buttonStates[3],6);//SW31
  keyboardButtons[16] = bitRead(buttonStates[5],0);//SW41
  keyboardButtons[17] = bitRead(buttonStates[5],1);//SW42
  keyboardButtons[18] = bitRead(buttonStates[3],7);//SW32
  keyboardButtons[19] = bitRead(buttonStates[4],2);//SW35
  keyboardButtons[20] = bitRead(buttonStates[4],0);//SW33
  keyboardButtons[21] = bitRead(buttonStates[5],2);//SW43
  keyboardButtons[22] = bitRead(buttonStates[4],1);//SW34
  keyboardButtons[23] = bitRead(buttonStates[5],3);//SW44

  samplePad[0] = bitRead(buttonStates[0],0);//SW1
  samplePad[1] = bitRead(buttonStates[0],1);//SW2
  samplePad[2] = bitRead(buttonStates[0],2);//SW3
  samplePad[3] = bitRead(buttonStates[0],7);//SW8
  samplePad[4] = bitRead(buttonStates[1],0);//SW9
  samplePad[5] = bitRead(buttonStates[1],1);//SW10
  samplePad[6] = bitRead(buttonStates[1],6);//SW15
  samplePad[7] = bitRead(buttonStates[1],7);//SW16
  samplePad[8] = bitRead(buttonStates[2],0);//SW17
  samplePad[9] = bitRead(buttonStates[2],5);//SW22
  samplePad[10] = bitRead(buttonStates[2],6);//SW23
  samplePad[11] = bitRead(buttonStates[2],7);//SW24

  synthButton = bitRead(buttonStates[1],2);//SW11
  samplerButton = bitRead(buttonStates[1],3);//SW12
  sequencerButton = bitRead(buttonStates[1],4);//SW13
  audioRecordButton = bitRead(buttonStates[1],5);//SW14
  
  switch (function) {
    case 1:
      previewButton = bitRead(buttonStates[0],3);//SW4
    break;
    case 2:
      playSequenceButton = bitRead(buttonStates[0],3);//SW4
      eraseSequenceButton = bitRead(buttonStates[0],4);//SW5
    break;
    case 4:
      recordButton = bitRead(buttonStates[0],3);//SW4
      previewButton = bitRead(buttonStates[0],4);//SW5
      eraseButton = bitRead(buttonStates[0],5);//SW6
      storeButton = bitRead(buttonStates[0],6);//SW7
    break;
  }
}

void ReadInputs::updateEncoders(){  
  click1 = bitRead(buttonStates[6],0);
  click2 = bitRead(buttonStates[6],1);
  click3 = bitRead(buttonStates[6],2);
  click4 = bitRead(buttonStates[6],3);
  
  if (freshData){
    for (int e = 0; e < numEncoders; e++){
      byte mask = B00000011;
      mask = mask << e*2;
      byte enc_val = buttonStates[7] & mask;
      enc_val = enc_val >> e*2;
      if (enc_val == 2){
        encoders[e]--;
      }
      else if (enc_val == 1){
        encoders[e]++;
      }
    }
    freshData = false;
  }
}