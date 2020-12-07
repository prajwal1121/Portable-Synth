//
// V2 I2C Input Processor
// Written by Prajwal Tumkur Mahesh
//

#include <Wire.h>

//Indicators for new data
#define LED 7
#define alert_pin 27

// Assign button matrix row pins
#define numRowPins 7
const int rowPins[numRowPins] = {0, 1, 2, 3, 4, 5, 6};

// Assign button matrix column pins
#define  numColPins 7
const int colPins[numColPins] = {8, 9, 10, 11, 12, 13, 14};

int prevState[numRowPins][numColPins] = {0};
int buttonIdx = 0;
int byteIdx = 0;
int bitIdx = 0;

//Quadrature Encoder Parameters
#define NUM_ENC 4
#define ENCA1 18 //Encoder 1 Pin A
#define ENCB1 19 //Encoder 1 Pin B
#define ENCA2 20  //Encoder 2 Pin A
#define ENCB2 21  //Encoder 2 Pin B
#define ENCA3 22 //Encoder 3 Pin A
#define ENCB3 23  //Encoder 3 Pin B
#define ENCA4 24  //Encoder 4 Pin A
#define ENCB4 25  //Encoder 4 Pin B
bool currentState1A;
bool currentState2A;
bool currentState3A;
bool currentState4A;
bool lastState1A;
bool lastState2A;
bool lastState3A;
bool lastState4A;
int8_t counter[NUM_ENC] = {0,0,0,0};

const int encButtonPins[NUM_ENC] = {30,31,32,33};
bool encButtonPrevState[NUM_ENC] = {0,0,0,0};

//Message length in bytes: 1 bit per button+ 2 bits per encoder
//51 bits for 51 buttons + 8 bits for 4 encoders = 58 bits
#define NUM_BYTES 8 
byte buttonStates[NUM_BYTES] = {0,0,0,0,0,0,0,0};

void setup() {
  /*Encoder pins are connected/disconnected to GND
  so they need to be pulled high as a default*/ 
  pinMode(ENCA1,INPUT_PULLUP);
  pinMode(ENCB1,INPUT_PULLUP);
  pinMode(ENCA2,INPUT_PULLUP);
  pinMode(ENCB2,INPUT_PULLUP);
  pinMode(ENCA3,INPUT_PULLUP);
  pinMode(ENCB3,INPUT_PULLUP);
  pinMode(ENCA4,INPUT_PULLUP);
  pinMode(ENCB4,INPUT_PULLUP); 
  
  //Initialize the state of each encoder
  lastState1A = digitalRead(ENCA1);
  lastState2A = digitalRead(ENCA2);
  lastState3A = digitalRead(ENCA3);
  lastState4A = digitalRead(ENCA4);
  
  /*Attach both pins of each encoder to a hardware interrupt to keep track
  of every change*/
  attachInterrupt(ENCA1, updateEncoder1, CHANGE);
  attachInterrupt(ENCB1, updateEncoder1, CHANGE);
  attachInterrupt(ENCA2, updateEncoder2, CHANGE);
  attachInterrupt(ENCB2, updateEncoder2, CHANGE);
  attachInterrupt(ENCA3, updateEncoder3, CHANGE);
  attachInterrupt(ENCB3, updateEncoder3, CHANGE);
  attachInterrupt(ENCA4, updateEncoder4, CHANGE);
  attachInterrupt(ENCB4, updateEncoder4, CHANGE);

  //Initialize Indicators and initialize them to low (nothing to report)
  pinMode(LED, OUTPUT);
  digitalWrite (LED, LOW);
  
  pinMode(alert_pin, OUTPUT);
  digitalWrite (alert_pin, LOW);

  /*All pushbuttons are connected/disconnected to GND
  so they need to be pulled high as a default
  */
  for(int cPin = 0; cPin < numColPins; cPin++)
  {
    pinMode(colPins[cPin], OUTPUT);
    digitalWrite(colPins[cPin], HIGH);
  }
  for(int rPin = 0; rPin < numRowPins; rPin++)
  {
    pinMode(rowPins[rPin], INPUT);
    digitalWrite(rowPins[rPin], HIGH);
  }
  for(int encoderButton = 0; encoderButton < NUM_ENC; encoderButton++)
  {
    pinMode(encButtonPins[encoderButton], INPUT_PULLUP);
  }

  /*Join I2c bus as a slave with address 9
  We're using the alternative I2C pins 16 and 17
  so make sure to add the .swap()
  */
  Wire.swap(1);
  Wire.begin(9);
  //Every time master device requests data, call requestEvent()                
  Wire.onRequest(requestEvent); 
}

void loop() {
/*Iterate over all buttons on the board and update their status in the
    output message only on a rising/falling edge. This way the message is 
    only updated when there is new data.
   */
  // Loop through the columns
  for(int cPin = 0; cPin < numColPins; cPin++)
  {
    //Set the voltage at the current column to LOW/GND
    digitalWrite(colPins[cPin], LOW);
    
    // Loop through the rows
    for(int rPin = 0; rPin < numRowPins; rPin++)
    {
      buttonIdx = 7*rPin+cPin;
      byteIdx = (buttonIdx)/8;
      bitIdx = buttonIdx-(byteIdx*8);
      
      //Check if each switch is pressed. Since the column is set to be LOW,
      // a button that's pressed would also read LOW
      if(digitalRead(rowPins[rPin]) == LOW)
      {
        //Only update the  message if the button state has changed since 
        // last time we checked
        if(prevState[cPin][rPin] == 0)
        {
          //indicate new data
          digitalWrite(LED, HIGH);
          digitalWrite(alert_pin, HIGH); 

          //Flip the corresponding bit to 1 (on)
          bitSet(buttonStates[byteIdx],bitIdx);

          // Update last known state of this switch
          prevState[cPin][rPin] = 1;
        }
      } 
      //Check if each switch is released. Since the column is set to be LOW,
      // a button that's released would read HIGH
      else {
        //Only update the  message if the button state has changed since 
        // last time we checked
        if(prevState[cPin][rPin] == 1)
        {
          //indicate new data
          digitalWrite(LED, HIGH);
          digitalWrite(alert_pin, HIGH);
  
          //Flip the corresponding bit to 0 (off) 
          bitClear(buttonStates[byteIdx],bitIdx);
          
          // Update last known state of this switch
          prevState[cPin][rPin] = 0;
        }
      }
    }
    //Pull the column back up again before we move on
    digitalWrite(colPins[cPin], HIGH);
  }

  
  /*Update message with the state of each encoder.
    Each encoder gets 2 bits to report its status*/
  for (byte e = 0; e < NUM_ENC; e++)  {
    //Read the encoder select button
    if(digitalRead(encButtonPins[e])==LOW)
    {
      if(encButtonPrevState[e] == 0)
      {
          //indicate new data
          digitalWrite(LED, HIGH);
          digitalWrite(alert_pin, HIGH); 

          //Flip the corresponding bit to 1 (on)
          bitSet(buttonStates[6],e);

          // Update last known state of this switch
          encButtonPrevState[e] = 1;
      }
    }
    else {
      if(encButtonPrevState[e] == 1)
      {
          //indicate new data
          digitalWrite(LED, HIGH);
          digitalWrite(alert_pin, HIGH); 

          //Flip the corresponding bit to 0 (off)
          bitClear(buttonStates[6],e);

          // Update last known state of this switch
          encButtonPrevState[e] = 0;
      }
    }
    
    //If Encoder has been incremented...
    if (counter[e] > 0){
      //indicate new data
      digitalWrite(LED, HIGH);
      digitalWrite(alert_pin, HIGH);
      //Flip corresponding bits to 01, or 1 (forward) 
      bitSet(buttonStates[7], e*2);
    }
    //If Encoder has been incremented...
    else if (counter[e] < 0){
      digitalWrite(LED, HIGH);
      digitalWrite(alert_pin, HIGH);
      //Flip corresponding bits to 10, or 2 (backwards)  
      bitSet(buttonStates[7], e*2+1);
    }
    //If nothing has changed with Encoder...
    else{
      //Reset corresponding bits to 00, or 0 
      bitClear(buttonStates[7], e*2);
      bitClear(buttonStates[7], e*2+1);
    }
  }
  delay(1);//delay for sanity
}

//Runs on data request from Teensy
void requestEvent()
{ 
  //Indicate data has been read
  digitalWrite(LED, LOW);
  digitalWrite(alert_pin, LOW);
  //Write 8 bytes of data
  Wire.write(buttonStates,8);
  //Reset encoder counts
  memset(counter, 0, sizeof(counter));
  buttonStates[7] = 0;
}

/*Runs on pin-change interrupt for Encoder 1
  Increments or decrements counter dependng on direction of rotation
 */
void updateEncoder1(){
    currentState1A = digitalRead(ENCA1);
    if (currentState1A != lastState1A  && currentState1A == 1){
      if (digitalRead(ENCB1) != currentState1A) {
        counter[0] ++;
      } else {
        counter[0] --;
      } 
    }
    lastState1A = currentState1A;
}

//Runs on pin-change interrupt for Encoder 2
void updateEncoder2(){
    currentState2A = digitalRead(ENCA2);
    if (currentState2A != lastState2A  && currentState2A == 1){
      if (digitalRead(ENCB2) != currentState2A) {
        counter[1] ++;
      } else {
        counter[1] --;
      } 
    }
    lastState2A = currentState2A;
}

//Runs on pin-change interrupt for Encoder 3
void updateEncoder3(){
    currentState3A = digitalRead(ENCA3);
    if (currentState3A != lastState3A  && currentState3A == 1){
      if (digitalRead(ENCB3) != currentState3A) {
        counter[2] ++;
      } else {
        counter[2] --;
      } 
    }
    lastState3A = currentState3A;
}

//Runs on pin-change interrupt for Encoder 4
void updateEncoder4(){
    currentState4A = digitalRead(ENCA4);
    if (currentState4A != lastState4A  && currentState4A == 1){
      if (digitalRead(ENCB4) != currentState4A) {
        counter[3] ++;
      } else {
        counter[3] --;
      } 
    }
    lastState4A = currentState4A;
}
