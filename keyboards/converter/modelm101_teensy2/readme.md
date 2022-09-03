# modelm101_teensy2

![IBM Model M 101 ANSI/102 ISO](https://user-images.githubusercontent.com/46733695/161862805-c891735b-e2e8-418a-ad82-d71c00570eab.jpg)

This is based on the modelm101 keyboard by iw0rm3r. The difference is that Teensy 2.0 board (produced by PJRC) is used instead of the Teensy 2.0++ due to the availability issues. Only CapsLock LED is supported since Teensy 2.0 only has 25 digital I/0 pins.

Configuration is build for the Atmel ATmega32U4 controller, which you can easily use on the Teensy 2.0 board (produced by PJRC).

Pins of the Teensy board you should use by default:
```  
Columns: 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16  
Pins:    F0 F1 F4 F5 F6 F7 B6 B5 B4 D7 D6 B0 B1 B2 B3 B7  
--------------------------------------------------------  
Rows: 1  2  3  4  5  6  7  8  
Pins: D0 D1 D2 D3 C6 C7 D5 D4  
--------------------------------------------------------  
Status LEDs: CapsLock +5V ScrollLock NumLock  
Pins:        E6       5V  -         -  
```  

Keyboard Maintainer: [wangfuco](https://github.com/wangfuco)  
Hardware Supported: Teensy 2.0 board by PJRC  
Hardware Availability: https://www.pjrc.com/store/teensy.html 

Make example for this keyboard (after setting up your build environment):

    make converter/modelm101_teensy2:default:teensy

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
