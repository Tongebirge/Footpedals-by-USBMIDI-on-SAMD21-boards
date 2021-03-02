// TONGEBIRGE FOOTJOV
// v0.1

#pragma once
#include "MIDIUSB.h"

// define pin 
const int susPin = 6;
const int expPin = A7;
const int susConnectPin = 8;
const int expConnectPin = 9;

// define variables
int susState = 0;
int susConnect = 0;
int susPorality = 0;
int susCount = 0;
int expValue = 0;
int expConnect = 0;

// send CC on USB-MIDI function
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void setup() {
  //Serial.begin(115200);
  pinMode(susConnectPin, INPUT_PULLUP);
  pinMode(expConnectPin, INPUT_PULLUP);
  pinMode(susPin, INPUT_PULLUP);
  susPorality = digitalRead(susPin); // Reading Sustain Pedal Porality
  delay(100); // After delay
  analogReadResolution(8); // Analog input be 256 step
}

void loop() {
  susConnect = digitalRead(susConnectPin);
  expConnect = digitalRead(expConnectPin);
  susState = digitalRead(susPin);
  expValue = analogRead(expPin) / 2;
  
  if(susConnect != 0 && susState != susPorality) {
    if(susCount == 0) {
      susCount = 1;
      controlChange(0, 64, 127); // Sustain ON
      MidiUSB.flush();
    }
  }else if(susConnect != 0 && susState == susPorality) {
    if (susCount == 1) {
      susCount = 0;
      controlChange(0, 64, 0);  // Sustain OFF
      delay(1);
    }
  }else if(susConnect == 0) {
    if(susCount == 1) {
      susCount = 0;
      controlChange(0, 64, 0);   // Sustain OFF
      delay(1);
    }
  }
  if(expConnect != 0 && expValue != 0) {
    controlChange(0, 11, expValue);   // Expression thru A4 value
    MidiUSB.flush();
  }
  delay(10);
}
