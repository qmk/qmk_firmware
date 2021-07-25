# A1200

Pins of the Teensy board you should use by default:
```  
Columns: 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16  
Pins:    C7 C6 C5 C4 C3 C2 C1 C0 E1 E0 D7 D6 D5 D4 D3 D2  
--------------------------------------------------------  
Rows: 1  2  3  4  5  6  7  8  
Pins: F7 F6 F5 F4 F3 F2 F1 F0  
--------------------------------------------------------  
Status LEDs: CapsLock +5V   
Pins:        B6       5V    
```  

Please note that some versions of Model M have LED connected with a ribbon cable, and not with separate wires.  

Keyboard Maintainer: [iw0rm3r](https://github.com/iw0rm3r)  
Hardware Supported: Teensy 2.0++ board by PJRC  
Hardware Availability: https://www.pjrc.com/store/teensypp.html 

Make example for this keyboard (after setting up your build environment):

    make converter/modelm101:default:teensy

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
