long ms_per_step = 1.0/(4.0*(bpm/60000.0));//1.0/(bpm/60000.0)ms/beat divided by 4steps/beat
long tempoMillis = millis();
int sequenceLoc = 0;
byte prevSequenceLoc = 255;
bool playSequence = 0;
bool playSequenceButtonPrev = 0;
bool eraseSequenceButtonPrev = 0;
byte seqSection = 0;
byte seqSectionPrev = 0;
byte seqDirection = 0;
byte seqDirectionPrev = 0;

void menuCheckSequencer() {
  if (screen != screenPrev){
    oled.fillScreen(BLACK);
    enc1Count = 0;
    enc1Change = 0;
    enc2Count = 0;
    enc2Change = 0;
    enc3Count = 0;
    enc3Change = 0;
    enc4Count = 0;
    enc4Change = 0;
    encoders[0] = 0;
    encoders[1] = 0;
    encoders[2] = 0;
    encoders[3] = 0;
    if(screen==0)enc2Count = bpm;
  }
  screenPrev = screen;
  switch (screen) {
    case 0:
      digitalWrite(enc2LED,HIGH);
      digitalWrite(enc3LED,HIGH);
      
      if (playSequenceButton and !playSequenceButtonPrev){
            playSequence = !playSequence;
            prevSequenceLoc = 21;
            for (byte hl = 0; hl < 12; hl++){
              oled.drawFastVLine((sequenceLoc-seqSection*numStepsOnScreen)*8,20+9*hl,8,BLACK);
              sample_envelope_bank[hl]->noteOff();
            }
            enc1Count = 0;
            enc1Change = 0;
            encoders[0] = 0;
            sequenceLoc = 0;
            tempoMillis = millis();
            oled.fillRect(0,13,125,6,BLACK);
          }
      playSequenceButtonPrev = playSequenceButton;
      
      switch (playSequence){
        case 0:
          digitalWrite(enc1LED,HIGH);
          //Parameter Scrolling
          enc1Change = encoders[0]-enc1Change;
          enc1Count = enc1Count + enc1Change;
          if (enc1Count < 0) enc1Count = 0;
          if (enc1Count > (numStepsInSequence-1)) enc1Count = (numStepsInSequence-1);
          if((enc1Count > sequenceLoc) or (enc1Count < sequenceLoc))prevSequenceLoc = sequenceLoc;
          sequenceLoc = enc1Count;
          enc1Change = encoders[0];
          color1 = RED;
        break;
        
        case 1:
          digitalWrite(enc1LED,LOW);
          if (millis()-tempoMillis > ms_per_step){
            prevSequenceLoc = sequenceLoc;
            switch (seqDirection){
              case 0:
                sequenceLoc = sequenceLoc+1;
              break;
              case 1:
                sequenceLoc = sequenceLoc-1;
              break;
              case 2:
                sequenceLoc = int(random(0,20));
              break;
            }
            if(sequenceLoc<0)sequenceLoc=(numStepsInSequence-1);
            if(sequenceLoc>(numStepsInSequence-1))sequenceLoc=0;
            tempoMillis = millis();
          }
          
          for (byte b = 0; b < 12; b++){
            if ((stepSequence[sequenceLoc][b]) and (!samplePad[b]) and (sampleIsPlaying[b]!=sequenceLoc) and (assigningNotPlaying[b]!=sequenceLoc)){
              flash_players[b]->play(samps[b].fileName);
              sample_envelope_bank[b]->noteOn();
              sampleIsPlaying[b]=sequenceLoc;
            }
            if(sequenceLoc!=assigningNotPlaying[b])assigningNotPlaying[b]=255;
            if(sequenceLoc!=sampleIsPlaying[b] and (!samplePad[b])){
              if(sample_envelope_bank[b]->isActive()){
                sample_envelope_bank[b]->noteOff();
              }
            }
            if(!sample_envelope_bank[b]->isActive() and (!samplePad[b])){
              flash_players[b]->stop();
            }
          }
          color1 = WHITE;
        break;
      }
      
      for (byte b = 0; b < 12; b++){
        if(mainSelect){
          if(samplePad[b] and !padPrev[b]){
            if (stepSequence[sequenceLoc][b]) oled.fillCircle(8*(sequenceLoc-seqSection*numStepsOnScreen),19+9*b,2,BLACK);
            else assigningNotPlaying[b] = sequenceLoc;
            stepSequence[sequenceLoc][b] = !stepSequence[sequenceLoc][b];
          }
        }
        padPrev[b]=samplePad[b];
      }
       
      if(eraseSequenceButton and !eraseSequenceButtonPrev){
        for (byte n = 0; n < numStepsInSequence; n++){
          for (byte b = 0; b < 12; b++){
            stepSequence[n][b]=0;
            oled.fillCircle(n*8,19+9*b,2,BLACK);
          }
        }
      }
      eraseSequenceButtonPrev=eraseSequenceButton;

      enc2Change = encoders[1]-enc2Change;
      enc2Count = enc2Count + enc2Change;
      if (enc2Count < 0) enc2Count = 0;
      if (enc2Count > 500) enc1Count = 500;
      bpm = enc2Count;
      if(bpm!=bpmPrev){
        ms_per_step = 1.0/(4.0*(bpm/60000.0));
        bpmPrev = bpm;
      }
      enc2Change = encoders[1];

      enc3Change = encoders[2]-enc3Change;
      enc3Count = enc3Count + enc3Change;
      if (enc3Count < 0) enc3Count = 0;
      if (enc3Count > 2) enc3Count = 2;
      if(enc3Count != seqDirection)oled.fillRect(0,13,125,6,BLACK);

      seqDirection = enc3Count;
      enc3Change = encoders[2];
      
      if(sequenceLoc<16) {
        if(seqSection == 1){
          oled.fillRect(0,13,125,6,BLACK);
          oled.drawFastVLine(127,19,109,BLACK);
          oled.drawFastVLine(0,19,109,BLACK);
          oled.fillTriangle(0,118,2,116,2,120,BLACK);
          oled.fillTriangle(0,19,2,17,2,21,BLACK);
          for (byte n = 0; n < numStepsInSequence; n++){
            for (byte b = 0; b < 12; b++){
              oled.fillCircle(n*8,19+9*b,2,BLACK);
            }
          }
        }
        seqSection = 0;
      }
      else {
        if(seqSection == 0){
          oled.fillRect(0,13,125,6,BLACK);
          oled.drawFastVLine(127,19,109,BLACK);
          oled.drawFastVLine(0,19,109,BLACK);
          oled.fillTriangle(127,118,125,116,125,120,BLACK);
          oled.fillTriangle(127,19,125,17,125,21,BLACK);
          for (byte n = 0; n < numStepsInSequence; n++){
            for (byte b = 0; b < 12; b++){
              oled.fillCircle(n*8,19+9*b,2,BLACK);
            }
          }
        }
        seqSection = 1;
      }   
    break;
  }
}

void staticMenuSequencer() {
  switch (screen) {
    case 0:
      //Write out header
      oled.setTextSize(1);
      oled.setTextColor(WHITE,BLACK);
      oled.setCursor(22, 2);
      oled.print(F("Step Sequencer"));
      oled.drawFastHLine(0,10,128, WHITE);
      //oled.fillTriangle(127,10,124,13,124,7,PURPLE);
      byte cursorXLoc = (sequenceLoc-seqSection*numStepsOnScreen)*8;
      byte clearXLoc = (prevSequenceLoc-seqSection*numStepsOnScreen)*8;
      switch(seqSection)
      {
        case 0:
          for (byte hl = 0; hl < 12; hl++){
            byte yloc = 19+9*hl;
            oled.drawFastHLine(0,yloc,128,DARKGREY);
            if(hl!=11){
              oled.drawFastVLine(cursorXLoc,yloc+1,8,color1);
              oled.drawFastVLine(clearXLoc,yloc+1,8,BLACK);
            }
            for (byte b = 0; b < numStepsOnScreen; b++){
              byte xloc = b*8;
              if(b%4==0)color2 = LIGHTGREY;
              else color2 = DARKGREY;
              if((b != (sequenceLoc-seqSection*numStepsOnScreen))and(hl!=11))oled.drawFastVLine(xloc,yloc,9,color2);
              if (stepSequence[b+numStepsOnScreen*seqSection][hl])oled.fillCircle(xloc,yloc,2,MAGENTA);
            }
          }
          oled.fillTriangle(127,118,125,116,125,120,LIGHTGREY);
          oled.fillTriangle(127,19,125,17,125,21,LIGHTGREY);
        break;
        case 1:
          for (byte hl = 0; hl < 12; hl++){
            byte yloc = 19+9*hl;
            oled.drawFastHLine(0,yloc,128,DARKGREY);
            if(hl!=11){
              oled.drawFastVLine(cursorXLoc,yloc+1,8,color1);
              oled.drawFastVLine(clearXLoc,yloc+1,8,BLACK);
              oled.drawFastVLine(127,yloc+1,8,DARKGREY);
            }
            for (byte b = 0; b < numStepsOnScreen; b++){
              byte xloc = b*8;
              if(b%4==0)color2 = LIGHTGREY;
              else color2 = DARKGREY;
              if((b != (sequenceLoc-seqSection*numStepsOnScreen))and(hl!=11)and(b!=0))oled.drawFastVLine(xloc,yloc,9,color2);
              if (stepSequence[b+numStepsOnScreen*seqSection][hl])oled.fillCircle(xloc,yloc,2,MAGENTA);
            }
          }
          oled.fillTriangle(0,118,2,116,2,120,LIGHTGREY);
          oled.fillTriangle(0,19,2,17,2,21,LIGHTGREY);
        break;
      }
      
      switch (seqDirection){
        case 0:
          oled.fillTriangle(cursorXLoc-1,19,cursorXLoc-1,13,cursorXLoc+3-1,16,BLUE);
          oled.fillTriangle(clearXLoc-1,19,clearXLoc-1,13,clearXLoc+3-1,16,BLACK);
          oled.fillRect(0,121,25,8,BLACK);
        break;
        case 1:
          oled.fillTriangle(cursorXLoc-1,19,cursorXLoc-1,13,cursorXLoc-3-1,16,BLUE);
          oled.fillTriangle(clearXLoc-1,19,clearXLoc-1,13,clearXLoc-3-1,16,BLACK);
          oled.fillRect(0,121,25,8,BLACK);
        break;
        case 2:
          oled.fillRect(cursorXLoc-3,13,7,6,BLACK);
          oled.setCursor(0,121);
          oled.setTextColor(BLUE,BLACK);
          oled.print(F("RAND"));
        break;
      }
      
      oled.setCursor(37,121);
      oled.setTextColor(GREEN,BLACK);
      oled.print(bpm);
      oled.setTextColor(WHITE,BLACK);
      oled.print(F("BPM"));
    break;
  }
}
