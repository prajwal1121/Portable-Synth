/*
 * Reads user interaction data from input processor and puts it 
 * into useful variables
 */
bool keyboardButtons[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const byte numButtons = 24;
int current_byte = 0;
int current_button = 0;
byte buttonStates[8] = {0,0,0,0,0,0,0,0};

const byte numEncoders = 4;
int encoders[numEncoders] = {0,0,0,0};
bool freshData = false;

bool click1 = 0; 
bool click2 = 0;
bool click3 = 0;
bool click4 = 0;

int8_t octave = 0;
bool left = false;
bool right = false;
bool recordButton = false;
bool previewButton = false;
bool eraseButton = false;
bool menuSelect = false;
bool storeButton = false;

#define joyX 25
#define joyY 24

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
  
  left = bitRead(buttonStates[5],4);
  menuSelect = bitRead(buttonStates[5],5);
  right = bitRead(buttonStates[5],6);  
  recordButton = bitRead(buttonStates[0],3);
  previewButton = bitRead(buttonStates[0],4);
  eraseButton = bitRead(buttonStates[0],5);
  storeButton = bitRead(buttonStates[0],6);
  
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
