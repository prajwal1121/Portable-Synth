/*
 * Audio playback code. The following functions are used    
 * to play sounds when keys are pressed, handle 8 note
 * polyphony, and generally update the connections and
 * parameters of the various audio system elements
 */
byte keystate[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool controlstate[4] = {0,0,0,0};
const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};
byte isAnythingPlaying = 0;

void playKeyboard(){   
  for (int i = 0; i < 24; i++){
    current_byte = i/8;
    current_button = i-8*current_byte;
    if (keyboardButtons[i]){
      if (!keystate[i]){
        byte voiceNum = nextAvailableVoice();
        currentFreqs[voiceNum] = i+48;
        polyPlay(voiceNum,i+48);
        mod_env1.noteOn();
        mod_env2.noteOn();
        keystate[i] = voiceNum+1;
      }
    }
    else{
      if (keystate[i]){ 
        byte voiceNum = keystate[i]-1;
        currentFreqs[voiceNum] = 0;
        envelope_bank[voiceNum]->noteOff();
        mod_env1.noteOff();
        mod_env2.noteOff();
        keystate[i] = 0;
        voiceStates[voiceNum]=0;
      }
    }
  }

  if (left){
    if(!controlstate[2]){
      octave = octave - 12;
      if (octave < -24){
        octave = -24;
      }
      controlstate[2] = 1;
    }
  }
  else{
    if(controlstate[2]){
      controlstate[2] = 0;
    }
  }

  if (right){
    if(!controlstate[3]){
      octave = octave + 12;
      if (octave > 24){
        octave = 24;
      }
      controlstate[3] = 1;
    }
  }
  else{
    if(controlstate[3]){
      controlstate[3] = 0;
    }
  }
}

void switchWave (byte oscillatorNum){
    waveShape[oscillatorNum] += 1;
    if (waveShape[oscillatorNum] > 8) waveShape[oscillatorNum] = 0; 
    
    switch (oscillatorNum){
      case 1:
        for (byte a = 0; a < 8; a++){
          a_bank[a]->begin(waveShape[oscillatorNum]);
        }
        break;
      case 2:
        for (byte b = 0; b < 8; b++){
          b_bank[b]->begin(waveShape[oscillatorNum]);
        }
        break;
    }
}

const byte BUFFER = 8;

void keyBuff(byte note, bool noteState) {
  static byte buff[BUFFER];
  static byte buffSize = 0;

  // Add Note
  if (noteState == true and (buffSize < BUFFER) ) {
    oscPlay(note);
    buff[buffSize] = note;
    buffSize++;
    return;
  }

  // Remove Note
  else if (noteState == false and (buffSize != 0)) {
    for (byte found = 0; found < buffSize; found++) {
      if (buff[found] == note) {
        for (byte gap = found; gap < (buffSize - 1); gap++) {
          buff[gap] = buff[gap + 1];
        }
        buffSize--;
        buff[buffSize] = 255;
        if (buffSize != 0) {
          oscPlay(buff[buffSize - 1]);
          return;
        }
        else {
          oscStop();
          return;
        }
      }
    }
  }
}

void oscPlay(byte note) {
  for (byte n = 0; n < 8; n++){
    noise_bank[n]->amplitude(waveAmplitude[0]);
  }
  for (byte a = 0; a < 8; a++){
    a_bank[a]->amplitude(waveAmplitude[1]);
    a_bank[a]->frequency((noteFreqs[note+octave])*pitchBend);
  }
  for (byte b = 0; b < 8; b++){
    b_bank[b]->amplitude(waveAmplitude[2]);
    b_bank[b]->frequency(noteFreqs[note+semitonesTune]*detuneFactor*pitchBend);
  }
  for (byte e = 0; e < 8; e++){
    envelope_bank[e]->noteOn();
  }
  
}

void oscStop() {
  for (byte e = 0; e < 8; e++){
    envelope_bank[e]->noteOff();
  }
}

void polyPlay(byte voiceNum, byte note){
  AudioNoInterrupts();
  noise_bank[voiceNum]->amplitude(waveAmplitude[0]);

  a_bank[voiceNum]->amplitude(waveAmplitude[1]);
  a_bank[voiceNum]->frequency((noteFreqs[note+octave])*pitchBend);

  b_bank[voiceNum]->amplitude(waveAmplitude[2]);
  b_bank[voiceNum]->frequency(noteFreqs[note+semitonesTune]*detuneFactor*pitchBend);

  envelope_bank[voiceNum]->noteOn();
  AudioInterrupts();
}

void updateFreq(){
  for (byte v = 0; v < 8; v++){
    if (voiceStates[v]){
       AudioNoInterrupts();
       a_bank[v]->frequency((noteFreqs[currentFreqs[v]+octave])*pitchBend);
       b_bank[v]->frequency(noteFreqs[currentFreqs[v]+semitonesTune]*detuneFactor*pitchBend);
       AudioInterrupts();
    }
  }
}

void updateEnvelope() {
  for (byte e = 0; e < 8; e++){
    envelope_bank[e]->attack(adsr[0]);
    envelope_bank[e]->decay(adsr[1]);
    envelope_bank[e]->sustain(adsr[2]);
    envelope_bank[e]->release(adsr[3]);
  }
}

void updateFilter(){
    for (byte f = 0; f < 8; f++){
    filter_bank[f]->frequency(filterFreq+filterBend);
    filter_bank[f]->resonance(filterQ);
  }
}

void updateModLFODest(byte LFOnum){
  if (LFODest[LFOnum][0]) {
    if (LFOnum==0 and (!envDest[0][3] or !envDest[1][3]))osc1_pitch_mod_mixer.gain(0,1.0);
    else if (LFOnum==1 and (!envDest[0][4] or !envDest[1][4]))osc1_pitch_mod_mixer.gain(1,1.0);
  }
  else {
    if (LFOnum==0)osc1_pitch_mod_mixer.gain(0,0.0);
    else if (LFOnum==1)osc1_pitch_mod_mixer.gain(1,0.0);
  }

  if (LFODest[LFOnum][1]) {
    if (LFOnum==0 and (!envDest[0][3] or !envDest[1][3]))osc2_pitch_mod_mixer.gain(0,1.0);
    else if (LFOnum==1 and (!envDest[0][4] or !envDest[1][4]))osc2_pitch_mod_mixer.gain(1,1.0);
  }
  else {
    if (LFOnum==0)osc2_pitch_mod_mixer.gain(0,0.0);
    else if (LFOnum==1)osc2_pitch_mod_mixer.gain(1,0.0);
  }

  if (LFODest[LFOnum][2]) {
    if (LFOnum==0 and (!envDest[0][3] or !envDest[1][3]))filter_cutoff_mod_mixer.gain(0,1.0);
    else if (LFOnum==1 and (!envDest[0][4] or !envDest[1][4]))filter_cutoff_mod_mixer.gain(1,1.0);
  }
  else {
    if (LFOnum==0)filter_cutoff_mod_mixer.gain(0,0.0);
    else if (LFOnum==1)filter_cutoff_mod_mixer.gain(1,0.0);
  }

  if (LFODest[LFOnum][3]) {
    if (LFOnum==0 and (!envDest[0][3] or !envDest[1][3]))LFO2_mixer.gain(0,1.0);
    else if (LFOnum==1 and (!envDest[0][4] or !envDest[1][4]))LFO1_mixer.gain(0,1.0);
  }
  else {
    if (LFOnum==0)LFO2_mixer.gain(0,0.0);
    else if (LFOnum==1)LFO1_mixer.gain(0,0.0);
  }
}

void updateModLFO(byte LFOnum){
  if (LFOnum==0){
    AudioNoInterrupts();
    mod_LFO1.frequency(LFOFrequency[0]);
    mod_LFO1.amplitude(LFOAmplitude[0]);
    AudioInterrupts();
  }
  else if (LFOnum==1){
    AudioNoInterrupts();
    mod_LFO2.frequency(LFOFrequency[1]);
    mod_LFO2.amplitude(LFOAmplitude[1]);
    AudioInterrupts();
  }
}

void updateModLFOShape(byte LFOnum){
  if (LFOnum==0){
    AudioNoInterrupts();
    mod_LFO1.begin(LFOWaveShape[0]);
    AudioInterrupts();
  }
  else if (LFOnum==1){
    AudioNoInterrupts();
    mod_LFO2.begin(LFOWaveShape[1]);
    AudioInterrupts();
  }
}

void updateModEnvDest(byte envnum){
  if (envDest[envnum][0]) {
    if (envnum==0)osc1_pitch_mod_mixer.gain(2,1.0);
    else if (envnum==1)osc1_pitch_mod_mixer.gain(3,1.0);
  }
  else {
    if (envnum==0)osc1_pitch_mod_mixer.gain(2,0.0);
    else if (envnum==1)osc1_pitch_mod_mixer.gain(3,0.0);
  }

  if (envDest[envnum][1]) {
    if (envnum==0)osc2_pitch_mod_mixer.gain(2,1.0);
    else if (envnum==1)osc2_pitch_mod_mixer.gain(3,1.0);
  }
  else {
    if (envnum==0)osc2_pitch_mod_mixer.gain(2,0.0);
    else if (envnum==1)osc2_pitch_mod_mixer.gain(3,0.0);
  }

  if (envDest[envnum][2]) {
    if (envnum==0)filter_cutoff_mod_mixer.gain(2,1.0);
    else if (envnum==1)filter_cutoff_mod_mixer.gain(3,1.0);
  }
  else {
    if (envnum==0)filter_cutoff_mod_mixer.gain(2,0.0);
    else if (envnum==1)filter_cutoff_mod_mixer.gain(3,0.0);
  }

  if (envDest[envnum][3]) {//Enabled LFO1 mod
    if (envnum==0){
      env1_mixer.gain(0,1.0);
      
      //Turn off LFO1 direct connections
      osc1_pitch_mod_mixer.gain(0,0.0);
      osc2_pitch_mod_mixer.gain(0,0.0);
      filter_cutoff_mod_mixer.gain(0,0.0);
      LFO2_mixer.gain(0,0.0);
    }
    else if (envnum==1){
      env2_mixer.gain(0,1.0);

      //Turn off LFO1 direct connections
      osc1_pitch_mod_mixer.gain(0,0.0);
      osc2_pitch_mod_mixer.gain(0,0.0);
      filter_cutoff_mod_mixer.gain(0,0.0);
      LFO2_mixer.gain(0,0.0);
    }
  }
  else {//Disabled LFO1 mod
    if (envnum==0){
      env1_mixer.gain(0,0.0);
      
      //Turn off LFO1 direct connections
      if (LFODest[0][0]) osc1_pitch_mod_mixer.gain(0,1.0);
      if (LFODest[0][1]) osc2_pitch_mod_mixer.gain(0,1.0);
      if (LFODest[0][2]) filter_cutoff_mod_mixer.gain(0,1.0);
      if (LFODest[0][3]) LFO2_mixer.gain(0,1.0);
    }
    else if (envnum==1){
      env2_mixer.gain(0,0.0);
      
      //Turn off LFO1 direct connections
      if (LFODest[0][0]) osc1_pitch_mod_mixer.gain(0,1.0);
      if (LFODest[0][1]) osc2_pitch_mod_mixer.gain(0,1.0);
      if (LFODest[0][2]) filter_cutoff_mod_mixer.gain(0,1.0);
      if (LFODest[0][3]) LFO2_mixer.gain(0,1.0);
    }
  }

  if (envDest[envnum][4]) {//Enabled LFO2 mod
    if (envnum==0){
      env1_mixer.gain(1,1.0);

      //Turn off LFO2 direct connections
      osc1_pitch_mod_mixer.gain(1,0.0);
      osc2_pitch_mod_mixer.gain(1,0.0);
      filter_cutoff_mod_mixer.gain(1,0.0);
      LFO1_mixer.gain(0,0.0);
    }
    else if (envnum==1){
      env2_mixer.gain(1,1.0);

      //Turn off LFO2 direct connections
      osc1_pitch_mod_mixer.gain(1,0.0);
      osc2_pitch_mod_mixer.gain(1,0.0);
      filter_cutoff_mod_mixer.gain(1,0.0);
      LFO1_mixer.gain(0,0.0);
    }
  }
  else {//Disabled LFO2 mod
    if (envnum==0){
      env1_mixer.gain(1,0.0);
  
      //Turn off LFO1 direct connections
      if (LFODest[1][0]) osc1_pitch_mod_mixer.gain(1,1.0);
      if (LFODest[1][1]) osc2_pitch_mod_mixer.gain(1,1.0);
      if (LFODest[1][2]) filter_cutoff_mod_mixer.gain(1,1.0);
      if (LFODest[1][3]) LFO2_mixer.gain(1,1.0);
    }
    else if (envnum==1){
      env2_mixer.gain(1,0.0);
            
      //Turn off LFO1 direct connections
      if (LFODest[1][0]) osc1_pitch_mod_mixer.gain(1,1.0);
      if (LFODest[1][1]) osc2_pitch_mod_mixer.gain(1,1.0);
      if (LFODest[1][2]) filter_cutoff_mod_mixer.gain(1,1.0);
      if (LFODest[1][3]) LFO2_mixer.gain(1,1.0);
    }
  }
}

void updateModEnvelope(byte envnum) {
  if (envnum==0){
    mod_env1.attack(modadsr[envnum][0]);
    mod_env1.decay(modadsr[envnum][1]);
    mod_env1.sustain(modadsr[envnum][2]);
    mod_env1.release(modadsr[envnum][3]);
    env1_dc.amplitude(modadsr[envnum][4]);
  }
  else if (envnum==1){
    mod_env2.attack(modadsr[envnum][0]);
    mod_env2.decay(modadsr[envnum][1]);
    mod_env2.sustain(modadsr[envnum][2]);
    mod_env2.release(modadsr[envnum][3]);
    env2_dc.amplitude(modadsr[envnum][4]);
  }
}

byte nextAvailableVoice(){
  byte counter = 0;
  for (byte s = 0; s < 8; s++){
    if (voiceStates[s]){
      counter++;
    }
  }
  if (counter == 8){
    byte minimum = 69;
    byte minidx = 69;
    for (byte s = 0; s < 8; s++){
      if (voiceStates[s] < minimum){
        minidx = s;
        minimum = voiceStates[s];
      }
    }
    for (byte s = 0; s < 8; s++){
      voiceStates[s] = voiceStates[s]-1;
    }
    voiceStates[minidx] = counter;
    return minidx;
  }
  else{
    for (byte s = 0; s < 8; s++){
      if (voiceStates[s] == 0){
        voiceStates[s] = counter+1;
        return s;
      }
    }
  }
}
