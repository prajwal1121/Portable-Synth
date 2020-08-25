int allocateVoice(byte channel, byte note);
int findVoice(byte channel, byte note);
void freeVoices();

int used_voices = 0;
int stopped_voices = 0;
int evict_voice = 0;
int notes_played = 0;

void OnNoteOn(byte channel, byte note, byte velocity) {
  notes_played++;
  freeVoices();
  int wavetable_id = allocateVoice(channel, note);
  switch (channel) {
  case 1:
    wavetable[wavetable_id].setInstrument(distortiongt);
    break;
  case 2:
    wavetable[wavetable_id].setInstrument(piano);
    break;
  case 3:
    wavetable[wavetable_id].setInstrument(Ocarina);
    break;
  case 4:
    wavetable[wavetable_id].setInstrument(standard_DRUMS);
    break;
  case 5:
    wavetable[wavetable_id].setInstrument(Pizzicato);
    break;
  default:
    wavetable[wavetable_id].setInstrument(standard_DRUMS);
    break;
  }
  wavetable[wavetable_id].playNote(note, velocity);
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  int wavetable_id = findVoice(channel, note);
  if (wavetable_id != TOTAL_VOICES)
    wavetable[wavetable_id].stop();
}

int allocateVoice(byte channel, byte note) {
  int i;
  int nonfree_voices = stopped_voices + used_voices;
  if (nonfree_voices < TOTAL_VOICES) {
    for (i = nonfree_voices; i < TOTAL_VOICES && voices[i].channel != channel; ++i);
    if (i < TOTAL_VOICES) {
      voice_t temp = voices[i];
      voices[i] = voices[nonfree_voices];
      voices[nonfree_voices] = temp;
    }
    i = nonfree_voices;
    used_voices++;
  }
  else {
    if (stopped_voices) {
      i = evict_voice % stopped_voices;
      voice_t temp = voices[i];
      stopped_voices--;
      voices[i] = voices[stopped_voices];
      voices[stopped_voices] = temp;
      used_voices++;
      i = stopped_voices;
    }
    else
      i = evict_voice;
  }

  voices[i].channel = channel;
  voices[i].note = note;

  evict_voice++;
  evict_voice %= TOTAL_VOICES;

  return voices[i].wavetable_id;
}

int findVoice(byte channel, byte note) {
  int i;
  //find match
  int nonfree_voices = stopped_voices + used_voices;
  for (i = stopped_voices; i < nonfree_voices && !(voices[i].channel == channel && voices[i].note == note); ++i);
  //return TOTAL_VOICES if no match
  if (i == (nonfree_voices)) return TOTAL_VOICES;

  voice_t temp = voices[i];
  voices[i] = voices[stopped_voices];
  voices[stopped_voices] = temp;
  --used_voices;

  return voices[stopped_voices++].wavetable_id;
}

void freeVoices() {
  for (int i = 0; i < stopped_voices; i++)
    if (wavetable[voices[i].wavetable_id].isPlaying() == false) {
      voice_t temp = voices[i];
      --stopped_voices;
      voices[i] = voices[stopped_voices];
      int nonfree_voices = stopped_voices + used_voices;
      voices[stopped_voices] = voices[nonfree_voices];
      voices[nonfree_voices] = temp;
    }
}
