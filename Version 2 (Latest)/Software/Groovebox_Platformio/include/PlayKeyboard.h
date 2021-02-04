#ifndef PLAY_KEYBOARD_H
#define PLAY_KEYBOARD_H

#include <Arduino.h>

extern byte keystate[24];
extern bool padState[12];
extern bool controlstate[4];

class PlayKeyboard {
  private:
    //Nothing Here
  public:
    void play();
};

#endif