#include <WS2812Serial.h>

const int numled = 10;
const int pin = 17;

byte drawingMemory[numled*3];         //  3 bytes per LED
DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED

WS2812Serial leds(numled, displayMemory, drawingMemory, pin, WS2812_GRB);

#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF

void setup() {
  leds.begin();
  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
}

void loop() {
  // change all the LEDs in 1.5 seconds
  int microsec = 150000/ leds.numPixels();
  
  
  
  digitalWrite(29,HIGH);
  digitalWrite(30,HIGH);
  digitalWrite(31,HIGH);
  digitalWrite(32,HIGH);
  
  int b = map(analogRead(24), 100, 900, 0,255);
  colorWipe(RED, microsec, b);
  b = map(analogRead(24), 100, 900, 0,255);
  colorWipe(GREEN, microsec, b);
  b = map(analogRead(24), 100, 900, 0,255);
  colorWipe(BLUE, microsec, b);
  b = map(analogRead(24), 100, 900, 0,255);
  colorWipe(YELLOW, microsec, b);
  b = map(analogRead(24), 100, 900, 0,255);
  colorWipe(PINK, microsec, b);
  b = map(analogRead(24), 100, 900, 0,255);
  colorWipe(ORANGE, microsec, b);
  b = map(analogRead(24), 100, 900, 0,255);
  colorWipe(WHITE, microsec, b);

  
}

void colorWipe(int color, int wait, int b) {
  for (int i=0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
    leds.setBrightness(b);
    leds.show();
    delayMicroseconds(wait);
  }
}
