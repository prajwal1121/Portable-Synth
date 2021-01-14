/*
 * Navigation code. This part lets the user switch menus,   
 * and edit different parameters when in different menus. 
 * This is where most of the work gets done.
 */
 
#define numMenus 5
byte screen = 0;
byte screenPrev = 0;

bool click1Prev = 0;
int enc1Count = 1;
int enc1Change = 0;

bool click2Prev = 0;
float enc2Count = 0;
int enc2Change = 0;

bool click3Prev = 0;
float enc3Count = 0;
int enc3Change = 0;

int enc4Count = 0;
int enc4Change = 0;

bool arbSelectPrev = 0;
bool arbSelect = 0;
bool waveformEditEnable = 0;

byte chosenOscillator = 0;
byte chosenOscPrev = 0;
int16_t color1 = WHITE;
int16_t color2 = WHITE;

byte chosenParameter = 0;
byte chosenParameterPrev = 0;

int waveIdx = 1;
unsigned long waveIdxTimer = millis();
int16_t waveDrawColor = WHITE;

int hOffset = 0;
int vOffset = 0;

int8_t circY;
int8_t circX;
int8_t circYPrev;
int8_t circXPrev;
byte joyYMod = 1;
byte joyXMod = 0;
bool enableJoystickMod[2] = {1,1};
byte i_got_here_first[2] = {1,0};

#define bendStFactor 8000 //number of semitones to bend * 1000
float pitchBend = 1;
float bendExponent = 0;

#define bendHz 800
float filterBend = 0;

byte chosenModSource = 0;
bool optionScreen = 0;
bool chosenModOption = 0;
bool modEditScreen = 0;
bool modAssignScreen = 0;
byte LFOWaveShape[2] = {0,0};
byte LFOWaveShapePrev[2] = {0,0};

byte chosenModDestination = 0;

void menuCheck() {
  //Menu Changer
  enc4Change = encoders[3]-enc4Change;
  enc4Count = enc4Count + enc4Change;
  if (enc4Count<0) enc4Count= 0;
  if (enc4Count>numMenus) enc4Count= numMenus;
  screen = enc4Count;
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

    if (screen==0)enc2Count = waveAmplitude[0];
    if (screen==1)enc2Count = adsr[0];
    if (screen==2){
      enc1Count = semitonesTune;
      enc2Count = detunePercent;
    }
    if (screen==3){
      enc1Count = filterFreq;
      enc2Count = filterQ;
    }
    if (screen==4){
      enc1Count = joyYMod;
      enc2Count = joyXMod;
    }
  }
  screenPrev = screen;
  enc4Change = encoders[3];

  if(enableJoystickMod[0]){
    switch(joyYMod){
      case 0:
      break;
      case 1:
        bendExponent = map(analogRead(joyY),130,820,-bendStFactor,bendStFactor)/(12000.0);
        pitchBend = pow(2,bendExponent);
        updateFreq();
      break;
      case 2:
        filterBend = map(analogRead(joyY),130,820,-bendHz,bendHz);
        if (filterFreq-filterBend < 100) filterBend = filterFreq-100;
        updateFilter();                                      
      break;
    }
  }
  if(enableJoystickMod[1]){
      switch(joyXMod){
        case 0:
        break;
        case 1:
          bendExponent = map(analogRead(joyX),220,870,bendStFactor,-bendStFactor)/(12000.0);
          pitchBend = pow(2,bendExponent);
          updateFreq();
        break;
        case 2:
          filterBend = map(analogRead(joyX),220,870,bendHz,-bendHz);
          if (filterFreq-filterBend < 0) filterBend = filterFreq;
          updateFilter();    
        break;
      }
    }

  switch (screen) {
    case 0: //Oscillator Screen
      enc1Change = encoders[0]-enc1Change;
      enc1Count = enc1Count + enc1Change;
      if (enc1Count<0) enc1Count= 0;
      if (enc1Count>2) enc1Count= 2;
      chosenOscillator = enc1Count;
      if (chosenOscillator != chosenOscPrev){
        enc2Change = 0;
        encoders[1] = 0;
        enc2Count = waveAmplitude[chosenOscillator];
        chosenOscPrev = chosenOscillator; 
      }
      enc1Change = encoders[0];
    
      //Amplitude Scrolling
      enc2Change = encoders[1]-enc2Change;
      enc2Count = enc2Count + 0.1*enc2Change;
      if (enc2Count < 0) enc2Count = 0;
      if (enc2Count > 1.0) enc2Count = 1.0;
      waveAmplitude[chosenOscillator] = enc2Count;
      switch (chosenOscillator){
        case 0:
          for (byte n = 0; n < 8; n++){
            noise_bank[n]->amplitude(waveAmplitude[0]);
          }
          break;
        case 1:
          for (byte a = 0; a < 8; a++){
            a_bank[a]->amplitude(waveAmplitude[1]);
          }
          break;
        case 2:
          for (byte b = 0; b < 8; b++){
            b_bank[b]->amplitude(waveAmplitude[2]);
          }
          break;
      }
      enc2Change = encoders[1];
      
      if (click1 and !click1Prev){
        switchWave(chosenOscillator);
        oled.fillRoundRect(10,(40*chosenOscillator)+18,45,30,5,BLACK);
      }
      click1Prev = click1;
    
      if (click3 and !arbSelectPrev){
        if (arbSelect){
          arbSelect = 0;
          oled.fillScreen(BLACK);
          for (int i=0; i < numled; i++) {
            leds.setPixel(i, BLACK);
            leds.setBrightness(5);
            leds.show();
          }
        }
        else if (!arbSelect and waveformEditEnable){
          arbSelect = 1;
          oled.fillScreen(BLACK);
          for (int i=0; i < numled; i++) {
            leds.setPixel(i, 0xFF1088);
            leds.setBrightness(5);
            leds.show();
          }
        }
      }
      arbSelectPrev = click3;
    
      if (arbSelect){
        if (right and (millis()-waveIdxTimer > 10)){
          waveIdx = waveIdx+1;
          if (waveIdx >= 255)waveIdx = 255;
          waveIdxTimer = millis();
        }
        else if (left and (millis()-waveIdxTimer > 10)){
          waveIdx = waveIdx-1;
          if (waveIdx <= 1)waveIdx = 1;
          waveIdxTimer = millis();
        }
    
        arbWave[waveIdx] = map(analogRead(joyY),130,820,-30000,30000);
        if (arbWave[waveIdx] > 30000) arbWave[waveIdx] = 30000;
        if (arbWave[waveIdx] <-30000) arbWave[waveIdx] = -30000;
      }
    break;

    case 1:
      enc1Change = encoders[0]-enc1Change;
      enc1Count = enc1Count + enc1Change;
      if (enc1Count < 0) enc1Count = 0;
      if (enc1Count > 3) enc1Count = 3;
      chosenParameter = enc1Count;
      if (chosenParameter != chosenParameterPrev){
        enc2Change = 0;
        encoders[1] = 0;
        enc2Count = adsr[chosenParameter];
        chosenParameterPrev = chosenParameter;
      }
      
      enc1Change = encoders[0];
      
      //Parameter Scrolling
      enc2Change = encoders[1]-enc2Change;
      switch (chosenParameter){
        case 0://Attack - 0-3000 in steps of 150
          enc2Count = enc2Count + 150*enc2Change;
          if (enc2Count > 3000) enc2Count = 3000;
          break;
        case 1://Decay - 0-3000 in steps of 150
          enc2Count = enc2Count + 150*enc2Change;
          if (enc2Count > 3000) enc2Count = 3000;
          break;
        case 2://Sustain - 0-1.0 in steps of 0.05
          enc2Count = enc2Count + 0.05*enc2Change;
          if (enc2Count > 1.0) enc2Count = 1.0;
          break;
        case 3://Release - 0-3000 in steps of 150
          enc2Count = enc2Count + 150*enc2Change;
          if (enc2Count > 3000) enc2Count = 3000;
          break;
      }
      if (enc2Count < 0) enc2Count = 0;
      adsr[chosenParameter] = enc2Count;
      updateEnvelope();
      enc2Change = encoders[1];
    break;

    case 2://Osc 2 Tuning
      //Semitone Scrolling
      enc1Change = encoders[0]-enc1Change;
      enc1Count = enc1Count + enc1Change;
      if (enc1Count < -24) enc1Count = -24;
      if (enc1Count > 24) enc1Count = 24;
      semitonesTune = enc1Count;
      enc1Change = encoders[0];
      
      //Detune Scrolling
      enc2Change = encoders[1]-enc2Change;
      enc2Count = enc2Count + enc2Change;
      if (enc2Count < -5) enc2Count = -5;
      if (enc2Count > 5) enc2Count = 5;
      detunePercent = enc2Count;
      detuneFactor = 1.0 + (detunePercent/100.0);
      enc2Change = encoders[1];

    break;

    case 3:
      //Freqency Scrolling
      enc1Change = encoders[0]-enc1Change;
      enc1Count = enc1Count + 50*enc1Change;
      if (enc1Count < 100) enc1Count = 100;
      if (enc1Count > 3000) enc1Count = 3000;
      filterFreq = enc1Count;
      updateFilter();
      enc1Change = encoders[0];

      //Resonance Scrolling
      enc2Change = encoders[1]-enc2Change;
      enc2Count = enc2Count + 0.1*enc2Change;
      if (enc2Count < 0) enc2Count = 0;
      if (enc2Count > 3.0) enc2Count = 3.0;
      filterQ = enc2Count;
      updateFilter();
      enc2Change = encoders[1];
      
      for (int i=0; i < numled; i++) {
        leds.setPixel(i, BLACK);
        leds.setBrightness(0);
        leds.show();
      }
    break;
    
    case 4://Joystick Mod
      circY = map(analogRead(joyY),130,820,22,-22);
      circX = map(analogRead(joyX),220,870,22,-22);

      enc1Change = encoders[0]-enc1Change;
      enc1Count = enc1Count + enc1Change;
      if (enc1Count<0) enc1Count = 0;
      if (enc1Count>2) enc1Count = 2;
      joyYMod = enc1Count;
      if ((joyYMod == joyXMod)&&(joyYMod == i_got_here_first[1])){
        enableJoystickMod[0] = 0;
        i_got_here_first[0] = 255;
        color1 = 0xA514;
      }
      else{
        enableJoystickMod[0] = 1;
        i_got_here_first[0] = joyYMod;
        color1 = RED;
      }
      enc1Change = encoders[0];

      enc2Change = encoders[1]-enc2Change;
      enc2Count = enc2Count + enc2Change;
      if (enc2Count<0) enc2Count = 0;
      if (enc2Count>2) enc2Count = 2;
      joyXMod = enc2Count;
      if ((joyXMod == joyYMod)&&(joyXMod == i_got_here_first[0])){
        enableJoystickMod[1] = 0;
        i_got_here_first[1] = 255;
        color2 = 0xA514;
      }
      else{
        enableJoystickMod[1] = 1;
        i_got_here_first[1] = joyXMod;
        color2 = GREEN;
      }
      enc2Change = encoders[1];

      for (int i=0; i < numled; i++) {
        leds.setPixel(i, 0xFF1088);
        leds.setBrightness(5);
        leds.show();
      }
    break;

    case 5:
      if(optionScreen){
        if (modEditScreen){
          if (chosenModSource == 0 or chosenModSource == 1){
            enc1Change = encoders[0]-enc1Change;
            enc1Count = enc1Count + enc1Change;
            if (enc1Count<0) enc1Count= 8;
            if (enc1Count>8) enc1Count= 0;
            LFOWaveShape[chosenModSource] = enc1Count;  
            enc1Change = encoders[0];
            
            if (LFOWaveShape[chosenModSource] != LFOWaveShapePrev[chosenModSource]){
              oled.fillRect(45,44,35,18,BLACK);
              updateModLFOShape(chosenModSource);
              LFOWaveShapePrev[chosenModSource]=LFOWaveShape[chosenModSource];
            }

            enc2Change = encoders[1]-enc2Change;
            enc2Count = enc2Count + 0.1*enc2Change;
            if (enc2Count<0) enc2Count= 0;
            if (enc2Count>10.0) enc2Count= 10.0;
            LFOFrequency[chosenModSource] = enc2Count;  
            enc2Change = encoders[1];
            if (LFOFrequency[chosenModSource] != LFOFrequencyPrev[chosenModSource]){
              updateModLFO(chosenModSource);
              LFOFrequencyPrev[chosenModSource] = LFOFrequency[chosenModSource];  
            }

            enc3Change = encoders[2]-enc3Change;
            enc3Count = enc3Count + 0.1*enc3Change;
            if (enc3Count<0) enc3Count= 0;
            if (enc3Count>1.0) enc3Count= 1.0;
            LFOAmplitude[chosenModSource] = enc3Count;  
            enc3Change = encoders[2];
            if (LFOAmplitude[chosenModSource] != LFOAmplitudePrev[chosenModSource]){
              updateModLFO(chosenModSource);
              LFOAmplitudePrev[chosenModSource] = LFOAmplitude[chosenModSource];  
            }         

            Serial.println(LFOFrequency[chosenModSource]);
          }
          else{
            enc1Change = encoders[0]-enc1Change;
            enc1Count = enc1Count + enc1Change;
            if (enc1Count < 0) enc1Count = 0;
            if (enc1Count > 3) enc1Count = 3;
            chosenParameter = enc1Count;
            if (chosenParameter != chosenParameterPrev){
              enc2Change = 0;
              encoders[1] = 0;
              enc2Count = modadsr[chosenModSource-2][chosenParameter];
              chosenParameterPrev = chosenParameter;
            }
            enc1Change = encoders[0];
            
            //Parameter Scrolling
            enc2Change = encoders[1]-enc2Change;
            switch (chosenParameter){
              case 0://Attack - 0-3000 in steps of 150
                enc2Count = enc2Count + 150*enc2Change;
                if (enc2Count > 3000) enc2Count = 3000;
                break;
              case 1://Decay - 0-3000 in steps of 150
                enc2Count = enc2Count + 150*enc2Change;
                if (enc2Count > 3000) enc2Count = 3000;
                break;
              case 2://Sustain - 0-1.0 in steps of 0.05
                enc2Count = enc2Count + 0.05*enc2Change;
                if (enc2Count > 1.0) enc2Count = 1.0;
                break;
              case 3://Release - 0-3000 in steps of 150
                enc2Count = enc2Count + 150*enc2Change;
                if (enc2Count > 3000) enc2Count = 3000;
                break;
            }
            if (enc2Count < 0) enc2Count = 0;
            modadsr[chosenModSource-2][chosenParameter] = enc2Count;
            enc2Change = encoders[1];

            enc3Change = encoders[2]-enc3Change;
            enc3Count = enc3Count + 0.1*enc3Change;
            if (enc3Count<0) enc3Count= 0;
            if (enc3Count>1.0) enc3Count= 1.0;
            modadsr[chosenModSource-2][4] = enc3Count;  
            enc3Change = encoders[2];

            updateModEnvelope(chosenModSource-2);
          }

          if (click2 and !click2Prev){
            modEditScreen = 0;
            oled.fillScreen(BLACK);
            encoders[0] = 0;
            encoders[1] = 0;
            encoders[2] = 0;
            enc1Change = 0;
            enc2Change = 0;
            enc3Change = 0;
            enc1Count = 0;
            enc2Count = chosenModOption;
            enc3Count = 0;
          }
          click2Prev = click2;
        }
        else if (modAssignScreen){
          enc3Change = encoders[2]-enc3Change;
          enc3Count = enc3Count + enc3Change;
          if (enc3Count<0) enc3Count= 0;
          if (chosenModSource == 0 or chosenModSource == 1){
            if (enc3Count>3) enc3Count= 3;
          }
          else {
            if (enc3Count>4) enc3Count= 4;
          }
          chosenModDestination = enc3Count;  
          enc3Change = encoders[2];

          if (chosenModSource == 0 or chosenModSource == 1){
            if (click3 and !click3Prev){
              LFODest[chosenModSource][chosenModDestination] = !LFODest[chosenModSource][chosenModDestination];
              oled.fillCircle(100,32+chosenModDestination*26,3,BLACK);
              updateModLFODest(chosenModSource);
            }
            click3Prev = click3;
          }
          else{
            if (click3 and !click3Prev){
              envDest[chosenModSource-2][chosenModDestination] = !envDest[chosenModSource-2][chosenModDestination];
              oled.fillCircle(100,32+chosenModDestination*20,3,BLACK);
              updateModEnvDest(chosenModSource-2);
            }
            click3Prev = click3;
          }
          
          if (click2 and !click2Prev){
            modAssignScreen = 0;
            oled.fillScreen(BLACK);
            encoders[0] = 0;
            encoders[1] = 0;
            encoders[2] = 0;
            enc1Change = 0;
            enc2Change = 0;
            enc3Change = 0;
            enc1Count = 0;
            enc2Count = chosenModOption;
            enc3Count = 0;
          }
          click2Prev = click2;

        }
        else{
          enc2Change = encoders[1]-enc2Change;
          enc2Count = enc2Count + enc2Change;
          if (enc2Count<0) enc2Count= 0;
          if (enc2Count>1) enc2Count= 1;
          chosenModOption = enc2Count;  
          enc2Change = encoders[1];
          Serial.println(LFOFrequency[chosenModSource]);
          if (click2 and !click2Prev){
            if (!chosenModOption) {
              modEditScreen = 1;
              if(chosenModSource == 0 or chosenModSource == 1){
                encoders[0] = 0;
                encoders[1] = 0;
                encoders[2] = 0;
                enc1Change = 0;
                enc2Change = 0;
                enc3Change = 0;
                enc1Count = LFOWaveShape[chosenModSource];
                enc2Count = LFOFrequency[chosenModSource];
                enc3Count = LFOAmplitude[chosenModSource];
              }
              else{
                encoders[0] = 0;
                encoders[1] = 0;
                encoders[2] = 0;
                enc1Change = 0;
                enc2Change = 0;
                enc3Change = 0;
                enc1Count = 0;
                enc2Count = modadsr[chosenModSource-2][0];
                enc3Count = modadsr[chosenModSource-2][4];
              }    
            }
            else {
              modAssignScreen = 1;
              encoders[0] = 0;
              encoders[1] = 0;
              encoders[2] = 0;
              enc1Change = 0;
              enc2Change = 0;
              enc3Change = 0;
              enc1Count = 0;
              enc2Count = 0;
              enc3Count = 0;
            }
            
            oled.fillScreen(BLACK);
          }
          click2Prev = click2;
  
          if (click1 and !click1Prev){
            optionScreen = 0;
            oled.fillScreen(BLACK);
            encoders[0] = 0;
            encoders[1] = 0;
            encoders[2] = 0;
            enc1Change = 0;
            enc2Change = 0;
            enc3Change = 0;
            enc1Count = chosenModSource;
            enc2Count = 0;
            enc3Count = 0;
          }
          click1Prev = click1;
        }
      }
      else{
        enc1Change = encoders[0]-enc1Change;
        enc1Count = enc1Count + enc1Change;
        if (enc1Count<0) enc1Count= 0;
        if (enc1Count>3) enc1Count= 3;
        chosenModSource = enc1Count;  
        enc1Change = encoders[0];
  
        if (click1 and !click1Prev){
          optionScreen = 1;
          encoders[0] = 0;
          encoders[1] = 0;
          encoders[2] = 0;
          enc1Change = 0;
          enc2Change = 0;
          enc3Change = 0;
          enc1Count = 0;
          enc2Count = 0;
          enc3Count = 0;
          oled.fillScreen(BLACK);
        }
        click1Prev = click1;
      }
      
      for (int i=0; i < numled; i++) {
        leds.setPixel(i, BLACK);
        leds.setBrightness(0);
        leds.show();
      }
    break;
  }
}

/*
 * Display code. This part lets the user see the 
 * different menus, the different controllable 
 * within each parameters, as well as what inputs
 * on the device can be used to control them.
 * 
 * Since the SSD1351 library from Adafruit is 
 * not buffered, display elements are manually 
 * updated locally while keeping most of the 
 * contents of the display static.
 */
void staticMenu() {
  switch (screen) {
  case 0: //Oscillator Screen
    if (arbSelect){
      digitalWrite(enc1LED,LOW);
      digitalWrite(enc2LED,LOW);
      digitalWrite(enc4LED,LOW);
       
      oled.setTextSize(1);
      oled.setTextColor(MAGENTA,BLACK);
      oled.setCursor(20, 2);
      oled.print("Waveform Editor");
      oled.drawRoundRect(0,0,127,11,6, MAGENTA);
      oled.drawFastHLine(0,70,127,WHITE);
      for (int s=0; s < 257; s++) {
        if ((s%2)==0){
          int8_t val = 50*(arbWave[s]/32767.0);
          if ((s == waveIdx) or (s == waveIdx-1)){
            waveDrawColor = RED;
          }
          else{
            waveDrawColor = WHITE;
          }
          if (val <=0){
             oled.drawFastVLine(s/2,70+1,-1*val,waveDrawColor);
             oled.drawFastVLine(s/2,70-50,50,BLACK);
             oled.drawLine(s/2,70+50,s/2,70+(-1*val)+1,BLACK);
             
          }
          else{
            oled.drawFastVLine(s/2,70-val,val,waveDrawColor);
            oled.drawFastVLine(s/2,70+1,70+50,BLACK);
            oled.drawLine(s/2,70-50,s/2,70-val-1,BLACK);
          }
        }
      }
    }
    else{
    //Light up active encoders
    digitalWrite(enc1LED,HIGH);
    digitalWrite(enc2LED,HIGH);
    digitalWrite(enc4LED,HIGH);  
    //Write out header
    oled.setTextSize(1);
    oled.setTextColor(WHITE,BLACK);
    oled.setCursor(35, 2);
    oled.print("Oscillators");
    oled.drawFastHLine(0,10,124, WHITE);
    oled.fillTriangle(127,10,124,13,124,7,YELLOW);
  
    //Show octave
    oled.setTextSize(1);
    oled.setCursor(5, 2);
    oled.setTextColor(WHITE,BLACK);
    if(octave>0){
      oled.print("+");
    }
    else if(octave==0){
      oled.print("+");
      oled.fillRect(16,0,19,9,BLACK);
    }
    oled.println(octave);
  
    for (byte i = 0; i<numOscillators; i++){
      oled.setTextColor(WHITE,BLACK);
      oled.setTextSize(1);
      oled.setCursor(100,(40*i)+24);
      oled.print("AMP");
      oled.setCursor(100,(40*i)+36);
      oled.print(waveAmplitude[i]);
      
      uint16_t waveColor = 0;
      if (i == chosenOscillator){
        oled.setTextColor(GREEN,BLACK);
        oled.setCursor(0,(40*i)+25);
        oled.drawRoundRect(10,(40*i)+18,45,30,5,GREEN);
        oled.drawFastHLine(58,(40*i)+34,int(waveAmplitude[i]*40)-1,GREEN);
        oled.drawFastHLine(58+int(waveAmplitude[i]*40),(40*i)+34,98-int(waveAmplitude[i]*40),BLACK);
        oled.drawCircle(0,(40*i)+32,8,RED);
        if (waveShape[i]==4){
          digitalWrite(enc3LED,HIGH);
          oled.drawRoundRect(12,(40*i)+22,41,22,5,BLUE);
          waveformEditEnable = 1;          
        }
        else{
          digitalWrite(enc3LED,LOW);
          oled.drawRoundRect(12,(40*i)+22,41,22,5,BLACK); 
          waveformEditEnable = 0;   
        }
        waveColor = RED;
      }
      else{
        oled.setTextColor(WHITE,BLACK);
        oled.drawRoundRect(10,(40*i)+18,45,30,5,WHITE);
        oled.drawFastHLine(58,(40*i)+34,int(waveAmplitude[i]*40),WHITE);
        oled.drawFastHLine(58+int(waveAmplitude[i]*40)+1,(40*i)+34,98-int(waveAmplitude[i]*40),BLACK);
        oled.drawCircle(0,(40*i)+32,8,BLACK);
        if (waveShape[i]==4){
          oled.drawRoundRect(12,(40*i)+22,41,22,5,BLACK);
          waveformEditEnable = 0;               
        }
        
        oled.drawRoundRect(12,(40*i)+22,41,22,5,BLACK);  
        
        waveColor = WHITE;
      }
  
      oled.setTextSize(1);
      oled.setCursor(0,(40*i)+29);
      if (i == 0){
        oled.print("N");
      }
      else{
        oled.print(i); 
      }
      
      if ((i == 1) or (i == 2)){
        switch(waveShape[i]){
          case 0://SINE
            oled.setCursor(16,(40*i)+26);
            oled.setTextColor(waveColor,BLACK);
            oled.setTextSize(2);
            oled.print("SIN");
            break;
          case 1://SAW
            oled.drawFastHLine(17, (40*i)+40, 8, waveColor);
            oled.drawLine(25, (40*i)+40, 40, (40*i)+24, waveColor);
            oled.drawFastVLine(40, (40*i)+24, 16, waveColor);
            oled.drawFastHLine(40, (40*i)+40, 8, waveColor);
            break;
          case 2://SQUARE
            oled.drawFastHLine(17, (40*i)+40, 8, waveColor);
            oled.drawFastVLine(25, (40*i)+24, 16, waveColor);
            oled.drawFastHLine(25, (40*i)+24, 15, waveColor);
            oled.drawFastVLine(40, (40*i)+24, 16, waveColor);
            oled.drawFastHLine(40, (40*i)+40, 8, waveColor);
            break;
          case 3://TRI
            oled.drawFastHLine(17, (40*i)+40, 8, waveColor);
            oled.drawLine(25, (40*i)+40, 33, (40*i)+24, waveColor);
            oled.drawLine(33, (40*i)+24, 40, (40*i)+40, waveColor);
            oled.drawFastHLine(40, (40*i)+40, 8, waveColor);
            break;
          case 4://ARB
            oled.setCursor(16,(40*i)+26);
            oled.setTextColor(waveColor,BLACK);
            oled.setTextSize(2);
            oled.print("ARB");
            break;
          case 5://PULSE
            oled.drawFastHLine(17, (40*i)+40, 12, waveColor);
            oled.drawFastVLine(29, (40*i)+24, 16, waveColor);
            oled.drawFastHLine(29, (40*i)+24, 7, waveColor);
            oled.drawFastVLine(36, (40*i)+24, 16, waveColor);
            oled.drawFastHLine(36, (40*i)+40, 12, waveColor);
            oled.setCursor(19,(40*i)+24);
            oled.setTextColor(waveColor,BLACK);
            oled.setTextSize(1);
            oled.print("P");
            break;
          case 6://REV SAW
            oled.drawFastHLine(17, (40*i)+40, 8, waveColor);
            oled.drawFastVLine(25, (40*i)+24, 16, waveColor);
            oled.drawLine(25, (40*i)+24, 40, (40*i)+40, waveColor);
            oled.drawFastHLine(40, (40*i)+40, 8, waveColor);
            break;
          case 7://SAMPLEHOLD
            oled.drawFastHLine(17, (40*i)+40, 12, waveColor);
            oled.drawFastVLine(29, (40*i)+24, 16, waveColor);
            oled.drawFastHLine(29, (40*i)+24, 7, waveColor);
            oled.drawFastVLine(36, (40*i)+24, 10, waveColor);
            oled.drawFastHLine(36, (40*i)+34, 5, waveColor);
            oled.drawFastVLine(41, (40*i)+34, 6, waveColor);
            oled.drawFastHLine(41, (40*i)+40, 7, waveColor);
            oled.setTextColor(waveColor,BLACK);
            oled.setTextSize(1);
            oled.setCursor(17,(40*i)+24);
            oled.print("S"); 
            oled.setCursor(22,(40*i)+31);
            oled.print("H"); 
            break;
          case 8://VAR TRI
            oled.drawFastHLine(17, (40*i)+40, 8, waveColor);
            oled.drawLine(25, (40*i)+40, 33, (40*i)+24, waveColor);
            oled.drawLine(33, (40*i)+24, 40, (40*i)+40, waveColor);
            oled.drawFastHLine(40, (40*i)+40, 8, waveColor);
            oled.setTextColor(waveColor,BLACK);
            oled.setTextSize(1);
            oled.setCursor(19,(40*i)+24);
            oled.print("V"); 
            break;
        }
      }
      else{//NOISE
        oled.drawFastHLine(17, 35, 8, WHITE);
        oled.drawLine(25, 35, 27, 26, WHITE);
        oled.drawLine(27, 26, 29, 42, WHITE);
        oled.drawLine(29, 42, 32, 24, WHITE);
        oled.drawLine(32, 24, 36, 41, WHITE);
        oled.drawLine(36, 41, 38, 25, WHITE);
        oled.drawLine(38, 25, 40, 35, WHITE);
        oled.drawFastHLine(40, 35, 8, WHITE);
      }
    }
    }
    break;

    case 1: //Main Envelope Screen
      digitalWrite(enc1LED,HIGH);
      digitalWrite(enc2LED,HIGH);      
      digitalWrite(enc3LED,LOW);
      digitalWrite(enc4LED,HIGH);  
      
      //Write out header
      oled.setTextSize(1);
      oled.setTextColor(WHITE,BLACK);
      oled.setCursor(27, 2);
      oled.print("Main Envelope");
      oled.drawFastHLine(3,10,121, WHITE);
      oled.fillTriangle(0,10,3,13,3,7,YELLOW);
      oled.fillTriangle(127,10,124,13,124,7,YELLOW);

      //Show octave
      oled.setTextSize(1);
      oled.setCursor(5, 2);
      oled.setTextColor(WHITE,BLACK);
      if(octave>0){
        oled.print("+");
      }
      else if(octave==0){
        oled.print("+");
        oled.fillRect(16,0,6,9,BLACK);
      }
      oled.println(octave);

      for (byte i = 0; i<4; i++){
        uint16_t waveColor = 0;
        if (i == chosenParameter){
          oled.drawRect((2*(i+1))+(30*i)-1,100,30,15,RED);
          color1 = RED;
          color2 = GREEN;
        }
        else{
          oled.drawRect((2*(i+1))+(30*i)-1,100,30,15,WHITE);
          color1 = WHITE;
          color2 = WHITE;
        }
        oled.setCursor((2*(i+1))+(30*i)+12,104);
        oled.setTextColor(color1,BLACK);
        oled.print(adsrNames[i]);

        int8_t circleLoc = 0;
        switch (i){
          case 0://Attack - 0-3000 in steps of 150
            circleLoc = 95-(adsr[i]/3000.0)*75.0;
            break;
          case 1://Decay - 0-3000 in steps of 150
            circleLoc = 95.0-(adsr[i]/3000.0)*75.0;
            break;
          case 2://Sustain - 0-1.0 in steps of 0.05
            circleLoc = 95.0-adsr[i]*75.0;
            break;
          case 3://Release - 0-3000 in steps of 150
            circleLoc = 95.0-(adsr[i]/3000.0)*75.0;
            break;
        }
        oled.drawLine((2*(i+1))+(30*i)+14, 100, (2*(i+1))+(30*i)+14, circleLoc, color2);
        oled.fillCircle((2*(i+1))+(30*i)+14, circleLoc, 3, color2);

        oled.drawLine((2*(i+1))+(30*i)+10,11,(2*(i+1))+(30*i)+10,circleLoc-1,BLACK);
        oled.drawLine((2*(i+1))+(30*i)+11,11,(2*(i+1))+(30*i)+11,circleLoc-2,BLACK);
        oled.drawLine((2*(i+1))+(30*i)+12,11,(2*(i+1))+(30*i)+12,circleLoc-3,BLACK);
        oled.drawLine((2*(i+1))+(30*i)+13,11,(2*(i+1))+(30*i)+13,circleLoc-4,BLACK);
        oled.drawLine((2*(i+1))+(30*i)+14,11,(2*(i+1))+(30*i)+14,circleLoc-4,BLACK);
        oled.drawLine((2*(i+1))+(30*i)+15,11,(2*(i+1))+(30*i)+15,circleLoc-4,BLACK);
        oled.drawLine((2*(i+1))+(30*i)+16,11,(2*(i+1))+(30*i)+16,circleLoc-3,BLACK);
        oled.drawLine((2*(i+1))+(30*i)+17,11,(2*(i+1))+(30*i)+17,circleLoc-2,BLACK);
        oled.drawLine((2*(i+1))+(30*i)+18,11,(2*(i+1))+(30*i)+18,circleLoc-1,BLACK);

        oled.drawLine((2*(i+1))+(30*i)+10,99,(2*(i+1))+(30*i)+10,circleLoc+1,BLACK);
        oled.drawLine((2*(i+1))+(30*i)+11,99,(2*(i+1))+(30*i)+11,circleLoc+2,BLACK);
        oled.drawLine((2*(i+1))+(30*i)+12,99,(2*(i+1))+(30*i)+12,circleLoc+3,BLACK);
        oled.drawLine((2*(i+1))+(30*i)+13,99,(2*(i+1))+(30*i)+13,circleLoc+4,BLACK);

        oled.drawLine((2*(i+1))+(30*i)+15,99,(2*(i+1))+(30*i)+15,circleLoc+4,BLACK);
        oled.drawLine((2*(i+1))+(30*i)+16,99,(2*(i+1))+(30*i)+16,circleLoc+3,BLACK);
        oled.drawLine((2*(i+1))+(30*i)+17,99,(2*(i+1))+(30*i)+17,circleLoc+2,BLACK);
        oled.drawLine((2*(i+1))+(30*i)+18,99,(2*(i+1))+(30*i)+18,circleLoc+1,BLACK);
      }
    break;

    case 2://Osc 2 Tune
      digitalWrite(enc1LED,HIGH);
      digitalWrite(enc2LED,HIGH);      
      digitalWrite(enc3LED,LOW);
      digitalWrite(enc4LED,HIGH);  
      
      //Write out header
      oled.setTextSize(1);
      oled.setTextColor(WHITE,BLACK);
      oled.setCursor(35, 2);
      oled.print("Osc 2 Tune");
      oled.drawFastHLine(3,10,121, WHITE);
      oled.fillTriangle(0,10,3,13,3,7,YELLOW);
      oled.fillTriangle(127,10,124,13,124,7,YELLOW);

      //Show octave
      oled.setTextSize(1);
      oled.setCursor(5, 2);
      oled.setTextColor(WHITE,BLACK);
      if(octave>0){
        oled.print("+");
      }
      else if(octave==0){
        oled.print("+");
        oled.fillRect(16,0,6,9,BLACK);
      }
      oled.println(octave);

      oled.drawCircle(64,70,34+semitonesTune/2.0+1,RED);
      oled.drawCircle(64,70,34+semitonesTune/2.0-1,RED);
      oled.drawCircle(64,70,34+semitonesTune/2.0+2,RED);
      oled.drawCircle(64,70,34+semitonesTune/2.0-3,RED);
      oled.drawCircle(64,70,34+semitonesTune/2.0,RED);
      oled.drawCircle(64,70,34+semitonesTune/2.0+3,BLACK);
      oled.drawCircle(64,70,34+semitonesTune/2.0-3,BLACK);
      if(semitonesTune<0){
        oled.setCursor(25, 121);
        if(semitonesTune>-10){
          oled.fillRect(97,121,8,8,BLACK);
        }
      }
      else{
        oled.setCursor(30, 121);
        oled.fillRect(25,121,5,8,BLACK);
        if(semitonesTune<10){
          oled.fillRect(95,121,8,8,BLACK);
        }
      }

      oled.setTextColor(RED,BLACK);
      oled.print("Semitones:");
      oled.print(semitonesTune);
      
      oled.drawCircle(64,70,15-1,GREEN);
      oled.drawCircle(64,70,15+1,GREEN);
      oled.drawCircle(64,70,15-3,GREEN);
      oled.drawCircle(64,70,15-3,BLACK);
      oled.drawCircle(64,70,15,GREEN);
      oled.setCursor(0, 18);
      oled.setTextColor(GREEN,BLACK);
      oled.print("Detune");
      oled.drawFastHLine(0,26,35, GREEN);
      oled.drawLine(35,26,52,60, GREEN);
      
      if(detunePercent<0){
        oled.setCursor(56, 67);
      }
      else{
        oled.setCursor(59, 67);
        oled.fillRect(56,67,3,8,BLACK);
        oled.fillRect(70,67,3,8,BLACK);
      }
      oled.print(detunePercent);
      oled.print("%");
      
    break;

    case 3://Filter
      digitalWrite(enc1LED,HIGH);
      digitalWrite(enc2LED,HIGH);      
      digitalWrite(enc3LED,LOW);
      digitalWrite(enc4LED,HIGH);  
      
      //Write out header
      oled.setTextSize(1);
      oled.setTextColor(WHITE,BLACK);
      oled.setCursor(47, 2);
      oled.print("Filter");
      oled.drawFastHLine(3,10,121, WHITE);
      oled.fillTriangle(0,10,3,13,3,7,YELLOW);
      oled.fillTriangle(127,10,124,13,124,7,YELLOW);
  
      //Show octave
      oled.setTextSize(1);
      oled.setCursor(5, 2);
      oled.setTextColor(WHITE,BLACK);
      if(octave>0){
        oled.print("+");
      }
      else if(octave==0){
        oled.print("+");
        oled.fillRect(16,0,6,9,BLACK);
      }
      oled.println(octave);
      
      oled.setCursor(0,30);
      oled.setTextColor(RED,BLACK);
      oled.print("F:");
      oled.print(filterFreq);
      if (filterFreq < 1000)oled.fillRect(30,30,6,7,BLACK);

      oled.setCursor(0,40);
      oled.setTextColor(GREEN,BLACK);
      oled.print("Q:");
      oled.print(filterQ);
      
      hOffset = 67*(filterFreq/3000.0)+56;
      vOffset = 64-filterQ*13;

      oled.fillRoundRect(0,70,hOffset,75,20,RED);
      oled.fillRect(0,70,20,75,RED);
      oled.fillRect(hOffset,70,128-(hOffset),75,BLACK);
      oled.drawFastHLine(hOffset-16,70,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-13,71,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-11,72,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-9,73,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-8,74,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-7,75,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-6,76,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-5,77,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-4,78,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-3,79,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-3,80,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-2,81,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-2,82,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-1,83,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-1,84,128-hOffset,BLACK);
      oled.drawFastHLine(hOffset-1,85,128-hOffset,BLACK);

      oled.fillCircle(hOffset-18,vOffset,3,GREEN);
      oled.drawCircle(hOffset-18,vOffset,4,BLACK);
      oled.drawCircle(hOffset-18,vOffset,5,BLACK);
      oled.drawFastHLine(hOffset-21,vOffset+4,6,BLACK);
      oled.drawFastHLine(hOffset-21,vOffset-4,6,BLACK);
      
    break;
    
    case 4://Joystick Assign
      digitalWrite(enc1LED,HIGH);
      digitalWrite(enc2LED,HIGH);      
      digitalWrite(enc3LED,LOW);
      digitalWrite(enc4LED,HIGH);  
      
      //Write out header
      oled.setTextSize(1);
      oled.setTextColor(WHITE,BLACK);
      oled.setCursor(40, 2);
      oled.print("Joystick");
      oled.drawFastHLine(3,10,121, WHITE);
      oled.fillTriangle(0,10,3,13,3,7,YELLOW);
      oled.fillTriangle(127,10,124,13,124,7,YELLOW);
  
      //Show octave
      oled.setTextSize(1);
      oled.setCursor(5, 2);
      oled.setTextColor(WHITE,BLACK);
      if(octave>0){
        oled.print("+");
      }
      else if(octave==0){
        oled.print("+");
        oled.fillRect(16,0,6,9,BLACK);
      }
      oled.println(octave);

      oled.drawFastHLine(20,40,40, WHITE);
      oled.drawFastVLine(10,50,40, WHITE);
      oled.drawFastHLine(20,100,40, WHITE);
      oled.drawFastVLine(70,50,40, WHITE);

      oled.drawLine(60,40,70,50, WHITE);
      oled.drawLine(58,40,70,52, WHITE);
      oled.drawLine(56,40,70,54, WHITE);
      
      oled.drawLine(70,90,60,100, WHITE);
      oled.drawLine(70,88,58,100, WHITE);
      oled.drawLine(70,86,56,100, WHITE);
      
      oled.drawLine(20,100,10,90, WHITE);
      oled.drawLine(22,100,10,88, WHITE);
      oled.drawLine(24,100,10,86, WHITE);
      
      oled.drawLine(10,50,20,40, WHITE);
      oled.drawLine(10,52,22,40, WHITE);
      oled.drawLine(10,54,24,40, WHITE);
      
      oled.fillCircle(40+circX,70+circY,5,MAGENTA);
      if (circYPrev != circY || circXPrev != circX){
        oled.fillCircle(40+circXPrev,70+circYPrev,5,BLACK);
      }

      oled.setTextColor(color1, BLACK);
      switch(joyYMod){
        case 0:
          oled.setCursor(18,32);
          oled.println("Disabled");
        break;
        case 1:
          oled.setCursor(27,32);
          oled.println("Pitch");
          oled.fillRect(15,32,12,7,BLACK);
          oled.fillRect(57,32,12,7,BLACK);
        break;
        case 2:
          oled.setCursor(25,32);
          oled.println("Filter");
        break;
      }
      
      oled.setTextColor(color2, BLACK);
      switch(joyXMod){
        case 0:
          oled.setCursor(72,68);
          oled.println("Disabled");
        break;
        case 1:
          oled.setCursor(72,68);
          oled.println("Pitch");
          oled.fillRect(102,68,18,9,BLACK);
        break;
        case 2:
          oled.setCursor(72,68);
          oled.println("Filter");

        break;
      }
      circYPrev = circY;
      circXPrev = circX;    
    break;

    case 5://Mod Sources
      if(optionScreen){
        if(modEditScreen){
          digitalWrite(enc1LED,HIGH);
          digitalWrite(enc2LED,HIGH);
          digitalWrite(enc3LED,HIGH);
          digitalWrite(enc4LED,LOW); 
          
          oled.setTextSize(1);
          oled.setTextColor(MAGENTA,BLACK);
          oled.setCursor(48, 2);
          oled.println("Editor");
          oled.drawRoundRect(0,0,127,11,6, MAGENTA);

          oled.fillCircle(5,20,2,GREEN);
          
          if (chosenModSource == 0 or chosenModSource == 1){
            oled.drawFastHLine(0,70,128,WHITE);
            oled.drawFastVLine(64,70,60,WHITE);
            
            oled.setCursor(48, 20);
            oled.setTextColor(WHITE,BLACK);
            oled.println("SHAPE");
            oled.drawFastVLine(62,28,12,WHITE);
            oled.fillTriangle(65,38,59,38,62,41,WHITE);

            oled.setTextColor(WHITE,BLACK);
            oled.setCursor(5, 74);
            oled.println("FREQUENCY");
            oled.drawFastVLine(32,82,12,WHITE);
            oled.fillTriangle(32,97,29,94,35,94,WHITE);
            oled.setTextColor(GREEN,BLACK);
            oled.setTextSize(2);
            if(LFOFrequency[chosenModSource]<10.0){
              oled.setCursor(9, 102);
              oled.fillRect(0,102,8,20,BLACK);
              oled.fillRect(55,102,8,20,BLACK);
            }
            else{
              oled.setCursor(0, 102);
            }
            oled.println(LFOFrequency[chosenModSource]);

            oled.setTextColor(WHITE,BLACK);
            oled.setTextSize(1);
            oled.setCursor(70, 74);
            oled.println("AMPLITUDE");
            oled.drawFastVLine(97,82,12,WHITE);
            oled.fillTriangle(97,97,94,94,100,94,WHITE);
            oled.setTextColor(BLUE,BLACK);
            oled.setTextSize(2);
            oled.setCursor(73, 102);
            oled.println(LFOAmplitude[chosenModSource]);
            
            switch(LFOWaveShape[chosenModSource]){
              case 0://SINE
                oled.setCursor(46,46);
                oled.setTextColor(RED,BLACK);
                oled.setTextSize(2);
                oled.print("SIN");
                break;
              case 1://SAW
                oled.drawFastHLine(46, 60, 8, RED);
                oled.drawLine(54, 60, 69, 44, RED);
                oled.drawFastVLine(69, 44, 16, RED);
                oled.drawFastHLine(69, 60, 8, RED);
                break;
              case 2://SQUARE
                oled.drawFastHLine(46, 60, 8, RED);
                oled.drawFastVLine(54, 44, 16, RED);
                oled.drawFastHLine(54, 44, 15, RED);
                oled.drawFastVLine(69, 44, 16, RED);
                oled.drawFastHLine(69, 60, 8, RED);
                break;
              case 3://TRI
                oled.drawFastHLine(46, 60, 8, RED);
                oled.drawLine(54, 60, 62, 44, RED);
                oled.drawLine(62, 44, 69, 60, RED);
                oled.drawFastHLine(69, 60, 8, RED);
                break;
              case 4://ARB
                oled.setCursor(45,46);
                oled.setTextColor(RED,BLACK);
                oled.setTextSize(2);
                oled.print("ARB");
                break;
              case 5://PULSE
                oled.drawFastHLine(46, 60, 12, RED);
                oled.drawFastVLine(59, 44, 16, RED);
                oled.drawFastHLine(59, 44, 7, RED);
                oled.drawFastVLine(65, 44, 16, RED);
                oled.drawFastHLine(65, 60, 12, RED);
                oled.setCursor(49,44);
                oled.setTextColor(RED,BLACK);
                oled.setTextSize(1);
                oled.print("P");
                break;
              case 6://REV SAW
                oled.drawFastHLine(46, 60, 8, RED);
                oled.drawFastVLine(54, 44, 16, RED);
                oled.drawLine(54, 44, 69, 60, RED);
                oled.drawFastHLine(69, 60, 8, RED);
                break;
              case 7://SAMPLEHOLD
                oled.drawFastHLine(46, 60, 12, RED);
                oled.drawFastVLine(59, 44, 16, RED);
                oled.drawFastHLine(59, 44, 7, RED);
                oled.drawFastVLine(66, 44, 10, RED);
                oled.drawFastHLine(66, 54, 5, RED);
                oled.drawFastVLine(70, 54, 6, RED);
                oled.drawFastHLine(70, 60, 7, RED);
                oled.setTextColor(RED,BLACK);
                oled.setTextSize(1);
                oled.setCursor(46,44);
                oled.print("S"); 
                oled.setCursor(51,51);
                oled.print("H"); 
                break;
              case 8://VAR TRI
                oled.drawFastHLine(46, 60, 8, RED);
                oled.drawLine(54, 60, 62, 44, RED);
                oled.drawLine(62, 44, 69, 60, RED);
                oled.drawFastHLine(69, 60, 8, RED);
                oled.setTextColor(RED,BLACK);
                oled.setTextSize(1);
                oled.setCursor(49,44);
                oled.print("V"); 
                break;
            }
          }
          else{
            oled.setCursor(36, 20);
            oled.setTextColor(WHITE,BLACK);
            oled.print("Depth:");
            oled.setTextColor(BLUE,BLACK);
            oled.print(modadsr[chosenModSource-2][4]);
            oled.setTextColor(WHITE,BLACK);
            
            for (byte i = 0; i<4; i++){
              uint16_t waveColor = 0;
              if (i == chosenParameter){
                oled.drawRect((2*(i+1))+(30*i)-1,100,30,15,RED);
                color1 = RED;
                color2 = GREEN;
              }
              else{
                oled.drawRect((2*(i+1))+(30*i)-1,100,30,15,WHITE);
                color1 = WHITE;
                color2 = WHITE;
              }
              oled.setCursor((2*(i+1))+(30*i)+12,104);
              oled.setTextColor(color1,BLACK);
              oled.print(adsrNames[i]);
      
              int8_t circleLoc = 0;
              switch (i){
                case 0://Attack - 0-3000 in steps of 150
                  circleLoc = 95-(modadsr[chosenModSource-2][i]/3000.0)*60.0;
                  break;
                case 1://Decay - 0-3000 in steps of 150
                  circleLoc = 95.0-(modadsr[chosenModSource-2][i]/3000.0)*60.0;
                  break;
                case 2://Sustain - 0-1.0 in steps of 0.05
                  circleLoc = 95.0-modadsr[chosenModSource-2][i]*60.0;
                  break;
                case 3://Release - 0-3000 in steps of 150
                  circleLoc = 95.0-(modadsr[chosenModSource-2][i]/3000.0)*60.0;
                  break;
              }
              oled.drawLine((2*(i+1))+(30*i)+14, 100, (2*(i+1))+(30*i)+14, circleLoc, color2);
              oled.fillCircle((2*(i+1))+(30*i)+14, circleLoc, 3, color2);
      
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
        }
        else if (modAssignScreen){
          digitalWrite(enc1LED,HIGH);
          digitalWrite(enc2LED,HIGH);
          digitalWrite(enc3LED,HIGH);
          digitalWrite(enc4LED,LOW); 
          
          oled.setTextSize(1);
          oled.setTextColor(MAGENTA,BLACK);
          oled.setCursor(48, 2);
          oled.println("Assign");
          oled.drawRoundRect(0,0,127,11,6, MAGENTA);

          oled.fillCircle(5,20,2,GREEN);

          if (chosenModSource == 0 or chosenModSource == 1){
            for (byte m = 0; m < 4; m++){
              if (m==chosenModDestination) {
                color1 = BLUE;
                color2 = BLUE;
              }
              else {
                color1 = BLACK;
                color2 = WHITE;
              }
      
              oled.drawFastHLine(5,32+m*26,35,color1);
              oled.fillTriangle(43,32+m*26,40,35+m*26,40,29+m*26,color1);
              if(LFODest[chosenModSource][m])oled.fillCircle(100,32+m*26,3,color2);
              else oled.drawCircle(100,32+m*26,3,color2);
              oled.setCursor(50,29+m*26);
              oled.setTextColor(color2,BLACK);
              switch(m){
                case 0:
                  oled.println("OSC 1");
                break;
                case 1:
                  oled.println("OSC 2");
                break;
                case 2:
                  oled.println("Filter");
                break; 
                case 3:
                  if (chosenModSource == 0)oled.println("LFO 2");
                  else oled.println("LFO 1");
                break;
              } 
            }
          }
          else{
            for (byte m = 0; m < 5; m++){
              if (m==chosenModDestination) {
                color1 = BLUE;
                color2 = BLUE;
              }
              else {
                color1 = BLACK;
                color2 = WHITE;
              }
      
              oled.drawFastHLine(5,32+m*20,35,color1);
              oled.fillTriangle(43,32+m*20,40,35+m*20,40,29+m*20,color1);
              if(envDest[chosenModSource-2][m])oled.fillCircle(100,32+m*20,3,color2);
              else oled.drawCircle(100,32+m*20,3,color2);
              oled.setCursor(50,29+m*20);
              oled.setTextColor(color2,BLACK);
              switch(m){
                case 0:
                  oled.println("OSC 1");
                break;
                case 1:
                  oled.println("OSC 2");
                break;
                case 2:
                  oled.println("Filter");
                break; 
                case 3:
                  oled.println("LFO 1");
                break;
                case 4:
                  oled.println("LFO 2");
                break;  
              } 
            }
          }
        }
        else{
          digitalWrite(enc1LED,HIGH);
          digitalWrite(enc2LED,HIGH);
          digitalWrite(enc3LED,LOW);
          digitalWrite(enc4LED,LOW); 

          oled.fillCircle(5,20,2,RED);
          
          oled.setTextSize(1);
          oled.setTextColor(MAGENTA,BLACK);
          oled.setCursor(50, 2);
          switch(chosenModSource){
              case 0:
                oled.println("LFO 1");
              break;
              case 1:
                oled.println("LFO 2");
              break;
              case 2:
                oled.println("ENV 1");
              break; 
              case 3:
                oled.println("ENV 2");
              break;
            } 
          oled.drawRoundRect(0,0,127,11,6, MAGENTA);

          for (byte o=0;o<2;o++){
            if (o==chosenModOption) {
              color1 = GREEN;
              color2 = GREEN;
            }
            else{
              color1 = WHITE;
              color2 = BLACK;
            }
            oled.drawCircle(35+o*58,70,25,color1);
            oled.drawCircle(35+o*58,70,20,color2);
            oled.fillTriangle(35+o*58,97,30+o*58,102,40+o*58,102,color2);
            oled.fillTriangle(35+o*58,43,30+o*58,38,40+o*58,38,color2);

            
            oled.setTextColor(color1,BLACK);
            if(!o){
              oled.setCursor(24,67);
              oled.println("Edit");
            }
            else{
              oled.setCursor(76,67);
              oled.println("Assign");
            }
          }
          
        }
      }
      else{
        digitalWrite(enc1LED,HIGH);
        digitalWrite(enc2LED,LOW);      
        digitalWrite(enc3LED,LOW);
        digitalWrite(enc4LED,HIGH);  
        
        //Write out header
        oled.setTextSize(1);
        oled.setTextColor(WHITE,BLACK);
        oled.setCursor(35, 2);
        oled.print("Mod Sources");
        oled.drawFastHLine(3,10,125, WHITE);
        oled.fillTriangle(0,10,3,13,3,7,YELLOW);
    
        //Show octave
        oled.setTextSize(1);
        oled.setCursor(5, 2);
        oled.setTextColor(WHITE,BLACK);
        if(octave>0){
          oled.print("+");
        }
        else if(octave==0){
          oled.print("+");
          oled.fillRect(16,0,6,9,BLACK);
        }
        oled.println(octave);
  
        for (byte m = 0; m < 4; m++){
          if (m==chosenModSource) color1 = RED;
          else color1 = WHITE;
  
          oled.drawRoundRect(0,23+m*25,127,20,5,color1);
          oled.setCursor(50,29+m*26);
          oled.setTextColor(color1,BLACK);
          switch(m){
            case 0:
              oled.println("LFO 1");
            break;
            case 1:
              oled.println("LFO 2");
            break;
            case 2:
              oled.println("ENV 1");
            break; 
            case 3:
              oled.println("ENV 2");
            break;
          } 
        }
      }
    break;
  }
}
