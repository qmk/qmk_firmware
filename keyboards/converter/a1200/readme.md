# Amiga 1200 Keyboard Converter

Modification of the Model-M 101 membrane adapter (converter/modelm101) to work with Amiga 1200 keyboard (and possibly Amiga 500/600 too). 
The adapter allows using the original Amiga keyboard as a USB input device, either with a desktop PC or a R-Pi/FPGA board hosted inside the Amiga case.

Available for two micros: AT90USB1286 (Teensy 2++ board), and ATmega32u4 (MiSS-1200 FPGA board).

A small PCB adapter is needed for connecting the keyboard membrane to the Teensy 2.0++ board. A very simple example of such a board is available here:
https://github.com/8bits4ever/A1200-Keyboard-Adapter

The MiSS-1200 FPGA board features a dedicated connector for the Amiga 1200 membrane keyboard.

Files have been modified in accordance to the Amiga keyboard layout and features. A second layer has been implemented (momentary toggle "Help" key) to access unexistent keys (like F11 and F12). This is a work in progress.


Pins of the Teensy board you should use by default:
```  
Columns: 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16  
Pins:    D2 D3 D4 D5 D6 D7 E0 E1 C0 C1 C2 C3 C4 C5 C6 C7 
--------------------------------------------------------  
Rows: 1  2  3  4  5  6  7  8  
Pins: F0 F1 F2 F3 F4 F5 F6 F7  
--------------------------------------------------------  
Status LEDs: CapsLock +5V   
Pins:        B6       5V    
```  

Pins assignment MiSS-1200 board (ATmega32u4):
```  
Columns: 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16  
Pins:    D0 D1 C7 D6 B7 B6 B5 B4 E6 D7 C6 D4 B2 D5 D3 D2 
--------------------------------------------------------  
Rows: 1  2  3  4  5  6  7  8  
Pins: F7 F6 F5 F4 F1 F0 B1 B3  
--------------------------------------------------------  
Status LEDs: CapsLock +5V   
Pins:        B0       5V    
```  

* Keyboard Maintainer: [8bits4ever](https://github.com/8bits4ever)
* Hardware Supported: Teensy 2.0++ board by PJRC, MiSS-1200 FPGA by 8bits4ever
* Hardware Availability: https://www.pjrc.com/store/teensypp.html

For first time flashing use the reset button to enter in bootloader mode. Once the board is flashed you can use "HELP"+"R" on the Amiga keyboard for reflashing.  

Make example for this keyboard (after setting up your build environment):

    make converter/a1200/teensy2pp:default

Or:

    make converter/a1200/miss1200:default


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
