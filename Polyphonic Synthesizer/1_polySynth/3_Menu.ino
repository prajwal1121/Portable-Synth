byte click1Prev = 0;

int menuCount = 0;
int menuChange = 0;
byte chosenOscPrev = 0;

float valCount = 0;
int valChange = 0;

float aCount = 0;
int aChange = 0;

byte chosenOscillator = 0;

byte chosenParameter = 0;

void menuCheck() {
  switch (screen){
    case 2:
      //Menu Scrolling
      menuChange = encoders[0]-menuChange;
      menuCount = menuCount + menuChange;
      if (menuCount > 2){
        screen = 3;
        menuCount = 0;
        menuChange = 0;
        encoders[0] = 0;
        valCount = adsr[0];
        valChange = 0;
        encoders[2] = 0;
        aCount = 0;
        aChange = 0;
        encoders[1] = 0;
        break;
      }
      if (menuCount < 0){
        screen = 1;
        menuCount = 0;
        menuChange = 0;
        encoders[0] = 0;
        valCount = semitonesTune;
        valChange = 0;
        encoders[2] = 0;
        aCount = detunePercent;
        aChange = 0;
        encoders[1] = 0;
        break;
      }
      chosenOscillator = menuCount;
      if (chosenOscillator != chosenOscPrev){
        valChange = 0;
        encoders[1] = 0;
        valCount = waveAmplitude[chosenOscillator];
        chosenOscPrev = chosenOscillator; 
      }
      menuChange = encoders[0];
    
      //Amplitude Scrolling
      valChange = encoders[1]-valChange;
      valCount = valCount + 0.1*valChange;
      if (valCount < 0) valCount = 0;
      if (valCount > 1.0) valCount = 1.0;
      waveAmplitude[chosenOscillator] = valCount;
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
      valChange = encoders[1];
      
      if (click1 and !click1Prev){
        switchWave(chosenOscillator);
      }
      click1Prev = click1;
      break;

    case 1:
      //Menu Scrolling
      menuChange = encoders[0]-menuChange;
      menuCount = menuCount + menuChange;
      if (menuCount > 0){
        screen = 2;
        menuCount = 0;
        menuChange = 0;
        encoders[0] = 0;
        valCount = waveAmplitude[0];
        valChange = 0;
        encoders[2] = 0;
        aCount = 0;
        aChange = 0;
        encoders[1] = 0;
        break;
      }
      if (menuCount < 0){
        screen = 0;
        menuCount = 0;
        menuChange = 0;
        encoders[0] = 0;
        valCount = lfoAmplitude;
        valChange = 0;
        encoders[2] = 0;
        aCount = lfoFrequency;
        aChange = 0;
        encoders[1] = 0;
        break;
      }
      menuChange = encoders[0];

      //Semitone Scrolling
      valChange = encoders[1]-valChange;
      valCount = valCount + valChange;
      if (valCount < -24) valCount = -24;
      if (valCount > 24) valCount = 24;
      semitonesTune = valCount;
      valChange = encoders[1];
      
      //Detune Scrolling
      aChange = encoders[2]-aChange;
      aCount = aCount + aChange;
      if (aCount < -5) aCount = -5;
      if (aCount > 5) aCount = 5;
      detunePercent = aCount;
      detuneFactor = 1.0 + (detunePercent/100.0);
      aChange = encoders[2];
      break;
      
    case 0:
      //Menu Scrolling
      menuChange = encoders[0]-menuChange;
      menuCount = menuCount + menuChange;
      if (menuCount > 0){
        screen = 1;
        menuCount = 0;
        menuChange = 0;
        encoders[0] = 0;
        valCount = semitonesTune;
        valChange = 0;
        encoders[2] = 0;
        aCount = detunePercent;
        aChange = 0;
        encoders[1] = 0;
        break;
      }
      if (menuCount < 0){
        menuCount = 0;
        menuChange = 0;
        encoders[0] = 0;
        break;
      }
      menuChange = encoders[0];

      if (click1 and !click1Prev){
        switchWave(3);
      }
      click1Prev = click1;

      //Amplitude Scrolling
      valChange = encoders[1]-valChange;
      valCount = valCount + 0.1*valChange;
      if (valCount < 0) valCount = 0;
      if (valCount > 1.0) valCount = 1.0;
      lfoAmplitude = valCount;
      lfo.amplitude(lfoAmplitude);
      valChange = encoders[1];
      
      //Frequency Scrolling
      aChange = encoders[2]-aChange;
      aCount = aCount + 0.1*aChange;
      if (aCount < 0) aCount = 0;
      lfoFrequency = aCount;
      lfo.frequency(lfoFrequency);
      aChange = encoders[2];
    
      break;

    case 3:
      //Menu Scrolling
      menuChange = encoders[0]-menuChange;
      menuCount = menuCount + menuChange;
      if (menuCount > 3){
        screen = 4;
        menuCount = 0;
        menuChange = 0;
        encoders[0] = 0;
        valCount = filterFreq;
        valChange = 0;
        encoders[2] = 0;
        aCount = filterQ;
        aChange = 0;
        encoders[1] = 0;
        break;
      }
      if (menuCount < 0){
        screen = 2;
        menuCount = 0;
        menuChange = 0;
        encoders[0] = 0;
        valCount = waveAmplitude[0];
        valChange = 0;
        encoders[1] = 0;
        aCount = 0;
        aChange = 0;
        encoders[2] = 0;
        break;
      }
      menuChange = encoders[0];
      
      if (menuCount != chosenParameter){
        valChange = 0;
        encoders[1] = 0;
        valCount = adsr[menuCount];
        chosenParameter = menuCount;
      }

      //Parameter Scrolling
      valChange = encoders[1]-valChange;
      switch (menuCount){
        case 0://Attack - 0-3000 in steps of 150
          valCount = valCount + 150*valChange;
          if (valCount > 3000) valCount = 3000;
          break;
        case 1://Decay - 0-3000 in steps of 150
          valCount = valCount + 150*valChange;
          if (valCount > 3000) valCount = 3000;
          break;
        case 2://Sustain - 0-1.0 in steps of 0.05
          valCount = valCount + 0.05*valChange;
          if (valCount > 1.0) valCount = 1.0;
          break;
        case 3://Release - 0-3000 in steps of 150
          valCount = valCount + 150*valChange;
          if (valCount > 3000) valCount = 3000;
          break;
      }
      if (valCount < 0) valCount = 0;
      adsr[menuCount] = valCount;
      updateEnvelope();
      valChange = encoders[1];
      
      break;

    case 4:
      //Menu Scrolling
      menuChange = encoders[0]-menuChange;
      menuCount = menuCount + menuChange;
      if (menuCount > 0){
        menuCount = 0;
        menuChange = 0;
        encoders[0] = 0;
        break;
      }
      if (menuCount < 0){
        screen = 3;
        menuCount = 0;
        menuChange = 0;
        encoders[0] = 0;
        valCount = adsr[0];
        valChange = 0;
        encoders[2] = 0;
        aCount = 0;
        aChange = 0;
        encoders[1] = 0;
        break;
      }
      menuChange = encoders[0];

      //Freqency Scrolling
      valChange = encoders[1]-valChange;
      valCount = valCount + 25*valChange;
      if (valCount < 100)valCount = 100;
      if (valCount > 3000)valCount = 3000;
      filterFreq = valCount;
      updateFilter();
      valChange = encoders[1];
      
      //Resonance Scrolling
      aChange = encoders[2]-aChange;
      aCount = aCount + 0.1*aChange;
      if (aCount < 0) aCount = 0;
      filterQ = aCount;
      updateFilter();
      aChange = encoders[2];
      break;
  }
  Serial.println(screen);
}

void staticMenu() {
  display.clearDisplay();
  switch (screen){
    case 2:
      //Write out header
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(35, 2);
      display.print("Oscillators");
      display.drawLine(0,10,127,10, WHITE);
  
      //Show octave
      display.setTextSize(1);
      display.setCursor(3, 2);
      display.setTextColor(SSD1306_WHITE);
      display.println(octave);
  
      for (byte i = 0; i<numOscillators; i++){
        display.setTextColor(SSD1306_WHITE);
        display.setTextSize(1);
        display.setCursor((2*(i+1))+(40*i)+11, 41);
        display.print("AMP");
        display.setCursor((2*(i+1))+(40*i)+8, 50);
        display.print(waveAmplitude[i]);
        
        uint16_t waveColor = 0;
        if (i == chosenOscillator){
          display.fillRoundRect((2*(i+1))+(40*i),15,40,25,5,SSD1306_WHITE);
          waveColor = SSD1306_BLACK;
        }
        else{
          display.drawRoundRect((2*(i+1))+(40*i),15,40,25,5,SSD1306_WHITE);
          waveColor = SSD1306_WHITE;
        }
  
        if ((i == 1) or (i == 2)){
          switch(waveShape[i]){
            case 0:
              display.setCursor((2*(i+1))+(40*i)+3, 20);
              display.setTextColor(waveColor);
              display.setTextSize(2);
              display.print("SIN");
              break;
            case 1:
              display.drawFastHLine((2*(i+1))+(40*i)+5, 34, 8, waveColor);
              display.drawLine((2*(i+1))+(40*i)+13, 34, (2*(i+1))+(40*i)+28, 19, waveColor);
              display.drawFastVLine((2*(i+1))+(40*i)+28, 19, 15, waveColor);
              display.drawFastHLine((2*(i+1))+(40*i)+28, 34, 8, waveColor);
              break;
            case 2:
              display.drawFastHLine((2*(i+1))+(40*i)+5, 34, 8, waveColor);
              display.drawFastVLine((2*(i+1))+(40*i)+13, 20, 15, waveColor);
              display.drawFastHLine((2*(i+1))+(40*i)+13, 19, 15, waveColor);
              display.drawFastVLine((2*(i+1))+(40*i)+28, 19, 15, waveColor);
              display.drawFastHLine((2*(i+1))+(40*i)+28, 34, 8, waveColor);
              break;
            case 3:
              display.drawFastHLine((2*(i+1))+(40*i)+5, 34, 8, waveColor);
              display.drawLine((2*(i+1))+(40*i)+13, 34, (2*(i+1))+(40*i)+22, 19, waveColor);
              display.drawLine((2*(i+1))+(40*i)+28, 34, (2*(i+1))+(40*i)+22, 19, waveColor);
              display.drawFastHLine((2*(i+1))+(40*i)+28, 34, 8, waveColor);
              break;
            case 4:
              display.setCursor((2*(i+1))+(40*i)+3, 20);
              display.setTextColor(waveColor);
              display.setTextSize(2);
              display.print("ARB");
              break;
            case 5:
              display.drawFastHLine((2*(i+1))+(40*i)+5, 34, 12, waveColor);
              display.drawFastVLine((2*(i+1))+(40*i)+17, 20, 15, waveColor);
              display.drawFastHLine((2*(i+1))+(40*i)+17, 19, 7, waveColor);
              display.drawFastVLine((2*(i+1))+(40*i)+24, 19, 15, waveColor);
              display.drawFastHLine((2*(i+1))+(40*i)+24, 34, 12, waveColor);
              display.setCursor((2*(i+1))+(40*i)+6, 19);
              display.setTextColor(waveColor);
              display.setTextSize(1);
              display.print("P");
              break;
            case 6:
              display.drawFastHLine((2*(i+1))+(40*i)+5, 34, 8, waveColor);
              display.drawFastVLine((2*(i+1))+(40*i)+13, 19, 15, waveColor);
              display.drawLine((2*(i+1))+(40*i)+28, 34, (2*(i+1))+(40*i)+13, 19, waveColor);
              display.drawFastHLine((2*(i+1))+(40*i)+28, 34, 8, waveColor);
              break;
            case 7:
              display.drawFastHLine((2*(i+1))+(40*i)+5, 34, 12, waveColor);
              display.drawFastVLine((2*(i+1))+(40*i)+17, 20, 15, waveColor);
              display.drawFastHLine((2*(i+1))+(40*i)+17, 19, 7, waveColor);
              display.drawFastVLine((2*(i+1))+(40*i)+24, 19, 10, waveColor);
              display.drawFastHLine((2*(i+1))+(40*i)+24, 29, 5, waveColor);
              display.drawFastVLine((2*(i+1))+(40*i)+29, 29, 5, waveColor);
              display.drawFastHLine((2*(i+1))+(40*i)+29, 34, 7, waveColor);
              display.setTextColor(waveColor);
              display.setTextSize(1);
              display.setCursor((2*(i+1))+(40*i)+6, 19);
              display.print("S"); 
              display.setCursor((2*(i+1))+(40*i)+11, 26);
              display.print("H"); 
              break;
            case 8:
              display.drawFastHLine((2*(i+1))+(40*i)+5, 34, 8, waveColor);
              display.drawLine((2*(i+1))+(40*i)+13, 34, (2*(i+1))+(40*i)+22, 19, waveColor);
              display.drawLine((2*(i+1))+(40*i)+28, 34, (2*(i+1))+(40*i)+22, 19, waveColor);
              display.drawFastHLine((2*(i+1))+(40*i)+28, 34, 8, waveColor);
              display.setTextColor(waveColor);
              display.setTextSize(1);
              display.setCursor((2*(i+1))+(40*i)+6, 19);
              display.print("V"); 
              break;
          }
        }
        else{
          display.drawFastHLine(7, 27, 8, waveColor);
          display.drawLine(15, 27, 17, 19, waveColor);
          display.drawLine(17, 19, 19, 32, waveColor);
          display.drawLine(19, 32, 22, 20, waveColor);
          display.drawLine(22, 20, 24, 32, waveColor);
          display.drawLine(24, 32, 26, 17, waveColor);
          display.drawLine(26, 17, 28, 31, waveColor);
          display.drawLine(28, 31, 30, 27, waveColor);
          display.drawFastHLine(30, 27, 8, waveColor);
        }
      }
      break;
    
    case 1:
      //Write out header
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(35, 2);
      display.print("TUNE OSC 2");

      display.drawRect(0,10,127, 53, SSD1306_WHITE);
      display.drawRect(2,12,123, 49, SSD1306_WHITE);
      display.drawFastHLine(0,35,127, SSD1306_WHITE);
      display.drawFastHLine(0,37,127, SSD1306_WHITE);

      
      //Show octave
      display.setTextSize(1);
      display.setCursor(3, 2);
      display.setTextColor(SSD1306_WHITE);
      display.println(octave);

      //Show semitone suning
      display.setCursor(10, 20);
      display.print("Semitones:");
      display.setCursor(82, 20);
      display.print(semitonesTune);

      //Show detune percentage
      display.setCursor(10, 45);
      display.print("Detune:");
      display.setCursor(82, 45);
      display.print(detunePercent);
      display.print("%");
      
      break;
      
    case 0:
      //Write out header
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(50, 2);
      display.print("LFO");
      display.drawFastHLine(64,10,64, SSD1306_WHITE);
      display.fillRect(0,10,64,64, SSD1306_WHITE);
      display.drawFastVLine(127, 10, 53, SSD1306_WHITE);
      display.drawFastHLine(64,63,64, SSD1306_WHITE);
      display.drawFastHLine(64,36,64, SSD1306_WHITE);
      
      //Show octave
      display.setCursor(3, 2);
      display.println(octave);

      //Show Amplitude
      display.setCursor(68, 12);
      display.print("Amplitude");
      display.setCursor(82, 25);
      display.print(lfoAmplitude);

      //Show Frequency
      display.setCursor(68, 38);
      display.print("Frequency");
      display.setCursor(82, 51);
      display.print(lfoFrequency);

      switch(lfoShape){
        case 0:
          display.setCursor(13, 30);
          display.setTextColor(SSD1306_BLACK);
          display.setTextSize(2);
          display.print("SIN");
          break;
        case 1:
          display.drawFastHLine(15, 44, 8, SSD1306_BLACK);
          display.drawLine(23, 44, 38, 29, SSD1306_BLACK);
          display.drawFastVLine(38, 29, 15, SSD1306_BLACK);
          display.drawFastHLine(38, 44, 8, SSD1306_BLACK);
          break;
        case 2:
          display.drawFastHLine(15, 44, 8, SSD1306_BLACK);
          display.drawFastVLine(23, 30, 15, SSD1306_BLACK);
          display.drawFastHLine(23, 29, 15, SSD1306_BLACK);
          display.drawFastVLine(38, 29, 15, SSD1306_BLACK);
          display.drawFastHLine(38, 44, 8, SSD1306_BLACK);
          break;
        case 3:
          display.drawFastHLine(15, 44, 8, SSD1306_BLACK);
          display.drawLine(23, 44, 32, 29, SSD1306_BLACK);
          display.drawLine(38, 44, 32, 29, SSD1306_BLACK);
          display.drawFastHLine(38, 44, 8, SSD1306_BLACK);
          break;
        case 4:
          display.setCursor(13, 30);
          display.setTextColor(SSD1306_BLACK);
          display.setTextSize(2);
          display.print("ARB");
          break;
        case 5:
          display.drawFastHLine(15, 44, 12, SSD1306_BLACK);
          display.drawFastVLine(27, 30, 15, SSD1306_BLACK);
          display.drawFastHLine(27, 29, 7, SSD1306_BLACK);
          display.drawFastVLine(34, 29, 15, SSD1306_BLACK);
          display.drawFastHLine(34, 44, 12, SSD1306_BLACK);
          display.setCursor(16, 29);
          display.setTextColor(SSD1306_BLACK);
          display.setTextSize(1);
          display.print("P");
          break;
        case 6:
          display.drawFastHLine(15, 44, 8, SSD1306_BLACK);
          display.drawFastVLine(23, 29, 15, SSD1306_BLACK);
          display.drawLine(38, 44, 23, 29, SSD1306_BLACK);
          display.drawFastHLine(38, 44, 8, SSD1306_BLACK);
          break;
        case 7:
          display.drawFastHLine(15, 44, 12, SSD1306_BLACK);
          display.drawFastVLine(27, 30, 15, SSD1306_BLACK);
          display.drawFastHLine(27, 29, 7, SSD1306_BLACK);
          display.drawFastVLine(34, 29, 10, SSD1306_BLACK);
          display.drawFastHLine(34, 39, 5, SSD1306_BLACK);
          display.drawFastVLine(39, 39, 5, SSD1306_BLACK);
          display.drawFastHLine(39, 44, 7, SSD1306_BLACK);
          display.setTextColor(SSD1306_BLACK);
          display.setTextSize(1);
          display.setCursor(16, 29);
          display.print("S"); 
          display.setCursor(21, 36);
          display.print("H"); 
          break;
        case 8:
          display.drawFastHLine(15, 44, 8, SSD1306_BLACK);
          display.drawLine(23, 44, 32, 29, SSD1306_BLACK);
          display.drawLine(38, 44, 32, 29, SSD1306_BLACK);
          display.drawFastHLine(38, 44, 8, SSD1306_BLACK);
          display.setTextColor(SSD1306_BLACK);
          display.setTextSize(1);
          display.setCursor(16, 29);
          display.print("V"); 
          break;
      }
      break;
    
    case 3:
      //Write out header
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(38, 2);
      display.print("Envelope");
      display.drawLine(0,10,127,10, SSD1306_WHITE);

      //Show octave
      display.setTextSize(1);
      display.setCursor(3, 2);
      display.setTextColor(SSD1306_WHITE);
      display.println(octave);

      for (byte i = 0; i<4; i++){
        uint16_t waveColor = 0;
        if (i == menuCount){
          display.fillRect((2*(i+1))+(30*i)-1,48,30,15,SSD1306_WHITE);
          waveColor = SSD1306_BLACK;
        }
        else{
          display.drawRect((2*(i+1))+(30*i)-1,48,30,15,SSD1306_WHITE);
          waveColor = SSD1306_WHITE;
        }
        display.setCursor((2*(i+1))+(30*i)+12,52);
        display.setTextColor(waveColor);
        display.print(adsrNames[i]);

        int8_t circleLoc = 0;
        switch (i){
          case 0://Attack - 0-3000 in steps of 150
            circleLoc = 48.0-(adsr[i]/3000.0)*33.0;
            break;
          case 1://Decay - 0-3000 in steps of 150
            circleLoc = 48.0-(adsr[i]/3000.0)*33.0;
            break;
          case 2://Sustain - 0-1.0 in steps of 0.05
            circleLoc = 48.0-adsr[i]*33.0;
            break;
          case 3://Release - 0-3000 in steps of 150
            circleLoc = 48.0-(adsr[i]/3000.0)*33.0;
            break;
        }
        display.drawLine((2*(i+1))+(30*i)+14, 48, (2*(i+1))+(30*i)+14, circleLoc, SSD1306_WHITE);
        display.fillCircle((2*(i+1))+(30*i)+14, circleLoc, 3, SSD1306_WHITE);
      }
      break;

    case 4:
      //Write out header
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(38, 2);
      display.print("LP Filter");
      display.drawLine(0,10,127,10, SSD1306_WHITE);

      //Show octave
      display.setTextSize(1);
      display.setCursor(3, 2);
      display.setTextColor(SSD1306_WHITE);
      display.println(octave);

      int hOffset = 67*(filterFreq/3000.0)+40;

      display.fillRect(0, 32, hOffset, 31, SSD1306_WHITE);
      display.drawFastVLine(hOffset, 32, 31, SSD1306_WHITE);
      display.drawFastVLine(hOffset+1, 33, 30, SSD1306_WHITE);
      display.drawFastVLine(hOffset+2, 33, 30, SSD1306_WHITE);
      display.drawFastVLine(hOffset+3, 34, 29, SSD1306_WHITE);
      display.drawFastVLine(hOffset+4, 35, 28, SSD1306_WHITE);
      display.drawFastVLine(hOffset+5, 37, 26, SSD1306_WHITE);
      display.fillTriangle(hOffset+5, 37, hOffset+15, 62, hOffset+5,62, SSD1306_WHITE);

      display.setCursor(10, 45);
      display.setTextColor(SSD1306_BLACK);
      display.print(filterFreq);
      display.print("Hz");

      display.setCursor(hOffset-15, 20);
      display.setTextColor(SSD1306_WHITE);
      display.print("Q:");
      display.println(filterQ);
      break;
  }
  display.display();
}
