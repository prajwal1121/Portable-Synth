bool recordPrev = 0;
bool prevewPrev = 0;

void recordAndStore(){
  if (recordSelect and !recordPrev) {
    if (recordMode == 0) startRecording();
  }
  else if (!recordSelect and recordPrev){
    if (recordMode == 1) stopRecording();
    turnOffLEDs();
  }
  recordPrev = recordSelect;

  if (previewSelect and !prevewPrev) {
    if (recordMode == 1) stopRecording();
    if (recordMode == 0) startPlayingPreview();
  }
  else if (!previewSelect and prevewPrev){
    if (recordMode == 2) stopPlayingPreview();
    turnOffLEDs();
  }
  prevewPrev = previewSelect;
  
  if (recordMode == 1) continueRecording();
  if (recordMode == 2) continuePlayingPreview();
}

void startRecording() {
  sgtl5000_1.micGain(microphoneGain);
  if (SD.exists(recs[currentRecording].fileName)) {
    SD.remove(recs[currentRecording].fileName);
  }
  recs[currentRecording].file = SD.open(recs[currentRecording].fileName, FILE_WRITE);
  if (recs[currentRecording].file) {
    if ((inputMethod == 1) or (inputMethod == 0)){
      record_input_queue.begin();
    }
    else if (inputMethod == 2){
      internal_recording_queue.begin();
    }
    recordMode = 1;
  }
}

void continueRecording() {
  if ((inputMethod == 1) or (inputMethod == 0)){
    if (record_input_queue.available() >= 2) {
      byte buffer[512];
      memcpy(buffer, record_input_queue.readBuffer(), 256);
      record_input_queue.freeBuffer();
      memcpy(buffer+256, record_input_queue.readBuffer(), 256);
      record_input_queue.freeBuffer();
      recs[currentRecording].file.write(buffer, 512);
    }
  }
  else if (inputMethod == 2){
    if (internal_recording_queue.available() >= 2) {
      byte buffer[512];
      memcpy(buffer, internal_recording_queue.readBuffer(), 256);
      internal_recording_queue.freeBuffer();
      memcpy(buffer+256, internal_recording_queue.readBuffer(), 256);
      internal_recording_queue.freeBuffer();
      recs[currentRecording].file.write(buffer, 512);
    }
  }
}

void stopRecording() {
  if ((inputMethod == 1) or (inputMethod == 0)){
    record_input_queue.end();
    if (recordMode == 1) {
      while (record_input_queue.available() > 0) {
        recs[currentRecording].file.write((byte*)record_input_queue.readBuffer(), 256);
        record_input_queue.freeBuffer();
      }
      recs[currentRecording].file.close();
    }
  }
  else if (inputMethod == 2){
    internal_recording_queue.end();
    if (recordMode == 1) {
      while (internal_recording_queue.available() > 0) {
        recs[currentRecording].file.write((byte*)internal_recording_queue.readBuffer(), 256);
        internal_recording_queue.freeBuffer();
      }
      recs[currentRecording].file.close();
    }
  }
  playRaw1.play(recs[currentRecording].fileName,0);
  recs[currentRecording].fileSize = playRaw1.lengthMillis();
  playRaw1.stop();
  currentEndTime = recs[currentRecording].fileSize;
  recordMode = 0;
}

void startPlayingPreview() {
  record_output_mixer.gain(0,outputGain);
  recs[currentRecording].file.close();
  playRaw1.play(recs[currentRecording].fileName,currentStartTime);
  recordMode = 2;
}

void continuePlayingPreview() {
  if (!playRaw1.isPlaying()) {
    playRaw1.stop();
    recordMode = 0; 
  }
  
  showPlaying = true;
  playPosition = (1.0*playRaw1.positionMillis())/(1.0*recs[currentRecording].fileSize);

  if (playRaw1.positionMillis() >= currentEndTime){
    playRaw1.stop();
    recordMode = 0;
  }
}

void stopPlayingPreview() {
  playRaw1.stop();
  showPlaying = false;
  recordMode = 0;
}
