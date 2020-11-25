const byte numMenus = 2;
byte chanPrev = 1;

bool selectedPrev = false;
bool menuSelectPrev = false;

int8_t menuCount = 0;
int menuChange = 0;

int8_t valCount = 0;
int valChange = 0;

float bpmCount = bpm;
int bpmChange = 0;
bool bpmSelectPrev = false;

bool holdSequencePrev = false;

bool eraseSequencePrev = false;

void menuCheck() {
  if (menuSelect and !menuSelectPrev){
    menuScreen = menuScreen + 1;
    if (menuScreen > numMenus){
      menuScreen = 1;
    }
    menuCount = 0;
    menuChange = 0;
    encoders[0] = 0;
    valCount = 0;
    valChange = 0;
    encoders[1] = 0;
    selected = false;
  }
  menuSelectPrev = menuSelect; 

  if (click3 and !bpmSelectPrev){
    if (bpmSelect){
      bpmSelect = false;
    }
    else{
      bpmSelect = true;
    }
  }
  bpmSelectPrev = click3;
  bpmChange = encoders[2]-bpmChange;
  bpmCount = bpmCount + bpmChange;
  bpmChange = encoders[2];
  if (bpmSelect){
    bpm = bpmCount;
    ms_per_beat = 1.0/(bpm/60000.0);
  }

  if (menuScreen == 1){
    menuChange = encoders[0]-menuChange;
    
    menuCount = menuCount + menuChange;
    if (menuCount > 4){
      menuCount = 0;
    }
    if (menuCount < 0){
      menuCount = 4;
    }
    menuChange = encoders[0];
  
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
  }

  if (menuScreen == 2){
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

    if (holdSequenceSelect and !holdSequencePrev){
      if (holdSequence[currentSequence]){
        holdSequence[currentSequence] = false;
      }
      else{
        holdSequence[currentSequence] = true;
      }
    }
    holdSequencePrev = holdSequenceSelect;

    if (eraseSequenceSelect and !eraseSequencePrev){
      if (!eraseSequence[currentSequence]){
        eraseSequence[currentSequence] = true;
        eraseSequenceNum(currentSequence);
        eraseSequence[currentSequence] = false;
      }
    }
    eraseSequencePrev = eraseSequenceSelect;
  }
}

void staticMenu() {
  if (menuScreen == 1){
    display.clearDisplay();
    display.setTextSize(1);

    display.setCursor(10, 0);
    if (chan == 1){
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else{
      display.setTextColor(SSD1306_WHITE);
    }
    display.println("Distortion Guitar");
  
    display.setCursor(10, 12);
    if (chan == 2){
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else{
      display.setTextColor(SSD1306_WHITE);
    }
    display.println("Piano");
  
    display.setCursor(10,24);
    if (chan == 3){
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else{
      display.setTextColor(SSD1306_WHITE);
    }
    display.println("Ocarina");
  
    display.setCursor(10, 36);
    if (chan == 4){
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else{
      display.setTextColor(SSD1306_WHITE);
    }
    display.println("Drums");
  
    display.setCursor(10, 48);
    if (chan == 5){
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else{
      display.setTextColor(SSD1306_WHITE);
    }
    display.println("Pizzicato");
  
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(2, ((menuCount) * 12));
    display.println(">");
  }

  if (menuScreen == 2){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(30, 0);
    display.print("Sequencer ");
    display.println(currentSequence+1);
    display.drawLine(0,10,127,10, WHITE);

    if (recordSelect){
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
    
    if (holdSequence[currentSequence]){
      display.setCursor(10, 36);
      display.setTextColor(SSD1306_WHITE);
      display.println("HOLD");
    }
    
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
  }

  display.setTextSize(1);
  display.setCursor(110, 48);
  display.setTextColor(SSD1306_WHITE);
  display.println(octave);

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
  
  display.display();
}
