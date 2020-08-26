long metronomeTimer = millis();

void metronomePlayer(){
  if (metronomeEnable == 2){
    if (millis()-metronomeTimer > ms_per_beat){
      metronome.play(AudioSampleMetronome);
      if (armLocation){
        armLocation = 0;
      }
      else{
        armLocation = 1;
      }
      metronomeTimer = millis();
    }
  }
}

void tapMetronome(){
  metronome.play(AudioSampleMetronome);
  tapTempo.update();
  bpm = tapTempo.getBPM();
}
