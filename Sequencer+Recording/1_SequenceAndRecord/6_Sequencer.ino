bool looped[numSequences] = {0,0,0,0};
byte holdvalue[numSequences] = {0,0,0,0};
bool holdflag[numSequences] = {0,0,0,0};
bool trigSignal[numSequences] = {0,0,0,0};
bool triggered[numSequences] = {0,0,0,0};

void eraseSequenceNum(byte sequence){
  for (byte n = 0; n < sequenceLength[sequence]; n++){
    seqs[sequence].notes[n] = 0;
    seqs[sequence].gains[n] = 0;
  }
  sequenceLength[sequence] = 0;
  sequenceCounter[sequence] = 0;
  seqs[sequence].instrument = chan;
}

void sequenceNote(byte note, byte velocity){
  if (recordSequenceSelect){
    if (sequenceCounter[currentSequence] == 0){
      seqs[currentSequence].instrument = chan;
    }
    if (sequenceCounter[currentSequence] < numSequenceNotes){
      seqs[currentSequence].notes[sequenceCounter[currentSequence]] = note;
      seqs[currentSequence].gains[sequenceCounter[currentSequence]] = velocity;
      sequenceCounter[currentSequence]++;
      sequenceLength[currentSequence]++;
    }
  }
}

void checkAndPlaySequence(){
  for (byte numseqs = 0; numseqs < numSequences; numseqs++){
    sequencePlayingCheck = 0;
    byte trigSignalCheck = 0;
    for (byte k = 0; k < numSequences; k++){
      if(!(k==numseqs)){
        sequencePlayingCheck += sequencePlaying[k];
        trigSignalCheck += trigSignal[k];
      }
    }
    
    if (playSequenceNum[numseqs]){
      if (sequencePlayingCheck){
        if (!triggered[numseqs] and trigSignalCheck){
          triggered[numseqs] = 1;
        }
        if (triggered[numseqs]){
          if (!sequencePlaying[numseqs]){
            sequenceCounter[numseqs]=0;
            sequencePlaying[numseqs] = 1;
          }
          long seqPeriod = (4.0/tSigs[seqs[numseqs].timeSignature])*ms_per_beat;
          if (millis()-seqTimers[numseqs] > seqPeriod){
            playSequence(numseqs);
            seqTimers[numseqs] = millis();
          }
          else{
            trigSignal[numseqs] = 0;
          }
        }  
      }
      else{
        if (!sequencePlaying[numseqs]){
          sequenceCounter[numseqs]=0;
          sequencePlaying[numseqs] = 1;
        }
        long seqPeriod = (4.0/tSigs[seqs[numseqs].timeSignature])*ms_per_beat;
        if (millis()-seqTimers[numseqs] > seqPeriod){
          playSequence(numseqs);
          seqTimers[numseqs] = millis();
        }
        else{
          trigSignal[numseqs] = 0;
        }
      }
    }
    else if (holdSequence[numseqs] and sequencePlaying[numseqs]){
      if (sequencePlayingCheck){
        if (!triggered[numseqs] and trigSignalCheck){
          triggered[numseqs] = 1;
        }
        if (triggered[numseqs]){
          if (!sequencePlaying[numseqs]){
            sequenceCounter[numseqs]=0;
            sequencePlaying[numseqs] = 1;
          }
          long seqPeriod = (4.0/tSigs[seqs[numseqs].timeSignature])*ms_per_beat;
          if (millis()-seqTimers[numseqs] > seqPeriod){
            playSequence(numseqs);
            seqTimers[numseqs] = millis();
          }
          else{
            trigSignal[numseqs] = 0;
          }
        }  
      }
      else{
        if (!sequencePlaying[numseqs]){
          sequenceCounter[numseqs]=0;
          sequencePlaying[numseqs] = 1;
        }
        long seqPeriod = (4.0/tSigs[seqs[numseqs].timeSignature])*ms_per_beat;
        if (millis()-seqTimers[numseqs] > seqPeriod){
          playSequence(numseqs);
          seqTimers[numseqs] = millis();
        }
        else{
          trigSignal[numseqs] = 0;
        }
      }
    }
    else if (!playSequenceNum[numseqs] and sequencePlaying[numseqs]){
      if (sequenceCounter[numseqs] == 0 and looped[numseqs]){
        OnNoteOff(seqs[numseqs].instrument,seqs[numseqs].notes[sequenceLength[numseqs]-1],100);
      }
      else{
        OnNoteOff(seqs[numseqs].instrument,seqs[numseqs].notes[sequenceCounter[numseqs]-1],100);
      }
      sequenceCounter[numseqs]=sequenceLength[numseqs];
      sequencePlaying[numseqs] = 0;
      seqTimers[numseqs];
      looped[numseqs] = 0;
      triggered[numseqs]=0;
    }
  }
}

void playSequence(byte sequence){
    trigSignal[sequence] = 1;
    
    if (holdflag[sequence] and !(seqs[sequence].notes[sequenceCounter[sequence]] == 2)){
      OnNoteOff(seqs[sequence].instrument,holdvalue[sequence],100);
      holdflag[sequence] = false;
      if(seqs[sequence].notes[sequenceCounter[sequence]]){
        OnNoteOn(seqs[sequence].instrument,seqs[sequence].notes[sequenceCounter[sequence]],seqs[sequence].gains[sequenceCounter[sequence]]);
      }
    }
    else if (!(seqs[sequence].notes[sequenceCounter[sequence]] == 2)){
      if (!sequenceCounter[sequence] and looped[sequence]){
        OnNoteOff(seqs[sequence].instrument,seqs[sequence].notes[sequenceLength[sequence]-1],100);
      }
      else{
        OnNoteOff(seqs[sequence].instrument,seqs[sequence].notes[sequenceCounter[sequence]-1],100);
      }
      if(seqs[sequence].notes[sequenceCounter[sequence]]){
        OnNoteOn(seqs[sequence].instrument,seqs[sequence].notes[sequenceCounter[sequence]],seqs[sequence].gains[sequenceCounter[sequence]]);
      }
    }
    else if (!holdflag[sequence]){
      if (sequenceCounter[sequence]){
        holdvalue[sequence] = seqs[sequence].notes[sequenceCounter[sequence]-1];
      }
      else{
        holdvalue[sequence] = 0;
      }
      holdflag[sequence] = true;
      
    }

    sequenceCounter[sequence] ++;
    if (sequenceCounter[sequence] == sequenceLength[sequence]){
      sequenceCounter[sequence]=0;
      looped[sequence] = 1;
    } 
}
