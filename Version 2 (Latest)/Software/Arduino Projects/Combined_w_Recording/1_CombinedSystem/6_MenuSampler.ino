// Overall Navigation Variables for Sampler
byte chosenFile = 0;
const byte fileNameLength = 80;
const byte checkChar = 118;//ASCII "v"
const byte onScreenItems = 11;
bool notInRoot = 0;
byte topItem = 1;
byte topItemPrev = 1;
bool previewButtonPrev = 0;
bool padPrev[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
bool assignSampleScreen = 0;

bool editSampleScreen = 0;
byte sampleToEdit = 0;

void menuCheckSampler() {
  if (screen != screenPrev){
    oled.fillScreen(BLACK);
    enc1Count = 0;
    enc1Change = 0;
    enc2Count = 0;
    enc2Change = 0;
    enc3Count = 0;
    enc3Change = 0;
    encoders[0] = 0;
    encoders[1] = 0;
    encoders[2] = 0;
    topItem = 1;
    if (screen==0)directoryDisplayed = 0;
  }
  screenPrev = screen;
  switch (screen) {
    case 0:
      if (right and !rightPrev){
        screen = 1;
      }
      rightPrev = right;
      if(assignSampleScreen){
        if (click1 and !click1Prev){
          assignSampleScreen = 0;
          directoryDisplayed = 0;
          oled.fillScreen(BLACK);
        }
        click1Prev=click1;

        for (byte b = 0; b < 12; b++){
          if(mainSelect){
            if(samplePad[b] and !padPrev[b]){
              bool doneAssigning = 0;
              while(!doneAssigning){
                oled.setTextSize(2);
                oled.setTextColor(BLUE,BLACK);
                oled.setCursor(22,62);
                oled.print(F("LOADING"));
                playSdWav1.stop();
                AudioNoInterrupts();
                strcpy(previewfileNameBuff,fileNameBuff);
                strcat(previewfileNameBuff,"/");
                strcat(previewfileNameBuff,newfileNameBuff);
                File entry = SD.open(previewfileNameBuff);
                unsigned long ln = entry.size();
                entry.close();
                SerialFlashFile ff = SerialFlash.open(samps[b].fileName);
                oled.setTextColor(RED,BLACK);
                oled.setCursor(22,62);
                oled.print(F("ERASING"));
                ff.erase();
                while (SerialFlash.ready() == false) {
                  //wait
                }
                AudioInterrupts();
                queue1.begin();
                playSdWav1.play(previewfileNameBuff);
                unsigned long count = 0;
                oled.setTextColor(GREEN,BLACK);
                oled.setCursor(22,62);
                oled.print(F("WRITING"));
                while(playSdWav1.isPlaying()){
                  if (queue1.available() >= 1) {
                    byte buf[256];
                    memcpy(buf, queue1.readBuffer(), 256);
                    queue1.freeBuffer();
                    ff.write(buf, 256);
                    count = count + 256;
                  }
                }
                oled.fillRect(22,62,84,16,BLACK);
                ff.close();
                queue1.clear();
                queue1.end();
                playSdWav1.stop();
                doneAssigning = 1;
              }
            }
          }
          padPrev[b] = samplePad[b];
        }
      }
      else{
        enc1Change = encoders[0]-enc1Change;
        enc1Count = enc1Count + enc1Change;
        if (enc1Count>numItems-1) enc1Count= numItems-1;
        if (enc1Count < 0){
          enc1Count = 0; 
          topItem = 1;
        }
        if ((int(enc1Count)%onScreenItems == 0) and (enc1CountPrev < enc1Count)){
          topItemPrev = topItem;
          topItem = 1+enc1Count;
          directoryDisplayed = 0;
          oled.fillRect(0,11,128,118,BLACK);
        }
        else if ((int(enc1Count)%onScreenItems == onScreenItems-1) and (enc1CountPrev > enc1Count)){
          topItemPrev = topItem;
          topItem = enc1Count-(onScreenItems-2);
          directoryDisplayed = 0;
          oled.fillRect(0,11,128,118,BLACK);
        }
        chosenFile = enc1Count;
        enc1CountPrev = enc1Count;
        enc1Change = encoders[0];
  
        if (click1 and !click1Prev){
          AudioNoInterrupts();
          currentDirectory = SD.open(fileNameBuff);
          currentDirectory.rewindDirectory();
          File entry =  currentDirectory.openNextFile();
          
          for (byte f = 0; f <chosenFile; f++){
            entry.close();
            entry =  currentDirectory.openNextFile();
          }
          
          entry.getName(newfileNameBuff,fileNameLength);
          
          if (entry.isDir()) {
            entry.close();
            strcat(fileNameBuff,"/");
            strcat(fileNameBuff,newfileNameBuff);
            enterDirectory(fileNameBuff);
          }
          else if(newfileNameBuff[strlen(newfileNameBuff)-1]==checkChar){
            if(entry.size()<maxSampleLength){
              assignSampleScreen = 1;
              oled.fillScreen(BLACK);
            }
            entry.close();
          }
          else{
            entry.close();
          }
          currentDirectory.close();
          AudioInterrupts();
        }
        click1Prev = click1;
  
        if (previewButton and !previewButtonPrev){
          playSdWav1.stop();
          AudioNoInterrupts();
          currentDirectory = SD.open(fileNameBuff);
          currentDirectory.rewindDirectory();
          File entry =  currentDirectory.openNextFile();
          for (byte f = 0; f <chosenFile; f++){
            entry.close();
            entry =  currentDirectory.openNextFile();
          }
          if (!entry.isDir()) {
            entry.getName(newfileNameBuff,fileNameLength);
            entry.close();
            if(newfileNameBuff[strlen(newfileNameBuff)-1]==checkChar){
              strcpy(previewfileNameBuff,fileNameBuff);
              strcat(previewfileNameBuff,"/");
              strcat(previewfileNameBuff,newfileNameBuff);
              playSdWav1.play(previewfileNameBuff);
            }
          }
          else{
            entry.close();
          }
          currentDirectory.close();
          AudioInterrupts();
        }
        previewButtonPrev = previewButton;
        
        if (strcmp(fileNameBuff,rootSampleDir)!=0)notInRoot = 1;
        else notInRoot = 0;
        if (click2 and !click2Prev and notInRoot){
          strcpy(fileNameBuff,rootSampleDir);
          enterDirectory(fileNameBuff);
          topItem = 1;
        }
      }
    break;
    case 1:
      if(editSampleScreen){
        //Parameter Scrolling
        enc1Change = encoders[0]-enc1Change;
        enc1Count = enc1Count + 15*enc1Change;
        if (enc1Count < 0) enc1Count = 0;
        if (enc1Count > 300) enc1Count = 300;
        sampleadsr[sampleToEdit][0]= enc1Count;
        enc1Change = encoders[0];

        enc2Change = encoders[1]-enc2Change;
        enc2Count = enc2Count + 15*enc2Change;;
        if (enc2Count < 0) enc2Count = 0;
        if (enc2Count > 300) enc2Count = 300;
        sampleadsr[sampleToEdit][1]= enc2Count;
        enc2Change = encoders[1];

        enc3Change = encoders[2]-enc3Change;
        enc3Count = enc3Count + 0.05*enc3Change;;
        if (enc3Count < 0) enc3Count = 0;
        if (enc3Count > 1.0) enc3Count = 1.0;
        sampleadsr[sampleToEdit][2]= enc3Count;
        enc3Change = encoders[2];

        enc4Change = encoders[3]-enc4Change;
        enc4Count = enc4Count + 15*enc4Change;;
        if (enc4Count < 0) enc4Count = 0;
        if (enc4Count > 300) enc4Count = 300;
        sampleadsr[sampleToEdit][3]= enc4Count;
        enc4Change = encoders[3];

        if (left and !leftPrev){
          sampleadsr[sampleToEdit][4]=sampleadsr[sampleToEdit][4]-0.05;
          if(sampleadsr[sampleToEdit][4]<0.0)sampleadsr[sampleToEdit][4]=0.0;
        }
        leftPrev = left;
        if (right and !rightPrev){
          sampleadsr[sampleToEdit][4]=sampleadsr[sampleToEdit][4]+0.05;
          if(sampleadsr[sampleToEdit][4]>1.0)sampleadsr[sampleToEdit][4]=1.0;
        }
        rightPrev = right;
        if (mainSelect and !mainSelectPrev){
          editSampleScreen = 0;
          oled.fillScreen(BLACK);
        }   
        mainSelectPrev = mainSelect;
        
        updateSampleEnvelope(sampleToEdit);
      }
      else{
        if (left and !leftPrev){
        screen = 0;
        }
        leftPrev = left;
        
        for (byte b = 0; b < 12; b++){
          if(samplePad[b] and !padPrev[b]){
             sampleToEdit = b;
             encoders[0] = 0;
             encoders[1] = 0;
             encoders[2] = 0;
             encoders[3] = 0;
             enc1Change = 0;
             enc2Change = 0;
             enc3Change = 0;
             enc4Change = 0;
             enc1Count = sampleadsr[b][0];
             enc2Count = sampleadsr[b][1];
             enc3Count = sampleadsr[b][2];
             enc4Count = sampleadsr[b][3];
             editSampleScreen = 1;
             oled.fillScreen(BLACK);
          }
        }
      }
    break;
  }
}

void staticMenuSampler() {
  switch (screen) {
    case 0:
      if(assignSampleScreen){
        digitalWrite(enc1LED,HIGH);
        digitalWrite(enc2LED,LOW);
        digitalWrite(enc3LED,LOW);
        digitalWrite(enc4LED,LOW);
         
        oled.setTextSize(1);
        oled.setTextColor(MAGENTA,BLACK);
        oled.setCursor(25, 2);
        oled.print(F("Assign Sample"));
        oled.drawRoundRect(0,0,127,11,6, MAGENTA);

        oled.drawRect(0,16,88,110,WHITE);
        oled.drawFastVLine(30,16,110,WHITE);
        oled.drawFastVLine(59,16,110,WHITE);
        oled.drawFastHLine(0,43,88,WHITE);
        oled.drawFastHLine(0,70,88,WHITE);
        oled.drawFastHLine(0,97,88,WHITE);

        for (byte b = 0; b < 12; b++){
          byte xloc = 29*(b%3)+6;
          byte yloc = 27*(b/3)+20;
          if(samplePad[b]){
            oled.fillRoundRect(xloc,yloc,20,20,3,WHITE);
          }
          else{
            oled.fillRoundRect(xloc,yloc,20,20,3,BLACK);
          }
        }
        
        oled.setCursor(100,67);
        oled.setTextSize(1);
        if(mainSelect){
          oled.drawRoundRect(97,64,29,13,3,MAGENTA);
          oled.setTextColor(WHITE,BLACK);
          oled.println(F("BIND"));
        }
        else{
          oled.drawRoundRect(97,64,29,13,3,BLACK);
          oled.setTextColor(BLACK,BLACK);
          oled.println(F("BIND"));
        }
        
      }
      else{
        //Light up active encoders
        digitalWrite(enc1LED,HIGH);
        digitalWrite(enc2LED,HIGH);
        digitalWrite(enc3LED,LOW);
        digitalWrite(enc4LED,LOW);
        //Write out header
        oled.setTextSize(1);
        oled.setTextColor(WHITE,BLACK);
        oled.setCursor(43, 2);
        oled.print(F("Samples"));
        oled.drawFastHLine(0,10,124, WHITE);
        oled.fillTriangle(127,10,124,13,124,7,MAGENTA);
  
        //If we haven't already, go through the current 
        // directory and show contents
        if (!directoryDisplayed){
          AudioNoInterrupts();
          currentDirectory = SD.open(fileNameBuff);
          currentDirectory.rewindDirectory();
          for (byte f = 0; f < topItem-1; f++){
            File entry =  currentDirectory.openNextFile();
            entry.close();
          }
          oled.setTextColor(WHITE,BLACK);
          oled.setTextSize(1);
          for (byte f = 0; f < onScreenItems; f++){
            if ((f+topItem-1)<numItems){
              File entry =  currentDirectory.openNextFile();
              entry.getName(newfileNameBuff,fileNameLength);
              if(entry.isDirectory()){
                oled.drawRect(10,16+f*10,8,6,WHITE);
                oled.fillRect(10,15+f*10,4,1,WHITE);
              }
              else{
                if(newfileNameBuff[strlen(newfileNameBuff)-1]==checkChar){
                  oled.fillCircle(12,19+f*10,1,MAGENTA);
                  oled.drawFastVLine(13,15+f*10,5,MAGENTA);
                  oled.drawLine(13,15+f*10,15,17+f*10,MAGENTA);
                }
                else{
                  oled.drawLine(10,16+f*10,15,22+f*10,DARKGREY);
                  oled.drawLine(10,22+f*10,15,16+f*10,DARKGREY);
                }
              }
              entry.close();
              oled.setCursor(20,15+f*10);
              if (strlen(newfileNameBuff) < 15){
                oled.println(newfileNameBuff);
              }
              else{
                for(byte c = 0; c < 15; c++){
                  oled.print(newfileNameBuff[c]);              
                }
                oled.println(F("..."));
              }
            }
          }
          directoryDisplayed = 1;
          currentDirectory.close();
          AudioInterrupts();
        }
  
        for (byte s = 0; s < onScreenItems; s++){
            if (s==int(enc1Count)%onScreenItems){
              color1=RED;
              color2=BLACK;
            }
            else{
              color1=BLACK;
              color2=BLACK;
            }
            oled.setCursor(0,15+s*10);
            oled.setTextColor(color1,color2);
            oled.println(F(">"));
        }
  
        if (notInRoot){
          oled.fillTriangle(0,3,4,3,2,0,GREEN);
          oled.drawFastVLine(2,3,3,GREEN);
          oled.drawFastHLine(2,6,10,GREEN);
          oled.fillCircle(12,6,2,GREEN);
        }
        else{
          oled.fillRect(0,0,15,9,BLACK);
        }
      }
    break;
    case 1:
      if(editSampleScreen){
        digitalWrite(enc1LED,HIGH);
        digitalWrite(enc2LED,HIGH);
        digitalWrite(enc3LED,HIGH);
        digitalWrite(enc4LED,HIGH);
         
        oled.setTextSize(1);
        oled.setTextColor(MAGENTA,BLACK);
        oled.setCursor(25, 2);
        oled.print(F("Edit Envelope"));
        oled.drawRoundRect(0,0,127,11,6, MAGENTA);
        
        oled.setCursor(31, 20);
        oled.setTextColor(WHITE,BLACK);
        oled.print(F("Volume:"));
        oled.setTextColor(MAGENTA,BLACK);
        oled.print(sampleadsr[sampleToEdit][4]);
        oled.setTextColor(WHITE,BLACK);
        
        for (byte i = 0; i<4; i++){
          int8_t circleLoc = 0;
          switch (i){
            case 0://Attack - 0-300 in steps of 15
              color1 = RED;
              circleLoc = 95-(sampleadsr[sampleToEdit][i]/300.0)*60.0;
              break;
            case 1://Decay - 0-300 in steps of 15
              color1 = GREEN;
              circleLoc = 95.0-(sampleadsr[sampleToEdit][i]/300.0)*60.0;
              break;
            case 2://Sustain - 0-1.0 in steps of 0.05
              color1 = BLUE;
              circleLoc = 95.0-sampleadsr[sampleToEdit][i]*60.0;
              break;
            case 3://Release - 0-300 in steps of 15
              color1 = YELLOW;
              circleLoc = 95.0-(sampleadsr[sampleToEdit][i]/300.0)*60.0;
              break;
          }
          oled.setCursor((2*(i+1))+(30*i)+12,104);
          oled.setTextColor(color1,BLACK);
          oled.print(adsrNames[i]);
          oled.drawRect((2*(i+1))+(30*i)-1,100,30,15,WHITE);
          oled.drawLine((2*(i+1))+(30*i)+14, 100, (2*(i+1))+(30*i)+14, circleLoc, color1);
          oled.fillCircle((2*(i+1))+(30*i)+14, circleLoc, 3, color1);
  
          oled.drawLine((2*(i+1))+(30*i)+10,29,(2*(i+1))+(30*i)+10,circleLoc-1,BLACK);
          oled.drawLine((2*(i+1))+(30*i)+11,29,(2*(i+1))+(30*i)+11,circleLoc-2,BLACK);
          oled.drawLine((2*(i+1))+(30*i)+12,29,(2*(i+1))+(30*i)+12,circleLoc-3,BLACK);
          oled.drawLine((2*(i+1))+(30*i)+13,29,(2*(i+1))+(30*i)+13,circleLoc-4,BLACK);
          oled.drawLine((2*(i+1))+(30*i)+14,29,(2*(i+1))+(30*i)+14,circleLoc-4,BLACK);
          oled.drawLine((2*(i+1))+(30*i)+15,29,(2*(i+1))+(30*i)+15,circleLoc-4,BLACK);
          oled.drawLine((2*(i+1))+(30*i)+16,29,(2*(i+1))+(30*i)+16,circleLoc-3,BLACK);
          oled.drawLine((2*(i+1))+(30*i)+17,29,(2*(i+1))+(30*i)+17,circleLoc-2,BLACK);
          oled.drawLine((2*(i+1))+(30*i)+18,29,(2*(i+1))+(30*i)+18,circleLoc-1,BLACK);
  
          oled.drawLine((2*(i+1))+(30*i)+10,99,(2*(i+1))+(30*i)+10,circleLoc+1,BLACK);
          oled.drawLine((2*(i+1))+(30*i)+11,99,(2*(i+1))+(30*i)+11,circleLoc+2,BLACK);
          oled.drawLine((2*(i+1))+(30*i)+12,99,(2*(i+1))+(30*i)+12,circleLoc+3,BLACK);
          oled.drawLine((2*(i+1))+(30*i)+13,99,(2*(i+1))+(30*i)+13,circleLoc+4,BLACK);
  
          oled.drawLine((2*(i+1))+(30*i)+15,99,(2*(i+1))+(30*i)+15,circleLoc+4,BLACK);
          oled.drawLine((2*(i+1))+(30*i)+16,99,(2*(i+1))+(30*i)+16,circleLoc+3,BLACK);
          oled.drawLine((2*(i+1))+(30*i)+17,99,(2*(i+1))+(30*i)+17,circleLoc+2,BLACK);
          oled.drawLine((2*(i+1))+(30*i)+18,99,(2*(i+1))+(30*i)+18,circleLoc+1,BLACK);
        }
      }
      else{
        //Light up active encoders
        digitalWrite(enc1LED,LOW);
        digitalWrite(enc2LED,LOW);
        digitalWrite(enc3LED,LOW);
        digitalWrite(enc4LED,LOW);
        //Write out header
        oled.setTextSize(1);
        oled.setTextColor(WHITE,BLACK);
        oled.setCursor(35, 2);
        oled.print(F("Edit Sample"));
        oled.drawFastHLine(0,10,128, WHITE);
        oled.fillTriangle(0,10,3,13,3,7,MAGENTA);
  
        for (byte b = 0; b < 12; b++){
          byte xloc = 29*(b%3)+46;
          byte yloc = 27*(b/3)+20;
          oled.fillRoundRect(xloc,yloc,20,20,3,WHITE);
        }
        
        oled.setTextSize(1);
        oled.setTextColor(MAGENTA,BLACK);
        oled.setCursor(2,67);
        oled.print(F("Select"));
        oled.drawFastHLine(0,64,38,MAGENTA);
        oled.drawFastHLine(0,76,38,MAGENTA);
        oled.drawFastVLine(0,64,12,MAGENTA);
        oled.drawFastVLine(37,16,49,MAGENTA);
        oled.drawFastVLine(38,16,49,MAGENTA);
        oled.drawFastVLine(37,76,50,MAGENTA);
        oled.drawFastVLine(38,76,50,MAGENTA);
        oled.drawFastHLine(38,16,90,MAGENTA);
        oled.drawFastHLine(38,125,90,MAGENTA);
        oled.drawLine(0,64,38,16,MAGENTA);
        oled.drawLine(0,76,38,125,MAGENTA);
      }
    break;
  }
}

void enterDirectory(char fileName[]){
  AudioNoInterrupts();
  currentDirectory = SD.open(fileName);
  numItems = 0;
  while(true) {
    File entry =  currentDirectory.openNextFile();
    if (!entry) {
      currentDirectory.rewindDirectory();
      break;
    }
    else{
      numItems = numItems+1;
    }
    delay(1);
    entry.close();
    delay(1);
  }
  oled.fillScreen(BLACK);
  directoryDisplayed = 0;
  currentDirectory.close();
  AudioInterrupts();
}

void updateSampleEnvelope(byte sampleNum) {
  sample_envelope_bank[sampleNum]->attack(sampleadsr[sampleNum][0]);
  sample_envelope_bank[sampleNum]->decay(sampleadsr[sampleNum][1]);
  sample_envelope_bank[sampleNum]->sustain(sampleadsr[sampleNum][2]);
  sample_envelope_bank[sampleNum]->release(sampleadsr[sampleNum][3]);
  if(sampleNum<4){
    sample_secondary_mixer_1.gain(sampleNum,sampleadsr[sampleNum][4]);
  }
  else if(sampleNum>=4 and sampleNum<8){
    sample_secondary_mixer_2.gain((sampleNum-4),sampleadsr[sampleNum][4]);
  }
  else if(sampleNum>=8 and sampleNum<12){
    sample_secondary_mixer_3.gain((sampleNum-8),sampleadsr[sampleNum][4]);
  }
}
