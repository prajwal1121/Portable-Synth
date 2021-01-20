#define USE_SdFat_ 

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <WS2812Serial.h>
#include <Si4703_Breakout.h>

#ifdef USE_SdFat_
  #include <SdFat.h>
  SdFat SD; 
#else
  #include <SD.h>
#endif

/*Pin configurations and settings for
 * SSD1351 Color OLED Display
 */
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>

#define OLED_RESET -1 
// Screen dimensions
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128 

//Extra pins for SPI
#define DC_PIN   40
#define CS_PIN   38
#define RST_PIN  41

Adafruit_SSD1351 oled = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI1, CS_PIN, DC_PIN, RST_PIN);

// Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xFA20
#define PURERED         0xF800
#define DARKGREEN       0x03A0
#define GREEN           0x47E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define PURPLE          0x6011
#define YELLOW          0xFD60  
#define WHITE           0xFFFF
#define DARKGREY        0x39C7
#define LIGHTGREY       0x6B6D
#define MAROON          0xBAEB
/*Pin configurations and settings for
 * Neopixels
 */
const int numled = 10;
const int pin = 17;

byte drawingMemory[numled*3];         //  3 bytes per LED
DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED

WS2812Serial leds(numled, displayMemory, drawingMemory, pin, WS2812_GRB);

/*Pin configurations and settings for
 * LEDs
 */
#define enc1LED 32
#define enc2LED 31
#define enc3LED 30
#define enc4LED 29

/*Pin configurations SD and Flash
 * Memory
 */
#define FLASHCHIP_CS_PIN 6
//#define SDCARD_CS_PIN  BUILTIN_SDCARD  
#define SDCARD_MOSI_PIN  11  
#define SDCARD_SCK_PIN   13

/*
 *Radio Module Config 
 */
#define radioReset  14
#define radioSdio  18
#define radioSclk  19
Si4703_Breakout radio(radioReset, radioSdio, radioSclk);
int radioChannel = 987;
char rdsBuffer[10];

float inputGain = 0.0;

EXTMEM char recNameBuff[15];
EXTMEM char previewNameBuff[15];
EXTMEM char entryNameBuff[15];
int numRecFiles = 0;
File currentDirectory;
/*
 * ASDT Output
 */
// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=275.0003128051758,267.85748386383057
AudioPlaySdRaw           playSdRec;     //xy=428.0000877380371,402.0001583099365
AudioMixer4              input_mixer;         //xy=436.0001220703125,280.0000629425049
AudioMixer4              record_mixer;         //xy=440.0001525878906,348.0001525878906
AudioAnalyzePeak         peak_left;          //xy=442.0000534057617,166.00000667572021
AudioAnalyzePeak         peak_right;          //xy=445.00004959106445,202.00002670288086
AudioRecordQueue         record_queue;         //xy=604.0000228881836,348.00011920928955
AudioMixer4              output_mixer;         //xy=745.000171661377,296.0000457763672
AudioOutputI2S           i2s1;           //xy=895.0001792907715,296.0000114440918
AudioConnection          patchCord1(i2s2, 0, input_mixer, 0);
AudioConnection          patchCord2(i2s2, 0, peak_left, 0);
AudioConnection          patchCord3(i2s2, 0, record_mixer, 0);
AudioConnection          patchCord4(i2s2, 1, input_mixer, 1);
AudioConnection          patchCord5(i2s2, 1, peak_right, 0);
AudioConnection          patchCord6(i2s2, 1, record_mixer, 1);
AudioConnection          patchCord7(playSdRec, 0, output_mixer, 1);
AudioConnection          patchCord8(input_mixer, 0, output_mixer, 0);
AudioConnection          patchCord9(record_mixer, record_queue);
AudioConnection          patchCord10(output_mixer, 0, i2s1, 0);
AudioConnection          patchCord11(output_mixer, 0, i2s1, 1);
AudioControlSGTL5000     codec;     //xy=444.33361053466797,114.50019979476929
// GUItool: end automatically generated code

/*
 * Navigation Globals
 */
byte screen = 0;
byte screenPrev = 0;
byte function = 0;

/*
 * A thing for volume
 */
int vol = 0;

void setup()
{
  Wire.begin();
  leds.begin();
  oled.begin();
  
  // Initialize the Codec  
  codec.enable();
  codec.inputSelect(AUDIO_INPUT_LINEIN);
  codec.dacVolumeRamp();
  codec.lineOutLevel(13);
  codec.volume(0.0);
  AudioNoInterrupts();
  
  // Initialize the SD card
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  SD.begin(SdioConfig(FIFO_SDIO));
  SerialFlash.begin(FLASHCHIP_CS_PIN);
  
  // Initialize the Display
  oled.fillScreen(BLACK);
  oled.setTextSize(3);
  oled.setTextColor(MAGENTA); 
  oled.setCursor(20, 54);     
  oled.println(F("RECRD"));
  oled.drawRoundRect(15,50,97,30,5,MAGENTA);

  //Give Audio Library a lot of memory to work with
  AudioMemory(24);

  pinMode(enc1LED, OUTPUT);
  pinMode(enc2LED, OUTPUT);
  pinMode(enc3LED, OUTPUT);
  pinMode(enc4LED, OUTPUT);
  
  //Initialize LEDs
  leds.begin();
  leds.setBrightness(5);
  
  //Turn off all neopixels to start
  for (byte i=0; i < numled; i++) {
    leds.setPixel(i, BLACK);
    leds.setBrightness(5);
    leds.show();
  }

  //Radio setup
  radio.powerOn();
  radio.setVolume(0);
  radio.setChannel(radioChannel);

  input_mixer.gain(0,inputGain);
  input_mixer.gain(1,inputGain);
  record_mixer.gain(0,0.25);
  record_mixer.gain(1,0.25);
  
  if (!SD.exists("/Recs")){
    SD.mkdir("/Recs");
  }

  //See what's in our root Recordings directory
  currentDirectory = SD.open("/Recs");
  while(true) {
     File entry =  currentDirectory.openNextFile();
     if (!entry) {
       currentDirectory.rewindDirectory();
       break;
     }
     else{
       numRecFiles = numRecFiles+1;
     }
     delay(1);
     entry.close();
     delay(1);
   }
   sprintf(recNameBuff,"/Recs/R%d.RAW",numRecFiles);
   Serial.println(numRecFiles);
  AudioInterrupts();

  //Display a fun animation
  delay(1000);
  oled.drawRoundRect(15,50,97,30,5,BLACK);
  
  oled.drawRoundRect(0,0,127,127,5,MAGENTA);
  oled.setTextColor(RED); 
  oled.setCursor(20, 54);     
  oled.println(F("RECRD"));
  delay(100);
  
  oled.drawRoundRect(15,15,98,98,5,MAGENTA);
  oled.setTextColor(GREEN); 
  oled.setCursor(20, 54);     
  oled.println(F("RECRD"));
  delay(100);
  
  oled.drawRoundRect(30,30,68,68,5,MAGENTA);
  oled.setTextColor(BLUE); 
  oled.setCursor(20, 54);     
  oled.println(F("RECRD"));
  delay(100);
  
  oled.drawRoundRect(45,45,38,38,5,MAGENTA);
  oled.setTextColor(YELLOW); 
  oled.setCursor(20, 54);     
  oled.println(F("RECRD"));
  delay(100);
  
  oled.drawRoundRect(60,60,8,8,5,MAGENTA);
  oled.setTextColor(WHITE); 
  oled.setCursor(20, 54);     
  oled.println(F("RECRD"));
  delay(100);
  
  oled.fillScreen(BLACK);
}

//Timing Variables
unsigned long last_time_input = millis();
unsigned long last_time_display = millis();
unsigned long last_time_print = millis();

void loop(){
  //Read and set volume
  int n = analogRead(15);
  if (n != vol) {
    vol = n;
    codec.volume((float)n / 1023);
  }

  menuCheckRecorder();//See if menu needs updating
  //Update every 10ms
  if (millis()-last_time_display > 10){
    staticMenuRecorder(); //Refresh display
    last_time_display = millis();
  }
  //Update every 25ms
  if (millis()-last_time_input > 25){
    readInputs(); //Request fresh user input data
    showRMS();
    last_time_input = millis();
  }
  //Update as fast as possible
  updateEncoders();
  playKeyboard();
  recordAndPlayback();
}
