byte keystate[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool controlstate[4] = {0,0,0,0};
const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};
byte isAnythingPlaying = 0;

void playKeyboard(){   
  for (int i = 0; i < 24; i++){
    current_byte = i/8;
    current_button = i-8*current_byte;
    if (bitRead(buttonStates[current_byte], current_button)){
      if (!keystate[i]){
        //keyBuff(i+48, 1);
        //keystate[i] = 1;
        byte voiceNum = nextAvailableVoice();
        polyPlay(voiceNum,i+48);
        keystate[i] = voiceNum+1;
      }
    }
    else{
      if (keystate[i]){ 
        //keyBuff(i+48, 0);
        //keystate[i] = 0;
        byte voiceNum = keystate[i]-1;
        envelope_bank[voiceNum]->noteOff();
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
//    #define WAVEFORM_SINE              0
//    #define WAVEFORM_SAWTOOTH          1
//    #define WAVEFORM_SQUARE            2
//    #define WAVEFORM_TRIANGLE          3
//    #define WAVEFORM_ARBITRARY         4
//    #define WAVEFORM_PULSE             5
//    #define WAVEFORM_SAWTOOTH_REVERSE  6
//    #define WAVEFORM_SAMPLE_HOLD       7
//    #define WAVEFORM_TRIANGLE_VARIABLE 8
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
      case 3:
        lfoShape += 1;
        if (lfoShape > 8) lfoShape= 0;
        lfo.begin(lfoShape);
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
  lfo.phase(90);
  for (byte n = 0; n < 8; n++){
    noise_bank[n]->amplitude(waveAmplitude[0]);
  }
  for (byte a = 0; a < 8; a++){
    a_bank[a]->amplitude(waveAmplitude[1]);
    a_bank[a]->frequency(noteFreqs[note]+octave);
  }
  for (byte b = 0; b < 8; b++){
    b_bank[b]->amplitude(waveAmplitude[2]);
    b_bank[b]->frequency(noteFreqs[note+semitonesTune]*detuneFactor);
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
  a_bank[voiceNum]->frequency(noteFreqs[note]+octave);

  b_bank[voiceNum]->amplitude(waveAmplitude[2]);
  b_bank[voiceNum]->frequency(noteFreqs[note+semitonesTune]*detuneFactor);

  envelope_bank[voiceNum]->noteOn();
  AudioInterrupts();
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
    filter_bank[f]->frequency(filterFreq);
    filter_bank[f]->resonance(filterQ);
  }
}

byte nextAvailableVoice(){
  byte counter = 0;
  for (int s = 0; s < 8; s++){
    if (voiceStates[s]){
      counter++;
    }
  }
  if (counter == 8){
    byte minimum = 69;
    byte minidx = 69;
    for (int s = 0; s < 8; s++){
      if (voiceStates[s] < minimum){
        minidx = s;
        minimum = voiceStates[s];
      }
    }
    for (int s = 0; s < 8; s++){
      voiceStates[s] = voiceStates[s]-1;
    }
    voiceStates[minidx] = counter;
    return minidx;
  }
  else{
    for (int s = 0; s < 8; s++){
      if (voiceStates[s] == 0){
        voiceStates[s] = counter+1;
        return s;
      }
    }
  }
}
