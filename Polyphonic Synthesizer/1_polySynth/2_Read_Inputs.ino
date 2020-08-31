const int numButtons = 24;
int current_byte = 0;
int current_button = 0;
byte buttonStates[6] = {0,0,0,0,0};

const int numEncoders = 3;
int encoders[numEncoders] = {0,0,0};
bool freshData = false;

void readInputs(){   
    Wire.requestFrom(8, 6);

    while(Wire.available()) { 
      buttonStates[0] = Wire.read();
      buttonStates[1] = Wire.read();
      buttonStates[2] = Wire.read();
      buttonStates[3] = Wire.read();
      buttonStates[4] = Wire.read();
      buttonStates[5] = Wire.read();
    }
  freshData = true; 

  left = bitRead(buttonStates[4],3);
  right = bitRead(buttonStates[4],4); 
}

void updateEncoders(){  
  click1 = bitRead(buttonStates[4],5);
  click2 = bitRead(buttonStates[4],6);
  click3 = bitRead(buttonStates[4],7);
  
  if (freshData){
    for (int e = 0; e < numEncoders; e++){
      byte mask = B00000011;
      mask = mask << e*2;
      byte enc_val = buttonStates[5] & mask;
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
