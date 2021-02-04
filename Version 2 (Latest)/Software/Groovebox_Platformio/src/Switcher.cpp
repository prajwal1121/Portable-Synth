#include "Switcher.h"
#include "ReadInputs.h"
#include "Display.h"
#include "AudioConfig.h"
#include "Synth.h"
extern Synth synth;
#include "Recorder.h"
#include "Mixer.h"
#include "Sequencer.h"

void Switcher::switchMode(){
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
    enc2Count = synth.getWaveAmplitude(0);
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
    playSdRec.stop();
    record_queue.end();
    recFile.close();
    recordStatus = 0;
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
    playSdRec.stop();
    record_queue.end();
    recFile.close();
    recordStatus = 0;
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
    playSdRec.stop();
    record_queue.end();
    recFile.close();
    recordStatus = 0;
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
    playSdRec.stop();
    record_queue.end();
    recFile.close();
    recordStatus = 0;
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

  if (audioRecordButton and !audioRecordButtonPrev){
    function = 4;
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
    draw = 1;
    directoryDisplayed = 0;
    playSdWav1.stop();
    playSdRec.stop();
    record_queue.end();
    recFile.close();
    recordStatus = 0;
    oled.fillScreen(BLACK);
    oled.setTextSize(3);      
    oled.setTextColor(MAGENTA);  
    oled.setCursor(20, 54);     
    oled.println(F("RECRD"));
    oled.drawRoundRect(15,50,97,30,5,MAGENTA);
    delay(800);
    oled.fillScreen(BLACK);
  }
  audioRecordButtonPrev = audioRecordButton;
}