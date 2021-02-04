#ifndef MIXER_H
#define MIXER_H

#include <Arduino.h>

/*
 * Output Stuff
 */
extern float outputVolume[2];

class Mixer {
  private:
    void init();
  public:
    Mixer()
    {
      init();
    }
    void menuCheck();
    void staticMenu();
};

#endif