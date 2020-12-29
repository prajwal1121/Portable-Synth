void menuCheckMixer() {
  enc1Change = encoders[0]-enc1Change;
  enc1Count = enc1Count + 0.1*enc1Change;
  if (enc1Count < 0) enc1Count = 0;
  if (enc1Count > 1.0) enc1Count = 1.0;
  outputVolume[0]= enc1Count;
  enc1Change = encoders[0];

  enc2Change = encoders[1]-enc2Change;
  enc2Count = enc2Count + 0.1*enc2Change;;
  if (enc2Count < 0) enc2Count = 0;
  if (enc2Count > 1.0) enc2Count = 1.0;
  outputVolume[1]= enc2Count;
  enc2Change = encoders[1];

  output_mixer.gain(0,outputVolume[0]);
  output_mixer.gain(1,outputVolume[1]);
}
void staticMenuMixer() {
  digitalWrite(enc1LED,HIGH);
  digitalWrite(enc2LED,HIGH);
  digitalWrite(enc3LED,LOW);
  digitalWrite(enc4LED,LOW);
   
  oled.setTextSize(1);
  oled.setTextColor(WHITE,BLACK);
  oled.setCursor(25, 2);
  oled.print(F("Adjust Volume"));
  oled.drawFastHLine(0,10,128, WHITE);
    
  for (byte i = 0; i<2; i++){
    int8_t circleLoc = 0;
    byte xloc = 42+42*i;
    byte yloc = 95.0-outputVolume[i]*76;
    switch (i){
      case 0://Sampler
        color1 = RED;
        oled.setTextColor(RED,BLACK);
        oled.setCursor(0,yloc+3);
        oled.print(outputVolume[0]);
        oled.fillRect(0,yloc-7,24,10,BLACK);
        oled.fillRect(0,yloc+11,24,10,BLACK);
        break;
      case 1://Synth
        color1 = GREEN;
        oled.setTextColor(GREEN,BLACK);
        oled.setCursor(104,yloc+3);
        oled.print(outputVolume[1]);
        oled.fillRect(104,yloc-7,24,10,BLACK);
        oled.fillRect(104,yloc+11,24,10,BLACK);
        break;
    }
    oled.fillRect(xloc-4,yloc,9,14,color1);
    oled.fillRect(xloc-4,yloc,9,14,color1);
    
    oled.fillRect(xloc-4,yloc-8,4,8,BLACK);
    oled.fillRect(xloc-4,yloc+14,4,8,BLACK);
    oled.fillRect(xloc+1,yloc-8,4,8,BLACK);
    oled.fillRect(xloc+1,yloc+14,4,8,BLACK);
    
    oled.drawLine(xloc,yloc-1,xloc,19,LIGHTGREY);
    oled.drawLine(xloc,yloc+14,xloc,108,LIGHTGREY);
  }
  oled.setTextColor(WHITE,BLACK);
  oled.setCursor(0,120);
  oled.print(F("SAMPLER"));
  oled.setCursor(98,120);
  oled.print(F("SYNTH"));
  oled.drawFastVLine(42,108,10,WHITE);
  oled.drawFastVLine(84,108,10,WHITE);
  oled.drawFastHLine(0,118,42,WHITE);
  oled.drawFastHLine(84,118,44,WHITE);

}
