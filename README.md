# FootJov
USB-MIDI Foot controllers interface
![IMG_0014](https://user-images.githubusercontent.com/7828838/109469058-dd443680-7ab0-11eb-8f92-7d7aff9319cd.jpg)

## Overview
An interface box just for sustain pedal and expression pedal. Just connect the board to a USB-MIDI host and you're ready to go.
The sustain pedal has polarity, but this program automatically recognizes it at startup, so you can use either one.
In my test, I used Seeed studio's XIAO, but I think it can be used with other SAMD21 boards and USB host boards.
For the enclosure, I've also uploaded an STL model I designed. Please use it by incorporating it inside.
I still have some ideas. I will update it when that time comes.

## Hardware
![IMG_0010](https://user-images.githubusercontent.com/7828838/109469773-d5d15d00-7ab1-11eb-96b9-bbce5ab7564e.jpg)
I tested with Seeed XIAO(SAMD21) board.

##### Parts
+ Seeed XIAO (or other boards)
+ **Two** 6.35mm Phone jacks with momentary switch
+ Enclosure
+ USB-C cable

### Enclosure
I made simple box by 3D printer. My case use Markforged Onyx.
The STL file is on this repository.

### Wiring
![FootJov_diagram_210301](https://user-images.githubusercontent.com/7828838/109468602-2a73d880-7ab0-11eb-880e-66a3983c212b.jpg)
Connecting XIAO and jacks simply and gonna work.

## Software
This program requires a [MIDIUSB library](https://github.com/arduino-libraries/MIDIUSB).
Upload the sketch using the Arduino IDE.
