bool keyboardButtons[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool samplePad[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
const byte numButtons = 24;
byte buttonStates[6] = {0,0,0,0,0};

const byte numEncoders = 4;
int encoders[numEncoders] = {0,0,0,0};
bool freshData = false;

bool click1 = false; 
bool click2 = false;
bool click3 = false;
bool click4 = false;

bool mainSelect = false;
bool selected = false;
byte menuScreen = 1;
bool left = false;
bool right = false;

//Sampler Controls
bool previewButton = false;

//Sequencer Controls
bool playSequenceButton = false;
bool eraseSequenceButton = false;

bool synthButton = 0;
bool samplerButton = 0;
bool sequencerButton = 0;

PROGMEM const byte joyX = 25;
PROGMEM const byte joyY = 24;

void readInputs(){   
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
  samplerButton = bitRead(buttonStates[1],3);//SW11
  sequencerButton = bitRead(buttonStates[1],4);//SW11
  
  switch (function) {
    case 1:
      previewButton = bitRead(buttonStates[0],3);//SW4
    break;
    case 2:
      playSequenceButton = bitRead(buttonStates[0],3);//SW4
      eraseSequenceButton = bitRead(buttonStates[0],4);//SW5
    break;
  }
}

void updateEncoders(){  
  click1 = bitRead(buttonStates[6],0);
  click2 = bitRead(buttonStates[6],1);
  click3 = bitRead(buttonStates[6],2);
  click4 = bitRead(buttonStates[6],3);
  
  if (freshData){
    for (int e = 0; e < numEncoders; e++){
      byte mask = B00000011;
      mask = mask << e*2;
      byte enc_val = buttonStates[7 ] & mask;
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
