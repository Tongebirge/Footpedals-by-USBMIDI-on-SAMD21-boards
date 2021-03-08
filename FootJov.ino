// FOOTJOV
// Made by Tongebirge/Leo Kuroshita
// v0.5

#pragma once
#include "MIDIUSB.h" // requested MIDIUSB library

// define pin
const int susPin = 5; // sustain damper input (make boolean)
const int expPin = A3; // expression analog input (3v3 - value - GND)
const int susConnectPin = 8; // sustain connect check (make boolean)
const int expConnectPin = 9; // expression connect check (make boolean)
const int debugPin =  10; // debug mode check on boot (make boolean)

// define variables
int susState = 0;
int susConnect = 0;
int susPorality = 0;
int susCount = 0;
int expValue = 0; // raw value data from Expression analog input
int expConnect = 0;
int debugState = 0;

//send CC on USB - MIDI function
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

// debug
void debug() {
  Serial.print("Sustain: ");
  Serial.print((susConnect) ? "Yes" : "No");
  Serial.print(" / ");
  Serial.print((susPorality) ? "Negative" : "Positive");
  Serial.print(" Now: ");
  Serial.print((susState) ? "Negative" : "Positive");
  Serial.print(" | Expression: ");
  Serial.print((expConnect) ? "Yes" : "No");
  Serial.print(" / ");
  Serial.println(expValue);
}

// Initialize
void setup() {
  Serial.begin(115200); // set serial speed
  analogReadResolution(8); // analog input be 256 step

  // connect check pin be digial input with pullup
  pinMode(susConnectPin, INPUT_PULLUP);
  pinMode(expConnectPin, INPUT_PULLUP);

  // sustain pin be digial input with pullup
  pinMode(susPin, INPUT_PULLUP);

  // check sustain pedal porality on boot
  susPorality = digitalRead(susPin); // reading sustain pedal porality

  // check debug pin on boot
  pinMode(debugPin, INPUT_PULLUP);
  (debugState) = digitalRead(debugPin) ? true : false;

  delay(100); // after delay
}

void loop() {
  susConnect = digitalRead(susConnectPin);
  expConnect = digitalRead(expConnectPin);
  susState = digitalRead(susPin);
  expValue = analogRead(expPin) >> 1; // readed 8bit value to 7bit

  // sustain
  if (susConnect != 0 && susState != susPorality) {
    if (susCount == 0) {
      susCount = 1;
      controlChange(0, 64, 127); // sustain ON
      MidiUSB.flush();
    }
  } else if (susConnect != 0 && susState == susPorality) {
    if (susCount == 1) {
      susCount = 0;
      controlChange(0, 64, 0);  // sustain OFF
      delay(1);
    }
  } else if (susConnect == 0) {
    if (susCount == 1) {
      susCount = 0;
      controlChange(0, 64, 0);   // sustain OFF
      delay(1);
    }
  }

  // expression
  if (expConnect != 0) {
    if (expValue != 0) {
      controlChange(0, 11, expValue);   // expression thru A4 value
      MidiUSB.flush();


    }
  }
  delay(10);

  if (debugState) {
    debug();
  }


}
