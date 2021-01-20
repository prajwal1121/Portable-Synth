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

int enc4Count = 0;
int enc4Change = 0;

bool rightPrev = 0;
bool leftPrev = 0;
int8_t recSource = 0;

int16_t color1 = WHITE;
int16_t color2 = WHITE;

bool radioOn = 0;
long last_time_rds_update = millis();
bool monitoringOn = 0;

byte microphoneGain = 36;
byte lineInGain = 5;
bool gainInitialized = 0;
byte circleLoc = 0;
byte recordStatus = 0;
bool recordButtonPrev = 0;
bool eraseButtonPrev = 0;
bool storeButtonPrev = 0;
bool selectButtonPrev = 0;
unsigned long currentStartTime = 0;

bool draw = 1;

File recFile;
const byte onScreenItems = 11;
byte topItem = 1;
byte topItemPrev = 1;
bool directoryDisplayed = 0;
byte chosenFile = 0;
bool previewStatus = 0;
bool fileErasePrompt = 0;

void menuCheckRecorder() {
  //Initialize encoder for mic gain
  if(screen==0 and recSource==0 and !gainInitialized){
    codec.inputSelect(AUDIO_INPUT_MIC);
    enc1Count = 36;
    gainInitialized = 1;
    screen = 1;
  }
  
  switch (screen) {
    case 0://list files
      enc1Change = encoders[0]-enc1Change;
      enc1Count = enc1Count + enc1Change;
      if (enc1Count>numRecFiles-1) enc1Count= numRecFiles-1;
      if (enc1Count < 0){
        enc1Count = 0; 
        topItem = 1;
      }
      if ((int(enc1Count)%onScreenItems == 0) and (enc1CountPrev < enc1Count)){
        topItemPrev = topItem;
        topItem = 1+enc1Count;
        directoryDisplayed = 0;
        oled.fillRect(0,11,128,118,BLACK);
        draw = 1;
      }
      else if ((int(enc1Count)%onScreenItems == onScreenItems-1) and (enc1CountPrev > enc1Count)){
        topItemPrev = topItem;
        topItem = enc1Count-(onScreenItems-2);
        directoryDisplayed = 0;
        oled.fillRect(0,11,128,118,BLACK);
        draw = 1;
      }
      if (enc1Count != enc1CountPrev)draw = 1;
      chosenFile = enc1Count;
      enc1CountPrev = enc1Count;
      enc1Change = encoders[0];

      if (previewButton and !previewStatus){
        AudioNoInterrupts();
        currentDirectory = SD.open("/Recs");
        currentDirectory.rewindDirectory();
        File entry =  currentDirectory.openNextFile();
        for (byte f = 0; f <chosenFile; f++){
          entry.close();
          entry =  currentDirectory.openNextFile();
        }
        entry.getName(entryNameBuff,15);
        strcpy(previewNameBuff,"/Recs/");
        strcat(previewNameBuff,entryNameBuff);
        entry.close();     
        currentDirectory.close();
        AudioInterrupts();
        startPlayingPreview();
        previewStatus = 1;
      }     
      else if(previewButton and previewStatus){
        previewStatus = 1;
      }
      else if(!previewButton and previewStatus){
        previewStatus = 0;
        stopPlayingPreview();
      }

      if (eraseButton and !menuSelect and !eraseButtonPrev){
        fileErasePrompt = 1;
        draw = 1;
      }
      else if (eraseButton and menuSelect and !selectButtonPrev){
        fileErasePrompt = 0;
        currentDirectory = SD.open("/Recs");
        currentDirectory.rewindDirectory();
        File entry =  currentDirectory.openNextFile();
        for (byte f = 0; f <chosenFile; f++){
          entry.close();
          entry =  currentDirectory.openNextFile();
        }
        entry.getName(entryNameBuff,15);
        strcpy(previewNameBuff,"/Recs/");
        strcat(previewNameBuff,entryNameBuff);
        entry.close();     
        currentDirectory.close();
        if(SD.remove(previewNameBuff))numRecFiles = numRecFiles - 1;
        directoryDisplayed = 0;
        oled.fillRect(0,11,128,118,BLACK);
        draw = 1;
      }
      else if(!eraseButton and fileErasePrompt){
        fileErasePrompt = 0;
        draw = 1;
      }
      eraseButtonPrev = eraseButton;
      selectButtonPrev = menuSelect;

      enc4Change = encoders[3]-enc4Change;
      if (enc4Change>0){
        enc1Change = 0;
        encoders[0] = 0;
        switch (recSource){
          case 0:
            enc1Count = microphoneGain;
          break;
          case 1:
            enc1Count = lineInGain;
          break;
          case 2:
            enc1Count = lineInGain;
          break;
        }
        oled.fillScreen(BLACK);
        screen = 1;
        draw = 1;
      }
      enc4Change = encoders[3];
    break;
    
    case 1://rec screen
      if (right and !rightPrev){
        enc1Count = 0;
        enc1Change = 0;
        encoders[0] = 0;
        oled.fillRect(102, 119,25,8,BLACK);
        recSource = recSource + 1;
        if (recSource>3)recSource=3;
        switch(recSource){
          case(0):
            codec.inputSelect(AUDIO_INPUT_MIC);
            enc1Count = microphoneGain;
            codec.micGain(microphoneGain);
            radio.setVolume(0);
            screen = 1;
          break;
          case(1):
            codec.inputSelect(AUDIO_INPUT_LINEIN);
            enc1Count = lineInGain;
            codec.lineInLevel(lineInGain);
            radio.setVolume(0);
            screen = 1;
          break;
          case(2):
            codec.inputSelect(AUDIO_INPUT_LINEIN);
            enc1Count = lineInGain;
            codec.lineInLevel(lineInGain);
            if(radioOn) radio.setVolume(15);
            else radio.setVolume(0);
            screen = 1;
          break;
          case(3):
            screen = 2;
            oled.fillScreen(BLACK);
            draw = 1;
          break;
        }
        oled.fillRect(61,21,49,9,BLACK);
        draw = 1;
      }
      rightPrev = right;
      
      if (left and !leftPrev){
        enc1Count = 0;
        enc1Change = 0;
        encoders[0] = 0;
        oled.fillRect(102, 119,25,8,BLACK);
        recSource = recSource - 1;
        if (recSource<0)recSource=0;
        switch(recSource){
          case(0):
            codec.inputSelect(AUDIO_INPUT_MIC);
            enc1Count = microphoneGain;
            codec.micGain(microphoneGain);
            radio.setVolume(0);
            screen = 1;
          break;
          case(1):
            codec.inputSelect(AUDIO_INPUT_LINEIN);
            enc1Count = lineInGain;
            codec.lineInLevel(lineInGain);
            radio.setVolume(0);
            screen = 1;
          break;
          case(2):
            codec.inputSelect(AUDIO_INPUT_LINEIN);
            enc1Count = lineInGain;
            codec.lineInLevel(lineInGain);
            if(radioOn) radio.setVolume(15);
            else radio.setVolume(0);
            screen = 1;
          break;
          case(3):
            screen = 2;
            oled.fillScreen(BLACK);
            draw = 1;
          break;
        }
        oled.fillRect(61,21,49,9,BLACK);
        draw = 1;
      }
      leftPrev = left;

      if (click2 and !click2Prev){
        switch(monitoringOn){
          case 0:
            monitoringOn = 1;
            inputGain = 0.25;
            input_mixer.gain(0,inputGain);
            input_mixer.gain(1,inputGain);
          break;
          case 1:
            monitoringOn = 0;
            inputGain = 0.0;
            input_mixer.gain(0,inputGain);
            input_mixer.gain(1,inputGain);
          break;
        }
        draw = 1;
      }
      click2Prev = click2;

      enc1Change = encoders[0]-enc1Change;
      enc1Count = enc1Count + enc1Change;
      switch(recSource){
          case(0)://Mic
            if (enc1Count<0) enc1Count= 0;
            if (enc1Count>62) enc1Count= 62;
            if (microphoneGain != enc1Count)draw = 1;
            microphoneGain = enc1Count;
            codec.micGain(microphoneGain);
          break;
          case(1):
            if (enc1Count<0) enc1Count= 0;
            if (enc1Count>15) enc1Count= 15;
            if (lineInGain != enc1Count)draw = 1;
            lineInGain = enc1Count;
            codec.lineInLevel(lineInGain);
          break;
          case(2):
            if (enc1Count<0) enc1Count= 0;
            if (enc1Count>15) enc1Count= 15;
            if (lineInGain != enc1Count)draw = 1;
            lineInGain = enc1Count;
            codec.lineInLevel(lineInGain);
          break;
          case(3):
          break;
      }
      enc1Change = encoders[0];

      if (recordButton and !recordButtonPrev){
        switch(recordStatus){
          case 0://Idle
            oled.fillCircle(61,61,26,BLACK);
            recordStatus = 1;
            startRecording();
          break;
          case 1://Recording
            stopRecording();
          break;
        }
        draw = 1;
      }
      recordButtonPrev = recordButton;
  
      if (previewButton and recordStatus==0){
        oled.fillCircle(61,61,26,BLACK);
        recordStatus = 2;
        startPlayingPreview();
        draw = 1;
      }
      else if(previewButton and recordStatus==2){
        recordStatus = 2;
      }
      else if(!previewButton and recordStatus==2){
        recordStatus = 0;
        stopPlayingPreview();
        draw = 1;
      }

      if(eraseButton and !eraseButtonPrev and recordStatus==0){
        recordStatus = 3;
        oled.fillCircle(61,61,26,BLACK);
        draw = 1;
      }
      else if(!eraseButton and recordStatus==3){
        recordStatus = 0;
        oled.drawRoundRect(29,63,19,19,5,BLACK);
        oled.fillRoundRect(53,63,19,19,5,BLACK);
        oled.drawRoundRect(77,63,19,19,5,BLACK);
        oled.fillRect(47,47,38,20,BLACK);
        draw = 1;
      }
      eraseButtonPrev = eraseButton;
     
      if(storeButton and !storeButtonPrev and recordStatus==0){
        recordStatus = 4;
        oled.fillCircle(61,61,26,BLACK);
        draw = 1;
      }
      else if(!storeButton and recordStatus==4){
        recordStatus = 0;
        oled.drawRoundRect(29,63,19,19,5,BLACK);
        oled.fillRoundRect(53,63,19,19,5,BLACK);
        oled.drawRoundRect(77,63,19,19,5,BLACK);
        oled.fillRect(47,47,38,20,BLACK);
        draw = 1;
      }
      storeButtonPrev = storeButton;

      if (menuSelect and !selectButtonPrev and recordStatus==3){//erase confirm
        recordStatus = 0;
        oled.drawRoundRect(29,63,19,19,5,BLACK);
        oled.fillRoundRect(53,63,19,19,5,BLACK);
        oled.drawRoundRect(77,63,19,19,5,BLACK);
        oled.fillRect(47,47,38,20,BLACK);
        SD.remove(recNameBuff);
        draw = 1;
      }
      else if (menuSelect and !selectButtonPrev and recordStatus==4){
        recordStatus = 0;
        oled.drawRoundRect(29,63,19,19,5,BLACK);
        oled.fillRoundRect(53,63,19,19,5,BLACK);
        oled.drawRoundRect(77,63,19,19,5,BLACK);
        oled.fillRect(47,47,38,20,BLACK);
        numRecFiles = numRecFiles + 1;
        sprintf(recNameBuff,"/Recs/R%d.RAW",numRecFiles);
        draw = 1;
      }
      selectButtonPrev = menuSelect;

      enc4Change = encoders[3]-enc4Change;
      if (enc4Change<0){
        screen = 0;
        enc1Count = 0;
        enc1Change = 0;
        encoders[0] = 0;
        directoryDisplayed=0;
        oled.fillScreen(BLACK);
        draw = 1;
      }
      enc4Change = encoders[3];
    break;
    
    case 2://Radio editor
      enc1Change = encoders[0]-enc1Change;
      if (radioOn){
        if(enc1Change>0){
          radioChannel = radio.seekUp();
          oled.fillRect(15,61,98,18,BLACK);
          draw = 1;
        }
        else if(enc1Change<0){
          radioChannel = radio.seekDown();
          oled.fillRect(15,61,98,18,BLACK);
          draw = 1;
        }   
      }
      enc1Change = encoders[0];

      if (click1 and !click1Prev){
        if(radioOn){
          radioOn = 0;
          radio.setVolume(0);
          oled.fillRect(10,82,50,40,BLACK);
        }
        else{
          radioOn = 1;
          radio.setVolume(15);
          oled.fillRect(10,82,50,40,BLACK);
        }
        draw = 1;
      }
      click1Prev = click1;
  
      if (left and !leftPrev){
        recSource = recSource - 1;
        enc1Change = 0;
        encoders[0] = 0;
        enc1Count = lineInGain;
        screen = 1;
        oled.fillScreen(BLACK);
        draw = 1;
      }
      leftPrev = left;

      //Keep this constant so it does't have
      // an effect when we go back to recording
      // menu
      enc4Change = encoders[3];
    break;
  }
}


void staticMenuRecorder() {
  switch(screen){
    case 0:
      if (draw){
        //Light up active encoders
        digitalWrite(enc1LED,HIGH);
        digitalWrite(enc2LED,LOW);
        digitalWrite(enc3LED,LOW);
        digitalWrite(enc4LED,HIGH);
        //Write out header
        oled.setTextSize(1);
        oled.setTextColor(WHITE,BLACK);
        oled.setCursor(34, 2);
        oled.print(F("Recordings"));
        oled.drawFastHLine(0,10,124, WHITE);
        oled.fillTriangle(127,10,124,13,124,7,YELLOW);
  
        //If we haven't already, go through the current 
        // directory and show contents
        if (!directoryDisplayed){
          AudioNoInterrupts();
          currentDirectory = SD.open("/Recs");
          currentDirectory.rewindDirectory();
          for (byte f = 0; f < topItem-1; f++){
            File entry =  currentDirectory.openNextFile();
            entry.close();
          }
          oled.setTextColor(WHITE,BLACK);
          oled.setTextSize(1);
          for (byte f = 0; f < onScreenItems; f++){
            if ((f+topItem-1)<numRecFiles){
              File entry =  currentDirectory.openNextFile();
              entry.getName(entryNameBuff,15);
              entry.close();
              oled.setCursor(12,15+f*10);
              oled.println(entryNameBuff);
            }
          }
          directoryDisplayed = 1;
          currentDirectory.close();
          AudioInterrupts();
        }
  
        for (byte s = 0; s < onScreenItems; s++){
            if (s==int(enc1Count)%onScreenItems){
              color1=RED;
            }
            else{
              color1=BLACK;
            }
            oled.setCursor(0,15+s*10);
            oled.setTextColor(color1,BLACK);
            oled.println(F(">"));
        }

        if (fileErasePrompt){
          oled.drawRoundRect(86,64,12,12,3,WHITE);
          oled.fillRoundRect(101,64,12,12,3,RED);
          oled.drawRoundRect(116,64,12,12,3,WHITE);
          oled.setTextSize(1);
          oled.setCursor(90,56);
          oled.setTextColor(WHITE,BLACK);
          oled.println(F("ERASE?"));
        }
        else{
          oled.drawRoundRect(86,64,12,12,3,BLACK);
          oled.fillRoundRect(101,64,12,12,3,BLACK);
          oled.drawRoundRect(116,64,12,12,3,BLACK);
          oled.setTextSize(1);
          oled.setCursor(90,56);
          oled.setTextColor(BLACK,BLACK);
          oled.println(F("ERASE?"));
        }
      }
    break;
    case 1:
      if (draw){
        digitalWrite(enc1LED,HIGH);
        digitalWrite(enc2LED,HIGH);
        digitalWrite(enc3LED,LOW);
        digitalWrite(enc4LED,HIGH);
      
        oled.setTextSize(1);
        oled.setTextColor(WHITE,BLACK);
        oled.setCursor(28, 2);
        oled.print(F("Record Input"));
        oled.drawFastHLine(0,10,128, WHITE);
        oled.fillTriangle(0,10,3,13,3,7,YELLOW);
        
        oled.drawRoundRect(62,20,51,11,2,MAGENTA);
        oled.setTextColor(WHITE,BLACK);
        oled.setCursor(12, 22);
        oled.print(F("Source:"));
        oled.fillTriangle(57,25,59,27,59,23,MAGENTA);
        oled.fillTriangle(117,25,115,27,115,23,MAGENTA);
  
        oled.setTextColor(WHITE,BLACK);
        oled.setCursor(72, 119);
        oled.print(F("Gain:"));
        switch(recSource){
          case (0)://MIC
            oled.setTextColor(RED,BLACK);
            oled.print(microphoneGain);
            oled.print(F("dB "));
            oled.setTextColor(WHITE,BLACK);
            oled.setCursor(79, 22);
            oled.println(F("MIC"));
            circleLoc = 11+106*microphoneGain/63;
          break;
          case (1)://LINE-IN
            oled.setTextColor(RED,BLACK);
            oled.print(lineInGain);
            oled.print(F("   "));
            oled.setTextColor(WHITE,BLACK);
            oled.setCursor(67, 22);
            oled.println(F("LINE-IN"));
            circleLoc = 11+106*lineInGain/15;
          break;
          case (2)://RADIO
            oled.setTextColor(RED,BLACK);
            oled.print(lineInGain);
            oled.print(F("   "));
            oled.setTextColor(WHITE,BLACK);
            oled.setCursor(73, 22);
            oled.println(F("RADIO"));
            circleLoc = 11+106*lineInGain/15;
          break;
          case (3)://RADIO
          break;
        }
        
        switch(recordStatus){
          case 0:
            oled.drawCircle(61,61,26,DARKGREY);
            oled.fillCircle(61,61,15,BLACK);
            oled.drawFastVLine(50,54,17,DARKGREY);
            oled.setTextSize(1);
            oled.setTextColor(LIGHTGREY,BLACK);
            oled.setCursor(52, 63);
            oled.print(numRecFiles);
            oled.setTextColor(DARKGREY,BLACK);
            oled.setCursor(52, 55);
            oled.print(F("FILE"));
            oled.setCursor(36, 92);
            oled.print(F("AVAILABLE"));
          break;
        
          case 1:
            oled.drawCircle(61,61,26,PURERED);
            oled.fillCircle(61,61,10,PURERED);
            oled.setTextSize(1);
            oled.setTextColor(PURERED,BLACK);
            oled.setCursor(36, 92);
            oled.print(F("RECORDING"));
          break;
  
          case 2:
            oled.drawCircle(61,61,26,WHITE);
            oled.fillTriangle(56,51,56,71,71,61,WHITE);
            oled.setTextSize(1);
            oled.setTextColor(WHITE,BLACK);
            oled.setCursor(36, 92);
            oled.print(F(" PREVIEW "));
          break;
  
          case 3://erase prompt
            oled.drawRoundRect(29,63,19,19,5,WHITE);
            oled.fillRoundRect(53,63,19,19,5,PURERED);
            oled.drawRoundRect(77,63,19,19,5,WHITE);
            oled.fillTriangle(62,61,65,57,59,57,WHITE);
            oled.setTextSize(1);
            oled.setTextColor(WHITE,BLACK);
            oled.setCursor(48, 48);
            oled.print(F("ERASE?"));
            oled.fillRect(35,91,56,10,BLACK);
          break;
  
          case 4://erase prompt
            oled.drawRoundRect(29,63,19,19,5,WHITE);
            oled.fillRoundRect(53,63,19,19,5,DARKGREEN);
            oled.drawRoundRect(77,63,19,19,5,WHITE);
            oled.fillTriangle(62,61,65,57,59,57,WHITE);
            oled.setTextSize(1);
            oled.setTextColor(WHITE,BLACK);
            oled.setCursor(51, 48);
            oled.print(F("SAVE?"));
            oled.fillRect(35,91,56,10,BLACK);
          break;
        }
        
        oled.setTextSize(1);
        oled.setTextColor(WHITE,BLACK);
        oled.setCursor(1, 119);
        oled.print(F("Monitor:"));
        oled.setTextColor(GREEN,BLACK);
        switch(monitoringOn){
          case 0:
            oled.print(F("N"));
          break;
          case 1:
            oled.print(F("Y"));
          break;
        }
        oled.drawFastHLine(8, 108, circleLoc-11, WHITE);
        oled.fillCircle(circleLoc, 108, 3, RED);
  
        oled.drawFastHLine(0,107,circleLoc-3,BLACK);
        oled.drawFastHLine(0,106,circleLoc-2,BLACK);
        oled.drawFastHLine(0,105,circleLoc-1,BLACK);
        oled.drawFastHLine(0,109,circleLoc-3,BLACK);
        oled.drawFastHLine(0,110,circleLoc-2,BLACK);
        oled.drawFastHLine(0,111,circleLoc-1,BLACK);
  
        oled.drawLine(circleLoc+4,108,128,108,BLACK);
        oled.drawLine(circleLoc+4,107,128,107,BLACK);
        oled.drawLine(circleLoc+3,106,128,106,BLACK);
        oled.drawLine(circleLoc+2,105,128,105,BLACK);
        oled.drawLine(circleLoc+4,109,128,109,BLACK);
        oled.drawLine(circleLoc+3,110,128,110,BLACK);
        oled.drawLine(circleLoc+2,111,128,111,BLACK);

        draw = 0;
      }
    break;
    
    case 2:
      if(draw){
        digitalWrite(enc1LED,HIGH);
        digitalWrite(enc2LED,LOW);
        digitalWrite(enc3LED,LOW);
        digitalWrite(enc4LED,LOW);
        
        oled.drawRoundRect(0,40,128,87,8,MAROON);
        oled.drawRoundRect(1,41,126,85,8,MAROON);
        oled.drawRect(20,35,10,6,MAROON);
        oled.drawRoundRect(10,60,108,20,5,MAROON);
        oled.drawCircle(95,100,10,color1);
        oled.drawCircle(95,100,8,color1);
        oled.drawLine(124,41,30,15,LIGHTGREY);
        oled.fillCircle(30,15,3,LIGHTGREY);
        
        if (radioOn){
          oled.setCursor(20, 93);
          oled.fillRect(10,93,15,17,WHITE);
          oled.fillTriangle(15,101,31,85,31,117,WHITE);
          
          oled.drawLine(34,101,44,101,WHITE);
          oled.drawLine(34,97,44,90,WHITE);
          oled.drawLine(34,105,44,112,WHITE);
          
          oled.fillRect(21,36,8,4,WHITE);
          color1 = RED;
          color2 = WHITE;
        }
        else{
          oled.setCursor(10, 93);
          oled.setTextSize(2);
          oled.setTextColor(RED,BLACK);
          oled.print(F("OFF"));
          oled.fillRect(21,36,8,4,BLACK);
          color1 = DARKGREY;
          color2 = DARKGREY;
        }
        
        oled.setTextSize(2);
        oled.setTextColor(color2,BLACK);
        if (radioChannel>=1000)oled.setCursor(39, 63);
        else oled.setCursor(45, 63);
        oled.print(radioChannel);
        oled.setTextSize(1);
        oled.print(F("FM"));

        draw = 0;
      }
    break;
  }
}

void showRMS(){
  if(peak_left.available()){
    float audioLevel = peak_left.read();
    int32_t meterColor;
    if (byte(audioLevel*5) == 5){
      meterColor = 0xFF0000;
    }
    else if (byte(audioLevel*5) == 4){
      meterColor = 0xFFFF00;
    }
    else{
      meterColor = 0x00FF00;
    }
    for (byte i=5; i < 10; i++) {
      if ((i-4)<=byte(audioLevel*5))leds.setPixel(i, meterColor);
      else leds.setPixel(i, BLACK);
      leds.show();
    }
  }
  if(peak_right.available()){
    float audioLevel = peak_right.read();
    int32_t meterColor;
    if (byte(audioLevel*5) == 5){
      meterColor = 0xFF0000;
    }
    else if (byte(audioLevel*5) == 4){
      meterColor = 0xFFFF00;
    }
    else{
      meterColor = 0x00FF00;
    }
    for (byte i=0; i < 5; i++) {
      if ((5-i)<=byte(audioLevel*5))leds.setPixel(i, meterColor);
      else leds.setPixel(i, BLACK);
      leds.show();
    }
  } 
}

void recordAndPlayback(){
  switch (screen){
    case 0://list files
      if (previewStatus) continuePlayingPreview();
    case 1://rec screen
      switch (recordStatus){
        case 1://Recording
          continueRecording();
        break;
        case 2://Playing
          continuePlayingPreview();
        break;
      }
    break;
  }
  
}
long numSamples = 0;
void startRecording() {
  if (SD.exists(recNameBuff)) {
    SD.remove(recNameBuff);
  }
  recFile = SD.open(recNameBuff,FILE_WRITE);
  if (recFile) {
    record_queue.begin();
  }
  numSamples = 0;
}

void continueRecording() {
  if (record_queue.available() >= 2) {
    byte buf[512];
    memcpy(buf, record_queue.readBuffer(), 256);
    record_queue.freeBuffer();
    memcpy(buf+256, record_queue.readBuffer(), 256);
    record_queue.freeBuffer();
   
    recFile.write(buf, 512);
    numSamples = numSamples + 512;
  }
}

void stopRecording() {
  record_queue.end();
  while (record_queue.available() > 0) {
    recFile.write((byte*)record_queue.readBuffer(), 256);
    record_queue.freeBuffer();
    numSamples = numSamples + 256;
  }
  recFile.close();
  playSdRec.play(recNameBuff,0);
  playSdRec.stop();
  recordStatus = 0;
}


void startPlayingPreview() {
  recFile.close();
  switch (screen){
    case 0://list files
      playSdRec.play(previewNameBuff,0);
    break;
    case 1://rec screen
      playSdRec.play(recNameBuff,0);
    break;
  }
}

void continuePlayingPreview() {
  if (!playSdRec.isPlaying()) {
    playSdRec.stop();
  }
}

void stopPlayingPreview() {
  playSdRec.stop();
}
