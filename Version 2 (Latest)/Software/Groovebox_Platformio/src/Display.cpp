#include <Display.h>

/*Pin configurations and settings for
* SSD1351 Color OLED Display
*/
const int8_t OLED_RESET = -1; 
// Screen dimensions
const byte SCREEN_WIDTH = 128;
const byte SCREEN_HEIGHT = 128;
//Extra pins for SPI
const byte DC_PIN = 40;
const byte CS_PIN = 38;
const byte RST_PIN = 41;
Adafruit_SSD1351 oled = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI1, CS_PIN, DC_PIN, RST_PIN);

// Color definitions
const uint16_t BLACK = 0x0000;
const uint16_t BLUE = 0x001F;
const uint16_t RED = 0xFA20;
const uint16_t GREEN = 0x47E0;
const uint16_t CYAN = 0x07FF;
const uint16_t MAGENTA = 0xF81F;
const uint16_t PURPLE = 0x6011;
const uint16_t YELLOW = 0xFD60;
const uint16_t WHITE = 0xFFFF;
const uint16_t DARKGREY = 0x39C7;
const uint16_t LIGHTGREY = 0x6B6D;
const uint16_t PURERED = 0xF800;
const uint16_t MAROON = 0xBAEB;
const uint16_t DARKGREEN = 0x03A0;

/*Pin configurations and settings for
 * Neopixels
 */
const int neopixel_pin = 17;
DMAMEM byte drawingMemory[numled*3];         //  3 bytes per LED
DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED
WS2812Serial leds(numled, displayMemory, drawingMemory, neopixel_pin, WS2812_GRB);

/*Pin configurations and settings for
 * LEDs
 */
const byte enc1LED = 32;
const byte enc2LED = 31;
const byte enc3LED = 30;
const byte enc4LED = 29;

/*
 *Update Controllers
 */
bool draw = 1;
bool directoryDisplayed = 0;

/*
 * Navigation Globals
 */
byte screen = 0;
byte screenPrev = 0;
byte function = 0;

void Display::init(){
    oled.begin();
    leds.begin();
}

void Display::startup(){
    // Initialize the Display
    oled.fillScreen(BLACK);
    oled.setTextSize(3);
    oled.setTextColor(MAGENTA); 
    oled.setCursor(20, 54);     
    oled.println(F("SYNTH"));
    oled.drawRoundRect(15,50,97,30,5,MAGENTA);

    pinMode(enc1LED, OUTPUT);
    pinMode(enc2LED, OUTPUT);
    pinMode(enc3LED, OUTPUT);
    pinMode(enc4LED, OUTPUT);
    
    leds.setBrightness(5);
    
    //Turn off all neopixels to start
    for (int i=0; i < numled; i++) {
        leds.setPixel(i, BLACK);
        leds.setBrightness(5);
        leds.show();
    }

    //Display a fun animation
    delay(1000);
    oled.drawRoundRect(15,50,97,30,5,BLACK);
    
    oled.drawRoundRect(0,0,127,127,5,MAGENTA);
    oled.setTextColor(RED); 
    oled.setCursor(20, 54);     
    oled.println(F("SYNTH"));
    delay(100);
    
    oled.drawRoundRect(15,15,98,98,5,MAGENTA);
    oled.setTextColor(GREEN); 
    oled.setCursor(20, 54);     
    oled.println(F("SYNTH"));
    delay(100);
    
    oled.drawRoundRect(30,30,68,68,5,MAGENTA);
    oled.setTextColor(BLUE); 
    oled.setCursor(20, 54);     
    oled.println(F("SYNTH"));
    delay(100);
    
    oled.drawRoundRect(45,45,38,38,5,MAGENTA);
    oled.setTextColor(YELLOW); 
    oled.setCursor(20, 54);     
    oled.println(F("SYNTH"));
    delay(100);
    
    oled.drawRoundRect(60,60,8,8,5,MAGENTA);
    oled.setTextColor(WHITE); 
    oled.setCursor(20, 54);     
    oled.println(F("SYNTH"));
    delay(100);
    
    oled.fillScreen(BLACK);
}