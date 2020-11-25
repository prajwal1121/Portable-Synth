#define PINK   0xFF1088
#define RED    0xFF0000
#define WHITE_LED  0xFFFFFF
#define BLACK_LED  0x000000

void doLEDs(){
  if (recordSelect){
    if (record_input_peak.available()){
      float pk = record_input_peak.read();
      pk=map(pk,0.01,0.1,0,10);
      
      for (int i=9; i > 9-pk; i--) {
        leds.setPixel(i, WHITE_LED);
      }
      for (int i=0; i < 9-pk; i++) {
        leds.setPixel(i, RED);
      }
      leds.show();
    }
  }
  if (inputMethod == 1){
    if (record_input_peak.available()){
      float pk = record_input_peak.read();
      pk=map(pk,0.01,0.1,0,10);
      
      for (int i=9; i > 9-pk; i--) {
        leds.setPixel(i, PINK);
      }
      for (int i=0; i < 9-pk; i++) {
        leds.setPixel(i, BLACK_LED);
      }
      leds.show();
    }
  }
  if (previewSelect){
    if (record_output_peak.available()){
      float pk = record_output_peak.read();
      pk=map(pk,0.01,0.1,0,10);
      
      for (int i=9; i > 9-pk; i--) {
        leds.setPixel(i, WHITE_LED);
      }
      for (int i=0; i < 9-pk; i++) {
        leds.setPixel(i, BLACK_LED);
      }
      leds.show();
    }
  }
}

void turnOffLEDs(){
  for (int i=0; i < numled; i++) {
    leds.setPixel(i, BLACK_LED);
  }
  leds.show();
}
