# modelm101

![IBM Model M 101 ANSI/102 ISO](https://i.imgur.com/DAE3W7g.jpg)

This is a configuration for the QMK firmware for reversible conversion of IBM's Model M keyboards (common 101-key ANSI and 102-key ISO models) from stock, power-hungry controller, to a modern one, running the USB bus.  
Configuration is build for the Atmel AT90USB1286 controller, which you can easily use on the Teensy 2.0++ board (produced by PJRC).  
Project is heavely based on 2 other projects:
1. Teensy 2.0++-based custom Model M controller running TMK firmware ('modelm" by [lmorchard](https://blog.lmorchard.com/2016/02/21/modelm-controller/)); - had a few issues.
2. Teensy 2.0++-based custom Model M 122-key controller running QMK firmware ("ibm122m" by [lukexorz](https://github.com/lukexorz)); - had wrong layout for 101/102-key boards and no status LED support.

For this conversion you will need:  
1. Teensy 2.0++ dev board itself (can be used a different dev board, but it will require some changes in configuration);
2. Ribbon connectors to connect the membrane to a dev board. Depending on your Model M variation, you will need 1 Trio-mate 16pin connector (6-520315-6 or 6-520415-6) and 1 Trio-mate 8pin connector (5-120628-8 or 5-520314-8), or 2 Trio-mate 16pin connectors;
3. Full-sized breadboard (without power rails; half-size should do, but full-sized one looks more native) or a PCB to wire everything up;
4. A bunch of jumper wires;
5. mini-USB male cable with any USB socket you want to use to connect Teensy inside the keyboard to your PC (I use short mini-USB male to mini-USB female cable);
6. (optional) Resistors for connecting status LEDs if your LED PCB doesn't have any;
7. (optional) Double-sided tape to fix USB socket on or inside the keyboard case.

Pins of the Teensy board you should use by default:
```  
Columns: 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16  
Pins:    C7 C6 C5 C4 C3 C2 C1 C0 E1 E0 D7 D6 D5 D4 D3 D2  
--------------------------------------------------------  
Rows: 1  2  3  4  5  6  7  8  
Pins: F7 F6 F5 F4 F3 F2 F1 F0  
--------------------------------------------------------  
Status LEDs: CapsLock +5V ScrollLock NumLock  
Pins:        B6       5V  B5         B4  
```  

Please note that some versions of Model M have LED connected with a ribbon cable, and not with separate wires.  

Keyboard Maintainer: [iw0rm3r](https://github.com/iw0rm3r)  
Hardware Supported: Teensy 2.0++ board by PJRC  
Hardware Availability: https://www.pjrc.com/store/teensypp.html 

Make example for this keyboard (after setting up your build environment):

    make converter/modelm101:default:teensy

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
