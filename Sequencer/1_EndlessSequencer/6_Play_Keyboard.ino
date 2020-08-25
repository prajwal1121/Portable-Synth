bool keystate[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool controlstate[4] = {0,0,0,0};

void playKeyboard(){   
  for (int i = 0; i < 24; i++){
    current_byte = i/8;
    current_button = i-8*current_byte;
    if (bitRead(buttonStates[current_byte], current_button)){
      if (!keystate[i]){
        OnNoteOn(chan,i+octave,100);
        sequenceNote(i+octave);
        keystate[i] = 1;
      }
    }
    else{
      if (keystate[i]){
        OnNoteOff(chan,i+octave,100);
        keystate[i] = 0;
      }
    }
  }

  if (addRest){
    if(!controlstate[0]){
      sequenceNote(0);
      controlstate[0] = 1;
    }
  }
  else{
    if(controlstate[0]){
      controlstate[0] = 0;
    }
  }

  if (addHold){
    if(!controlstate[1]){
      sequenceNote(2);
      controlstate[1] = 1;
    }
  }
  else{
    if(controlstate[1]){
      controlstate[1] = 0;
    }
  }

  if (left){
    if(!controlstate[2]){
      octave = octave - 12;
      if (octave < 0){
        octave = 0;
      }
      controlstate[2] = 1;
    }
  }
  else{
    if(controlstate[2]){
      controlstate[2] = 0;
    }
  }

  if (right){
    if(!controlstate[3]){
      octave = octave + 12;
      if (octave > 84){
        octave = 84;
      }
      controlstate[3] = 1;
    }
  }
  else{
    if(controlstate[3]){
      controlstate[3] = 0;
    }
  }
}
