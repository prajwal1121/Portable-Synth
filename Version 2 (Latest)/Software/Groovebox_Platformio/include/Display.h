#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <WS2812Serial.h>

extern Adafruit_SSD1351 oled;

// Color definitions
extern const uint16_t BLACK;
extern const uint16_t BLUE;
extern const uint16_t RED;
extern const uint16_t GREEN;
extern const uint16_t CYAN;
extern const uint16_t MAGENTA;
extern const uint16_t PURPLE;
extern const uint16_t YELLOW;
extern const uint16_t WHITE;
extern const uint16_t DARKGREY;
extern const uint16_t LIGHTGREY;
extern const uint16_t PURERED;
extern const uint16_t MAROON;
extern const uint16_t DARKGREEN;

/*Pin configurations and settings for
 * LEDs
 */
extern const byte enc1LED;
extern const byte enc2LED;
extern const byte enc3LED;
extern const byte enc4LED;

/*
 * Navigation Globals
 */
extern byte screen;
extern byte screenPrev;
extern byte function;

/*Pin configurations and settings for
 * Neopixels
 */
#define numled 10
extern const int neopixel_pin;
extern DMAMEM byte drawingMemory[numled*3];  //  3 bytes per LED
extern DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED
extern WS2812Serial leds;

/*
 *Update Controllers
 */
extern bool draw;
extern bool directoryDisplayed;

class Display {
  private:
    void init();
  public:
    Display()
    {
      init();
    }
    void startup();
};
#endif