// Overall Navigation Variables
const byte numMenus = 4;
bool selectedPrev = false;
bool menuSelectPrev = false;
int8_t menuCount = 0;
int menuChange = 0;
int8_t valCount = 0;
int valChange = 0;

//Sequencer Navigation Variables
byte chanPrev = 1;
int bpmChange = 0;
bool bpmSelectPrev = false;
bool holdSequencePrev = false;
bool eraseSequencePrev = false;

//Recorder Navigation Variables
byte prevScreenSelect = 0;
const byte onScreenItems = 4;
byte topItem = 1;
int8_t menuCountPrev = 0;
int8_t dbCount = 0;
int dbChange = 0;
int outputGainChange = 0;
bool selectInputPrev = 0;
byte inputMethod = 0;
bool startOrEndPrev = 0;
byte scrubAdjust = 50;
float playPosition = 0;
bool recordSelectPrev = 0;

//Metronome Navigation Variables
bool metronomeEnableSelectPrev = 0;
bool armLocation = 0;

void menuCheck() {
  //Change main function and reset controls
  if (menuSelect and !menuSelectPrev){
    Serial.println("changed menus");
    menuScreen = menuScreen + 1;
    if (menuScreen > numMenus){
      menuScreen = 1;
    }
    menuCount = 0;
    menuChange = 0;
    bpmChange = 0;
    valCount = 0;
    valChange = 0;
    encoders[0] = 0;
    encoders[1] = 0;
    encoders [2] = 0;
    selected = false;
  }
  menuSelectPrev = menuSelect;

  //Actions for Wavetable Synthesis Menu
  if (menuScreen == 1){
    //Menu Scrolling
    menuChange = encoders[0]-menuChange;
    menuCount = menuCount + menuChange;
    if (menuCount > 4){
      menuCount = 0;
    }
    if (menuCount < 0){
      menuCount = 4;
    }
    menuChange = encoders[0];

    //Selecting Instruments
    if (click1 and !selectedPrev){
      if (selected){
        selected = false;
      }
      else{
        selected = true;
      }
    }
    selectedPrev = click1;
  
    if (selected){
      chan = menuCount + 1;
      if (chan != chanPrev){
        for (int w; w < TOTAL_VOICES; w++){
          wavetable[w].stop();
        }
      }
    }

    //Adjust input gain
    valChange = encoders[1]-valChange;
    currentInputGain = currentInputGain + 0.05*valChange;
    if (currentInputGain < 0) currentInputGain = 0;
    if (currentInputGain > 1.0) currentInputGain = 1.0;
    currentVelocity = currentInputGain*127.0;
    valChange = encoders[1];
  }

  //Actions for Sequencer Menu
  if (menuScreen == 2){
    //Scroll Thru Sequencer Slots
    menuChange = encoders[0]-menuChange;
    menuCount = menuCount + menuChange;
    if (menuCount > numSequences-1){
      menuCount = 0;
    }
    if (menuCount < 0){
      menuCount = numSequences-1;
    }
    menuChange = encoders[0];
    if (currentSequence != menuCount){
      currentSequence = menuCount;
      valCount= seqs[currentSequence].timeSignature;
    }

    //Scroll through note lengths
    valChange = encoders[1]-valChange;
    valCount = valCount + valChange;
    if (valCount > numTSigs-1){
      valCount = 0;
    }
    if (valCount < 0){
      valCount = numTSigs-1;
    }
    valChange = encoders[1];
    seqs[currentSequence].timeSignature = valCount;

    //Toggle hold
    if (holdSequenceSelect and !holdSequencePrev){
      if (holdSequence[currentSequence]){
        holdSequence[currentSequence] = false;
      }
      else{
        holdSequence[currentSequence] = true;
      }
    }
    holdSequencePrev = holdSequenceSelect;

    //Erase sequencs slot
    if (eraseSequenceSelect and !eraseSequencePrev){
      if (!eraseSequence[currentSequence]){
        eraseSequence[currentSequence] = true;
        eraseSequenceNum(currentSequence);
        eraseSequence[currentSequence] = false;
      }
    }
    eraseSequencePrev = eraseSequenceSelect;

    if (click3 and !bpmSelectPrev){
      if (bpmSelect){
        bpmSelect = false;
      }
      else{
        bpmSelect = true;
      }
    }
    bpmSelectPrev = click3;
    
    if (bpmSelect){
      bpmChange = encoders[2]-bpmChange;
      bpm = bpm + bpmChange;
      if (bpm < 0) bpm = 0;
      bpmChange = encoders[2];
      ms_per_beat = 1.0/(bpm/60000.0);
    }
  }

  //Actions for Recorder Menu
  if (menuScreen == 3){
    //Toggle between recorder screens 
    if (click1 and !prevScreenSelect){
      //If in editor, return to list
      if (currentScreen_Recorder == 1){
        playRaw1.stop();
        currentScreen_Recorder = 0; 
      }
      //If in list, enter editor
      else if (currentScreen_Recorder == 0){
        currentRecording = menuCount;
        if (SD.exists(recs[currentRecording].fileName)) {
          playRaw1.play(recs[currentRecording].fileName,0);
          recs[currentRecording].fileSize = playRaw1.lengthMillis();
          playRaw1.stop();
          currentEndTime = recs[currentRecording].fileSize;
        }
        else{
          currentEndTime = 0;
        }
        currentStartTime = 0;
        currentScreen_Recorder = 1;
      }
      currentRecording = menuCount;
      playPosition = 0;
      outputGain = 1;
      menuCount = 0;
      topItem = 1;
      menuChange = 0;
      encoders[0] = 0;
      encoders[1] = 0;
      encoders[2] = 0;
    }
    prevScreenSelect = click1; 

    //Actions for Recording List Screen
    if (currentScreen_Recorder == 0){
      //Scroll through recordings
      menuChange = encoders[0]-menuChange;
      menuCount = menuCount + menuChange;
      if (menuCount >= numRecordFiles){
        menuCount = numRecordFiles-1;
      }
      if (menuCount < 0){
        menuCount = 0; 
        topItem = 1;
      }
      if ((menuCount%onScreenItems == 0) and (menuCountPrev < menuCount)){
        topItem = 1+menuCount;
      }
      else if ((menuCount%onScreenItems == 3) and (menuCountPrev > menuCount)){
        topItem = menuCount-(onScreenItems-2);
      }
      menuCountPrev = menuCount;
      menuChange = encoders[0];
    }

    //Actions for Recording Editor Screen
    if (currentScreen_Recorder == 1){
      //Adjust recording output gain
      outputGainChange = encoders[0]-outputGainChange;
      outputGain = outputGain + 0.1*outputGainChange;
      if (outputGain > 9.90){https://manual.audacityteam.org/index.html
        outputGain = 9.90;
      }
      if (outputGain < 0){
        outputGain = 0;
      }
      outputGainChange = encoders[0];

      //Choose trim mode
      if (click2 and !startOrEndPrev){
        if (startOrEndSelect==0){
          startOrEndSelect = 1;
          scrubAdjust = 200;
        }
        else if (startOrEndSelect==1){
          startOrEndSelect = 2;
          scrubAdjust = 50;
          encoders[1]=0;
          valChange = 0; 
        }
        else if (startOrEndSelect==2){
          startOrEndSelect = 3;
          scrubAdjust = 200;
        }
        else if (startOrEndSelect==3){
          startOrEndSelect = 0;
          scrubAdjust = 50;
          encoders[1]=0;
          valChange = 0; 
        }
      }
      startOrEndPrev = click2;

      //Trim Recording
      if (startOrEndSelect==0 or startOrEndSelect==1){
        valChange = encoders[1]-valChange;
        currentStartTime = currentStartTime + scrubAdjust*valChange;
        if (currentStartTime > recs[currentRecording].fileSize){
          currentEndTime = recs[currentRecording].fileSize;
        }
        if (currentStartTime > currentEndTime){
          currentEndTime = currentStartTime;
        }
        if (currentStartTime < 0){
          currentStartTime = 0;
        }
        valChange = encoders[1];
      }
      else if (startOrEndSelect==2 or startOrEndSelect==3) { 
        valChange = encoders[1]-valChange;
        currentEndTime = currentEndTime + scrubAdjust*valChange;
        if (currentEndTime > recs[currentRecording].fileSize){
          currentEndTime = recs[currentRecording].fileSize;
        }
        if (currentEndTime < currentStartTime){
          currentStartTime = currentEndTime;
        }
        if (currentEndTime < 0){
          currentEndTime = 0;
        }
        valChange = encoders[1];
      }

      //Toggle between recording inputs
      if (click3 and !selectInputPrev){
        if (inputMethod == 0){
          inputMethod = 1;
          sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
          record_output_mixer.gain(1,1);
        }
        else if (inputMethod == 1){
          inputMethod = 2;
          turnOffLEDs();
          record_output_mixer.gain(1,0);
        }
        else if (inputMethod == 2){
          inputMethod = 0;
          turnOffLEDs();
          sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
          record_output_mixer.gain(1,0);
        } 
      }
      selectInputPrev = click3;

      if (recordButton and !recordSelectPrev){
        if (recordSelect){
          recordSelect = false;
        }
        else{
          recordSelect = true;
        }
      }
      recordSelectPrev = recordButton;

      //Adjust microphone input gain
      if(inputMethod == 0){
        dbChange = encoders[2]-dbChange;
        microphoneGain = microphoneGain + dbChange;
        if (microphoneGain > 63){
          microphoneGain = 63;
        }
        if (microphoneGain < 0){
          microphoneGain = 0;
        }
        dbChange = encoders[2];
      }
    }
  }

  //Actions for Metronome Menu
  if (menuScreen == 4){
    //Toggle Metronome 
    if (click1 and !metronomeEnableSelectPrev){
      if (metronomeEnable == 2){
        metronomeEnable = 0;
        metronome.stop();
      }
      else if (metronomeEnable == 0){
        metronomeEnable = 1;
      }
      else if (metronomeEnable == 1){
        metronomeEnable = 2;
      }
    } 
    metronomeEnableSelectPrev = click1;

    //Adjust system bpm
    bpmChange = encoders[0]-bpmChange;
    bpm = bpm + bpmChange;
    if (bpm < 0) bpm = 0;
    bpmChange = encoders[0];
    ms_per_beat = 1.0/(bpm/60000.0);
    
  }
  Serial.println(bpmChange);
}

void staticMenu() {
  display.clearDisplay();

  //Graphics for Wavetable Synthesis Menu
  if (menuScreen == 1){
    //Write out header
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(35, 2);
    display.print("Instrument");
    display.drawLine(0,10,127,10, WHITE);
    display.drawLine(16,0,16,10, WHITE);
    display.drawLine(0,0,0,10, WHITE);
    display.drawLine(0,0,16,0, WHITE);
    
    //Write out Instrument Names
    display.setTextSize(1);
    display.setCursor(10, 15);
    if (chan == 1){
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else{
      display.setTextColor(SSD1306_WHITE);
    }
    display.println("Piano");
  
    display.setCursor(10, 27);
    if (chan == 2){
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else{
      display.setTextColor(SSD1306_WHITE);
    }
    display.println("Dist. Guitar");
  
    display.setCursor(10,39);
    if (chan == 3){
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else{
      display.setTextColor(SSD1306_WHITE);
    }
    display.println("Ocarina");
  
    display.setCursor(10, 51);
    if (chan == 4){
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else{
      display.setTextColor(SSD1306_WHITE);
    }
    display.println("Drums");
  
    display.setCursor(10, 63);
    if (chan == 5){
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else{
      display.setTextColor(SSD1306_WHITE);
    }
    display.println("Pizzicato");
    display.setTextColor(SSD1306_WHITE);

    //Show Cursor
    display.setCursor(2, 15+((menuCount) * 12));
    display.println(">");

    //Show octave
    display.setTextSize(1);
    display.setCursor(3, 2);
    display.setTextColor(SSD1306_WHITE);
    display.println(octave);

    //Show Input Gain
    if (currentInputGain <= 1.0){
      int circleLoc = 59.0-currentInputGain*44.0;
      display.drawLine(122,59,122,circleLoc, WHITE);
      display.fillCircle(122, circleLoc, 3, SSD1306_WHITE);
    }
    else{
      display.drawLine(122,59,122,23, WHITE);
      display.drawLine(100,23,122,23, WHITE);
      display.setCursor(100, 15);
      display.print(currentInputGain);
    }
  }

  //Graphics for Sequencer Menu
  if (menuScreen == 2){
    //Write out header
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(30, 0);
    display.print("Sequencer ");
    display.println(currentSequence+1);
    display.drawLine(0,10,127,10, WHITE);

    //Show if recording
    if (recordSequenceSelect){
      display.setCursor(33, 15);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.println("RECORDING");
      display.setTextColor(SSD1306_WHITE);
    }
    else{     
      display.setCursor(52, 15);
      display.print("1/");
      display.println(int(tSigs[seqs[currentSequence].timeSignature]));
    }

    //Show if hold applied
    if (holdSequence[currentSequence]){
      display.setCursor(10, 36);
      display.setTextColor(SSD1306_WHITE);
      display.println("HOLD");
    }

    //Show sequence note number
    display.setTextSize(4);
    if (sequenceCounter[currentSequence] < 10){
      display.setCursor(50, 30);
      if (sequencePlayingCheck and sequenceCounter[currentSequence]==0){
        display.println(sequenceLength[currentSequence]);
      }
      else{
        display.println(sequenceCounter[currentSequence]);
      }
    }
    else{
      display.setCursor(38, 30);
      display.println(sequenceCounter[currentSequence]);
    }

    //Show BPM
    if (bpmSelect){
      display.clearDisplay();
      display.setTextSize(3);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(30, 20);
      display.print(int(bpm));
      display.setTextSize(1);
      display.print(" BPM");
    }
    else{
      display.setTextSize(1);
      display.setCursor(110, 36);
      display.setTextColor(SSD1306_WHITE);
      display.println(int(bpm));
    }

    //Show octave
    display.setTextSize(1);
    display.setCursor(110, 48);
    display.setTextColor(SSD1306_WHITE);
    display.println(octave);
  }

  //Graphics for Recorder Menu
  if (menuScreen == 3){
    //Graphics for Recording List Screen
    if (currentScreen_Recorder == 0){
      //Show title
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(32, 0);
      display.print("Recordings");
      display.drawLine(0,10,127,10, WHITE);

      //Scroll displayed items
      for (int i = 0; i < onScreenItems; i++){
        if ((i+topItem-1)<numRecordFiles){
          display.setCursor(10, 15+(i*12));
          display.print(i+topItem);
          display.print(". ");
          if (SD.exists(recs[i+topItem-1].fileName)) {
            display.print(recs[i+topItem-1].fileName);
          }
          else {
            display.println("NONE");
          }
        }
      }

      //Show cursor
      display.setCursor(2, (15+(menuCount%onScreenItems * 12)));
      display.println(">");
    }
    
    //Actions for Recording Editor Screen
    if (currentScreen_Recorder == 1){
      //Show slot number
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(4, 2);
      display.print("Slot ");
      display.print(currentRecording+1);
      display.drawLine(40,0,40,10, WHITE);
      display.drawLine(0,10,127,10, WHITE);
      display.drawLine(0,0,40,0, WHITE);
      display.drawLine(0,0,0,10, WHITE);

      //Show output gain
      display.setCursor(90, 2);
      display.print("G ");
      display.print(outputGain);

      //Show if 'key bind' selected
      if (keyBindSelect){
        display.setCursor(40, 20);
        display.setTextSize(2);
        display.println("BIND");
        display.setTextSize(1);
      }
      //Show if 'key unbind' selected
      else if (keyUnbindSelect){
        display.setCursor(30, 20);
        display.setTextSize(2);
        display.println("UNBIND");
        display.setTextSize(1);
      }
      //Show recording input source
      else{
        if (inputMethod == 1){
          display.setCursor(12, 15);
          display.println("Source: Line-In");
          display.setCursor(12, 27);
          display.print("Pass-Through");
          recs[currentRecording].sourceType = inputMethod;
        }
        else if (inputMethod == 2){
          display.setCursor(12, 15);
          display.println("Source: Internal");
          recs[currentRecording].sourceType = inputMethod;
        }
        else if (inputMethod == 0){     
          display.setCursor(12, 15);
          display.println("Source: Microphone");
          display.setCursor(24, 27);
          display.print("Gain: ");
          display.print(microphoneGain);
          display.print("dB");
          recs[currentRecording].sourceType = inputMethod;
        }
      }

      //Show if recording
      if (recordSelect){
        display.setCursor(8, 40);
        display.setTextSize(2);
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.println("RECORDING");
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
      }
      //Show progress bar
      else{
        display.drawLine(10,50,117,50, WHITE);
        if (showPlaying) display.drawLine(10+(playPosition*107),55,10+(playPosition*107),45, WHITE);
        float startMarker = (1.0*currentStartTime)/(1.0*recs[currentRecording].fileSize);
        float endMarker = (1.0*currentEndTime)/(1.0*recs[currentRecording].fileSize);
        display.drawLine(10+(startMarker*107),55,10+(startMarker*107),45, WHITE);
        display.drawLine(10+(endMarker*107),55,10+(endMarker*107),45, WHITE);
        if (startOrEndSelect==0){
          display.setCursor(8+(startMarker*107), 55);
          display.println("L");
        }
        else if (startOrEndSelect==1){
          display.setCursor(8+(startMarker*107), 55);
          display.println("H");
        }
        else if (startOrEndSelect==2) {
          display.setCursor(8+(endMarker*107), 55);
          display.println("L");
        }
        else if (startOrEndSelect==3) {
          display.setCursor(8+(endMarker*107), 55);
          display.println("H");
        }
      }
    }
  }

  //Graphics for Sequencer Menu
  if (menuScreen == 4){
    //Write out header
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(38, 0);
    display.print("Metronome");
    display.drawLine(0,10,127,10, WHITE);
    display.drawLine(64,10,64,63, WHITE);
    display.drawLine(0,10,0,63, WHITE);
    display.drawLine(0,63,127,63, WHITE);
    display.fillRect(64,10,127,63, SSD1306_WHITE);

    //Show BPM readout
    display.setTextSize(2);
    display.setCursor(14, 22);
    display.print(int(bpm));
    display.setTextSize(2);
    display.setCursor(14, 37);
    display.print("BPM");
    display.setTextSize(1);
    

    //Show metronome animation
    if (metronomeEnable == 2){
      if (armLocation){
        display.drawLine(96,63,76,20, BLACK);
      }
      else{
        display.drawLine(96,63,116,20, BLACK);  
      }
    }
    else if (metronomeEnable == 1){
      display.setTextSize(2);
      display.setCursor(81, 29);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.print("TAP");
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
    }
    else if (metronomeEnable == 0){
      display.setTextSize(2);
      display.setCursor(81, 29);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.print("OFF");
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
    }
  }
  display.display();
}
