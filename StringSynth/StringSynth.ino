#include <Audio.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WS2812Serial.h>
#define OLED_RESET -1 

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

// GUItool: begin automatically generated code
AudioSynthKarplusStrong  string15; //xy=411.99995040893555,992.1904554367065
AudioSynthKarplusStrong  string13; //xy=412.9999828338623,881.1904830932617
AudioSynthKarplusStrong  string14; //xy=416.9999837875366,941.1904850006104
AudioSynthKarplusStrong  string23; //xy=415.99995040893555,1509.8571424484253
AudioSynthKarplusStrong  string21; //xy=416.9999828338623,1398.8571701049805
AudioSynthKarplusStrong  string11; //xy=420.99995040893555,710.8571424484253
AudioSynthKarplusStrong  string9; //xy=421.9999828338623,599.8571701049805
AudioSynthKarplusStrong  string22; //xy=420.9999837875366,1458.857172012329
AudioSynthKarplusStrong  string10; //xy=425.9999837875366,659.8571720123291
AudioSynthKarplusStrong  string19; //xy=423.99995040893555,1256.8571424484253
AudioSynthKarplusStrong  string17; //xy=424.9999828338623,1145.8571701049805
AudioSynthKarplusStrong  string2;        //xy=430.0000228881836,176.14286422729492
AudioSynthKarplusStrong  string16; //xy=427.99992752075195,1058.0475769042969
AudioSynthKarplusStrong  string18; //xy=428.9999837875366,1205.857172012329
AudioSynthKarplusStrong  string3;        //xy=435.0000228881836,228.1428680419922
AudioSynthKarplusStrong  string7;        //xy=435.0000228881836,447.14287853240967
AudioSynthKarplusStrong  string5;        //xy=436.00005531311035,336.14290618896484
AudioSynthKarplusStrong  string1;        //xy=437.00004959106445,114.14286231994629
AudioSynthKarplusStrong  string24; //xy=431.99992752075195,1575.7142639160156
AudioSynthKarplusStrong  string4;        //xy=438.0000228881836,279.1428699493408
AudioSynthKarplusStrong  string12; //xy=436.99992752075195,776.7142639160156
AudioSynthKarplusStrong  string6;        //xy=440.00005626678467,396.1429080963135
AudioSynthKarplusStrong  string20; //xy=439.99992752075195,1322.7142639160156
AudioSynthKarplusStrong  string8;        //xy=451,513
AudioEffectEnvelope      envelope14; //xy=561.999927520752,944.0475769042969
AudioEffectEnvelope      envelope15; //xy=565.999927520752,996.0475769042969
AudioEffectEnvelope      envelope22; //xy=565.999927520752,1461.7142639160156
AudioEffectEnvelope      envelope10; //xy=570.999927520752,662.7142639160156
AudioEffectEnvelope      envelope23; //xy=569.999927520752,1513.7142639160156
AudioEffectEnvelope      envelope11; //xy=574.999927520752,714.7142639160156
AudioEffectEnvelope      envelope18; //xy=573.999927520752,1208.7142639160156
AudioEffectEnvelope      envelope16; //xy=575.999942779541,1059.047592163086
AudioEffectEnvelope      envelope13; //xy=577.9999504089355,880.0475912094116
AudioEffectEnvelope      envelope19; //xy=577.999927520752,1260.7142639160156
AudioEffectEnvelope      envelope24; //xy=579.999942779541,1576.7142791748047
AudioEffectEnvelope      envelope6; //xy=585,399
AudioEffectEnvelope      envelope21; //xy=581.9999504089355,1397.7142782211304
AudioEffectEnvelope      envelope12; //xy=584.999942779541,777.7142791748047
AudioEffectEnvelope      envelope9; //xy=586.9999504089355,598.7142782211304
AudioEffectEnvelope      envelope7; //xy=589,451
AudioEffectEnvelope      envelope20; //xy=587.999942779541,1323.7142791748047
AudioEffectEnvelope      envelope2; //xy=593,172
AudioEffectEnvelope      envelope4; //xy=593,280
AudioEffectEnvelope      envelope17; //xy=589.9999504089355,1144.7142782211304
AudioEffectEnvelope      envelope1;      //xy=595.0000228881836,110.99999618530273
AudioEffectEnvelope      envelope3; //xy=596,227
AudioEffectEnvelope      envelope8;      //xy=599.0000152587891,514.0000152587891
AudioEffectEnvelope      envelope5; //xy=601.0000228881836,335.00001430511475
AudioMixer4              mixer4; //xy=886,905.3333129882812
AudioMixer4              mixer6; //xy=890,1423
AudioMixer4              mixer3; //xy=895,624
AudioMixer4              mixer5; //xy=898,1170
AudioMixer4              mixer1;         //xy=909.0000190734863,201.00000762939453
AudioMixer4              mixer2;         //xy=909.000072479248,360.2857360839844
AudioMixer4              mixer7;         //xy=1224.9999923706055,518.2857208251953
AudioMixer4              mixer8;         //xy=1225.666660308838,681.6666946411133
AudioMixer4              mixer9;         //xy=1432.6666870117188,580
AudioAnalyzePeak         peak1;          //xy=1593.4288749694824,439.14287853240967
AudioOutputI2S           i2s1;           //xy=1639.0006523132324,561.2859630584717
AudioConnection          patchCord1(string15, envelope15);
AudioConnection          patchCord2(string13, envelope13);
AudioConnection          patchCord3(string14, envelope14);
AudioConnection          patchCord4(string23, envelope23);
AudioConnection          patchCord5(string21, envelope21);
AudioConnection          patchCord6(string11, envelope11);
AudioConnection          patchCord7(string9, envelope9);
AudioConnection          patchCord8(string22, envelope22);
AudioConnection          patchCord9(string10, envelope10);
AudioConnection          patchCord10(string19, envelope19);
AudioConnection          patchCord11(string17, envelope17);
AudioConnection          patchCord12(string2, envelope2);
AudioConnection          patchCord13(string16, envelope16);
AudioConnection          patchCord14(string18, envelope18);
AudioConnection          patchCord15(string3, envelope3);
AudioConnection          patchCord16(string7, envelope7);
AudioConnection          patchCord17(string5, envelope5);
AudioConnection          patchCord18(string1, envelope1);
AudioConnection          patchCord19(string24, envelope24);
AudioConnection          patchCord20(string4, envelope4);
AudioConnection          patchCord21(string12, envelope12);
AudioConnection          patchCord22(string6, envelope6);
AudioConnection          patchCord23(string20, envelope20);
AudioConnection          patchCord24(string8, envelope8);
AudioConnection          patchCord25(envelope14, 0, mixer4, 1);
AudioConnection          patchCord26(envelope15, 0, mixer4, 2);
AudioConnection          patchCord27(envelope22, 0, mixer6, 1);
AudioConnection          patchCord28(envelope10, 0, mixer3, 1);
AudioConnection          patchCord29(envelope23, 0, mixer6, 2);
AudioConnection          patchCord30(envelope11, 0, mixer3, 2);
AudioConnection          patchCord31(envelope18, 0, mixer5, 1);
AudioConnection          patchCord32(envelope16, 0, mixer4, 3);
AudioConnection          patchCord33(envelope13, 0, mixer4, 0);
AudioConnection          patchCord34(envelope19, 0, mixer5, 2);
AudioConnection          patchCord35(envelope24, 0, mixer6, 3);
AudioConnection          patchCord36(envelope6, 0, mixer2, 1);
AudioConnection          patchCord37(envelope21, 0, mixer6, 0);
AudioConnection          patchCord38(envelope12, 0, mixer3, 3);
AudioConnection          patchCord39(envelope9, 0, mixer3, 0);
AudioConnection          patchCord40(envelope7, 0, mixer2, 2);
AudioConnection          patchCord41(envelope20, 0, mixer5, 3);
AudioConnection          patchCord42(envelope2, 0, mixer1, 1);
AudioConnection          patchCord43(envelope4, 0, mixer1, 3);
AudioConnection          patchCord44(envelope17, 0, mixer5, 0);
AudioConnection          patchCord45(envelope1, 0, mixer1, 0);
AudioConnection          patchCord46(envelope3, 0, mixer1, 2);
AudioConnection          patchCord47(envelope8, 0, mixer2, 3);
AudioConnection          patchCord48(envelope5, 0, mixer2, 0);
AudioConnection          patchCord49(mixer4, 0, mixer7, 3);
AudioConnection          patchCord50(mixer6, 0, mixer8, 1);
AudioConnection          patchCord51(mixer3, 0, mixer7, 2);
AudioConnection          patchCord52(mixer5, 0, mixer8, 0);
AudioConnection          patchCord53(mixer1, 0, mixer7, 0);
AudioConnection          patchCord54(mixer2, 0, mixer7, 1);
AudioConnection          patchCord55(mixer7, 0, mixer9, 0);
AudioConnection          patchCord56(mixer8, 0, mixer9, 1);
AudioConnection          patchCord57(mixer9, 0, i2s1, 0);
AudioConnection          patchCord58(mixer9, 0, i2s1, 1);
AudioConnection          patchCord59(mixer9, peak1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1518.5000076293945,335.00012016296387
// GUItool: end automatically generated code

AudioEffectEnvelope *envs[24] = {&envelope1, &envelope2, &envelope3, &envelope4, &envelope5, &envelope6, &envelope7, &envelope8, &envelope9, &envelope10, &envelope11, &envelope12, &envelope13, &envelope14, &envelope15, &envelope16, &envelope17, &envelope18, &envelope19, &envelope20, &envelope21, &envelope22, &envelope23, &envelope24};
AudioSynthKarplusStrong *strs[24] = {&string1, &string2, &string3, &string4, &string5, &string6, &string7, &string8, &string9, &string10, &string11, &string12, &string13, &string14, &string15, &string16, &string17, &string18, &string19, &string20, &string21, &string22, &string23, &string24};
const float keys[24] = {261.63,277.18,293.66,311.13,329.63,349.23,369.99,392.00,415.30,440.00,466.16,493.88,523.25,554.37,587.33,622.25,659.25,698.46,739.99,783.99,830.61,880.00,932.33,987.77};
bool keystate[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

const int numButtons = 24;
int current_byte = 0;
int current_button = 0;
byte buttonStates[5] = {0,0,0,0,0};

const int numEncoders = 3;
int encoders[numEncoders] = {0,0,0};
bool freshData = false;

const int numled = 10;
const int pin = 29;
byte drawingMemory[numled*3];         //  3 bytes per LED
DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED
WS2812Serial leds(numled, displayMemory, drawingMemory, pin, WS2812_GRB);
#define PINK   0xFF1088

int volume = 50;

bool click1 = false;
bool click2 = false;
bool selected = false;
bool selectedPrev = false;
bool fineAdj = false;
bool adjPrev = false; 
int8_t menuCount = 0;
int menuChange = 0;
int valChange = 0;

float adsr[4] = {90.2,31.4,0.6,440.5};

void setup() {
  Wire.begin();             
  
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(2);
  display.clearDisplay();
  display.setTextSize(3);      
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(20, 25);     
  display.println(F("SYNTH"));
  display.drawRect(15, 20, 96, 30, SSD1306_WHITE);
  display.display();
  
  AudioMemory(24);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(1.0);
  

  for (int i=0; i<24; i++) {
    envs[i]->attack(adsr[0]);
    envs[i]->hold(0);
    envs[i]->decay(adsr[1]);
    envs[i]->sustain(adsr[2]);
    envs[i]->release(adsr[3]);
  }
  AudioInterrupts();
  
  display.clearDisplay();
  
  AudioProcessorUsageMaxReset();
  AudioMemoryUsageMaxReset();
  
  leds.begin();
  leds.setBrightness(10);
}

unsigned long last_time = millis();

void loop() {

  int n = analogRead(15);
  if (n != volume) {
    volume = n;
    sgtl5000_1.volume((float)n / 1023);
  }
    
  if (millis()-last_time > 25){
    readButtons();
    menuCheck();
    staticMenu();
    setEnvelope();
    last_time = millis();
  }
  
  for (int i = 0; i < 24; i++){
    current_byte = i/8;
    current_button = i-8*current_byte;
    if (bitRead(buttonStates[current_byte], current_button)){
      if (!keystate[i]){
        AudioNoInterrupts();
        strs[i]->noteOn(keys[i],0.4);
        envs[i]->noteOn();
        AudioInterrupts();
        keystate[i] = 1;
      }
    }
    else{
      if (keystate[i]){
        AudioNoInterrupts();
        envs[i]->noteOff();
        AudioInterrupts();
        keystate[i] = 0;
      }
    }
  }

  if (freshData){
    for (int e = 0; e < numEncoders; e++){
      byte mask = B00000011;
      mask = mask << e*2;
      byte enc_val = buttonStates[5] & mask;
      enc_val = enc_val >> e*2;
      if (enc_val == 2){
        encoders[e]--;
      }
      else if (enc_val == 1){
        encoders[e]++;
      }
      Serial.print(encoders[e]);
      Serial.print(" ");
    }
    Serial.println();
    freshData = false;
  }
  
  if (peak1.available()){
    float pk = peak1.read();
    pk=map(pk,0.01,0.1,0,10);
    
    for (int i=9; i > 9-pk; i--) {
      leds.setPixel(i, PINK);
    }
    for (int i=0; i < 9-pk; i++) {
      leds.setPixel(i, BLACK);
    }
    leds.show();
  }

  click1 = bitRead(buttonStates[4],5);
  click2 = bitRead(buttonStates[4],6);
}

void readButtons(){   
    Wire.requestFrom(8, 6);
    
    while(Wire.available()) { 
      buttonStates[0] = Wire.read();
      buttonStates[1] = Wire.read();
      buttonStates[2] = Wire.read();
      buttonStates[3] = Wire.read();
      buttonStates[4] = Wire.read();
      buttonStates[5] = Wire.read();
//      Serial.print(buttonStates[0],BIN);
//      Serial.print("  ");
//      Serial.print(buttonStates[1],BIN);
//      Serial.print("  ");
//      Serial.print(buttonStates[2],BIN);
//      Serial.print("  ");
//      Serial.print(buttonStates[3],BIN); 
//      Serial.print("  ");
//      Serial.print(buttonStates[4],BIN);         
//      Serial.print("  ");
//      Serial.print(buttonStates[5],BIN); 
    }
//    Serial.println();
  freshData = true;   
}

void staticMenu() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10, 0);
  display.println("ENVELOPE");
  //---------------------------------
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("Attack:");
  display.setCursor(60, 20);
  if (selected and menuCount == 0){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.println(adsr[0]);
    display.setTextColor(SSD1306_WHITE);
  }
  else{
    display.setTextColor(SSD1306_WHITE);
    display.println(adsr[0]);
  }

  display.setCursor(10, 30);
  display.println("Decay:");
  display.setCursor(60, 30);
  if (selected and menuCount == 1){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.println(adsr[1]);
    display.setTextColor(SSD1306_WHITE);
  }
  else{
    display.setTextColor(SSD1306_WHITE);
    display.println(adsr[1]);
  }

  display.setCursor(10, 40);
  display.println("Sustain:");
  display.setCursor(60, 40);
  if (selected and menuCount == 2){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.println(adsr[2]);
    display.setTextColor(SSD1306_WHITE);
  }
  else{
    display.setTextColor(SSD1306_WHITE);
    display.println(adsr[2]);
  }

  display.setCursor(10, 50);
  display.println("Release:");
  display.setCursor(60, 50);
  if (selected and menuCount == 3){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.println(adsr[3]);
    display.setTextColor(SSD1306_WHITE);
  }
  else{
    display.setTextColor(SSD1306_WHITE);
    display.println(adsr[3]);
  }

  display.setCursor(2, ((menuCount+1) * 10) + 10);
  display.println(">");

  display.display();
}

void menuCheck() {
  menuChange = encoders[0]-menuChange;
  valChange = encoders[1]-valChange;
  
  menuCount = menuCount + menuChange;
  if (menuCount > 3){
    menuCount = 0;
  }
  if (menuCount < 0){
    menuCount = 3;
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

  if (click2 and !adjPrev){
    if (fineAdj){
      fineAdj = false;
    }
    else{
      fineAdj = true;
    }
  }
  adjPrev = click2;

  if (selected){
    if (fineAdj){
      adsr[menuCount] = adsr[menuCount]+valChange/10.0;
    }
    else{
      adsr[menuCount] = adsr[menuCount]+valChange;
    }
  }
  valChange = encoders[1];

  if (adsr[menuCount] < 0){
    adsr[menuCount] = 0;
  }
}
void setEnvelope(){
    for (int i=0; i<24; i++) {
    envs[i]->attack(adsr[0]);
    envs[i]->hold(0);
    envs[i]->decay(adsr[1]);
    envs[i]->sustain(adsr[2]);
    envs[i]->release(adsr[3]);
  }
}
