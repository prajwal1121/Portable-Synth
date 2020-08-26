bool keystate[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte keyMode[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool controlstate[4] = {0,0,0,0};

void playKeyboard(){   
  for (int i = 0; i < 24; i++){
    current_byte = i/8;
    current_button = i-8*current_byte;
    if (bitRead(buttonStates[current_byte], current_button)){
      if (!keystate[i]){
        //Bind key to recording
        if (keyBindSelect){
          pk[i].fileNum= currentRecording;
          pk[i].startTime = currentStartTime;
          pk[i].endTime = currentEndTime;
          pk[i].mixerGain = outputGain;
          keyMode[i] = 1;
        }
        //Free key from recording
        if (keyUnbindSelect){
          keyMode[i] = 0;
        }
        if (keyMode[i] == 1) startPlaying(i);
        if (keyMode[i] == 2) continuePlaying(i);

        //If on tap tempo mode, dedicate entire keyboard
        if (metronomeEnable == 1){
          tapMetronome();
        }
        else{
          //If free, play instrument
          if (!keyMode[i]){
          OnNoteOn(chan,i+octave,100);
          sequenceNote(i+octave);
          }
        }
        keystate[i] = 1;
      }
    }
    else{
      if (keystate[i]){
        if (keyMode[i] == 2) stopPlaying(i);
        OnNoteOff(chan,i+octave,100);
        keystate[i] = 0;
      }
    }
    if (keyMode[i] == 2) continuePlaying(i);
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

void startPlaying(byte key) {
  record_output_mixer.gain(0,pk[key].mixerGain);
  playRaw1.play(recs[pk[key].fileNum].fileName,pk[key].startTime);
  keyMode[key] = 2;
}

void continuePlaying(byte key) {
  if (!playRaw1.isPlaying()) {
    //playRaw1.stop();
    keyMode[key] = 1; 
    startPlaying(key);
  }
  
  if (pk[key].fileNum == currentRecording){
    showPlaying = true;
    playPosition = (1.0*playRaw1.positionMillis())/(1.0*recs[currentRecording].fileSize);
  }
  
  if (playRaw1.positionMillis() >= pk[key].endTime){
    //playRaw1.stop();
    keyMode[key] = 1; 
    startPlaying(key);
  }
}

void stopPlaying(byte key) {
  byte sum = 0;
  for (byte i = 0; i<24; i++){
    if (keyMode[i] == 2) sum ++;
  }
  if (sum <= 1){ 
    playRaw1.stop();
    showPlaying = false;
  }
  keyMode[key] = 1;
}
