//Shared control variables
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

float enc4Count = 0;
int enc4Change = 0;

bool mainSelectPrev = 0;
bool rightPrev = 0;
bool leftPrev = 0;

uint16_t color1 = WHITE;
uint16_t color2 = WHITE;

//Switch between different device functions
bool synthButtonPrev = 0;
bool samplerButtonPrev = 0;
bool sequencerButtonPrev = 0;
void switcher(){
  //Switch to Synth Mode
  if (synthButton and !synthButtonPrev and !mainSelect){
    function = 0;
    //Turn off encoder LEDs
    digitalWrite(enc1LED,LOW);
    digitalWrite(enc2LED,LOW);
    digitalWrite(enc3LED,LOW);
    digitalWrite(enc4LED,LOW);

    enc1Count = 0;
    enc1Change = 0;
    enc2Count = waveAmplitude[0];
    enc2Change = 0;
    enc3Count = 0;
    enc3Change = 0;
    enc4Count = 0;
    enc4Change = 0;
    encoders[0] = 0;
    encoders[1] = 0;
    encoders[2] = 0;
    encoders[3] = 0;
    screen = 0;
    playSdWav1.stop();
    oled.fillScreen(BLACK);
    oled.setTextSize(3);      
    oled.setTextColor(MAGENTA); 
    oled.setCursor(20, 54);     
    oled.println(F("SYNTH"));
    oled.drawRoundRect(15,50,97,30,5,MAGENTA);
    delay(800);
    oled.fillScreen(BLACK);
  }
  //Switch to Mixer Mode
  else if (synthButton and !synthButtonPrev and mainSelect){
    function = 3;
    //Turn off encoder LEDs
    digitalWrite(enc1LED,LOW);
    digitalWrite(enc2LED,LOW);
    digitalWrite(enc3LED,LOW);
    digitalWrite(enc4LED,LOW);
    
    enc1Count = outputVolume[0];
    enc1Change = 0;
    enc2Count = outputVolume[1];
    enc2Change = 0;
    enc3Count = 0;
    enc3Change = 0;
    enc4Count = 0;
    enc4Change = 0;
    encoders[0] = 0;
    encoders[1] = 0;
    encoders[2] = 0;
    encoders[3] = 0;
    screen = 0;
    playSdWav1.stop();
    oled.fillScreen(BLACK);
    oled.setTextSize(3);      
    oled.setTextColor(WHITE); 
    oled.setCursor(20, 54);     
    oled.println(F("MIXER"));
    oled.drawRoundRect(15,50,97,30,5,WHITE);
    delay(800);
    oled.fillScreen(BLACK);
  }
  synthButtonPrev = synthButton;

  //Switch to Sampler Mode
  if (samplerButton and !samplerButtonPrev){
    function = 1;
    //Turn off encoder LEDs
    digitalWrite(enc1LED,LOW);
    digitalWrite(enc2LED,LOW);
    digitalWrite(enc3LED,LOW);
    digitalWrite(enc4LED,LOW);

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
    screen = 0;
    playSdWav1.stop();
    oled.fillScreen(BLACK);
    oled.setTextSize(3);      
    oled.setTextColor(MAGENTA); 
    oled.setCursor(20, 54);     
    oled.println(F("SAMPL"));
    oled.drawRoundRect(15,50,97,30,5,MAGENTA);
    delay(800);
    oled.fillScreen(BLACK);
    directoryDisplayed = 0;
  }
  samplerButtonPrev = samplerButton;

  //Switch to Sequencer Mode
  if (sequencerButton and !sequencerButtonPrev){
    function = 2;
    //Turn off encoder LEDs
    digitalWrite(enc1LED,LOW);
    digitalWrite(enc2LED,LOW);
    digitalWrite(enc3LED,LOW);
    digitalWrite(enc4LED,LOW);
    
    enc1Count = 0;
    enc1Change = 0;
    enc2Count = bpm;
    enc2Change = 0;
    enc3Count = 0;
    enc3Change = 0;
    enc4Count = 0;
    enc4Change = 0;
    encoders[0] = 0;
    encoders[1] = 0;
    encoders[2] = 0;
    encoders[3] = 0;
    screen = 0;
    playSdWav1.stop();
    oled.fillScreen(BLACK);
    oled.setTextSize(3);      
    oled.setTextColor(MAGENTA); 
    oled.setCursor(20, 54);     
    oled.println(F("SEQNC"));
    oled.drawRoundRect(15,50,97,30,5,MAGENTA);
    delay(800);
    oled.fillScreen(BLACK);
  }
  sequencerButtonPrev = sequencerButton;
}
