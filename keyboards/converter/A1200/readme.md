# A1200

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

Please note that some versions of Model M have LED connected with a ribbon cable, and not with separate wires.  

Keyboard Maintainer: [8bits4ever](https://github.com/8bits4ever)  
Hardware Supported: Teensy 2.0++ board by PJRC  
Hardware Availability: https://www.pjrc.com/store/teensypp.html 

Make example for this keyboard (after setting up your build environment):

    make converter/A1200:8bits4ever:teensy

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
