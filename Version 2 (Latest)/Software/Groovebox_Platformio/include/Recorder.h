#ifndef RECORDER_H
#define RECORDER_H

#include <Arduino.h>
#include "SDHeader.h"
#include <Si4703_Breakout.h>

extern Si4703_Breakout radio;

/*
 *Recorder Stuff 
 */
extern EXTMEM char recNameBuff[15];
extern EXTMEM char previewNameBuff[15];
extern EXTMEM char entryNameBuff[15];\
extern float inputGain;
extern int numRecFiles;
extern byte recordStatus;
extern File recFile;

class Recorder {
  private:
    int radioChannel;
    int8_t recSource;
    bool radioOn;
    bool monitoringOn;
    byte microphoneGain ;
    byte lineInGain;
    bool gainInitialized;
    byte circleLoc;
    bool selectButtonPrev;
    unsigned long currentStartTime;
    bool previewStatus;
    bool fileErasePrompt;
    float inputGain;
    int numRecFiles;

    void startRecording();
    void continueRecording();
    void stopRecording();
    void startPlayingPreview();
    void continuePlayingPreview();
    void stopPlayingPreview();
    void init();
  public:
    Recorder()
      :radioChannel{987},
      microphoneGain{36},
      lineInGain{5}
    {
      init();
    }
    void menuCheck();
    void staticMenu();
    void showRMS();
    void recordAndPlayback();

};

#endif