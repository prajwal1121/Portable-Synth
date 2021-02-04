#ifndef SAMPLER_H
#define SAMPLER_H

#include <Arduino.h>
#include "SDHeader.h"

// Overall Navigation Variables for Sampler
extern const byte onScreenItems;
extern byte topItem;
extern byte topItemPrev;
extern bool padPrev[12];
extern byte chosenFile;

/*
 * Sampler Stuff
 */
#define numSampleFiles 12
extern const long maxSampleLength;
struct samples {
  char fileName[20];
};
extern EXTMEM samples samps[numSampleFiles];
extern EXTMEM char fileNameBuff[80];
extern EXTMEM char newfileNameBuff[80];
extern EXTMEM char previewfileNameBuff[80];
extern EXTMEM char rootSampleDir[25];
extern File currentDirectory;

class Sampler {
  private:
    const byte fileNameLength;
    const byte checkChar;
    bool notInRoot;
    bool assignSampleScreen;
    bool editSampleScreen;
    byte sampleToEdit;
    int numItems;
    float sampleadsr[12][5];

    void enterDirectory(char fileName[]);
    void updateSampleEnvelope(byte sampleNum);
    void init();
  public:
    Sampler()
      : fileNameLength{80},
    checkChar{118}//ASCII "v"
    {
      init();
    }
    void menuCheck();
    void staticMenu();
};

#endif