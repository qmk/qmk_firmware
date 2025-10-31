# ibm122m

![IBM Model M 122 key](https://i.imgur.com/Oo3Ozqz.jpg)

This is a keymap for the IBM Model M 122 key terminal keyboard running on a Teensy++ 2.0
I wired it to weird pins on mine (mainly to accomodate two speakers), so make sure to update the pin arrays.

* Keyboard Maintainer: [Luke Stanley](https://github.com/lukexorz)
* Hardware Supported: Teensy++ 2.0
* Hardware Availability: https://www.pjrc.com/store/teensypp.html

Pins of the Teensy board you should use by default:
```  
Columns: 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20  
Pins:    E6 B7 D0 D1 D2 D3 D4 D5 D6 D7 E0 E1 C0 C1 C2 C3 C4 C5 C7 F1  
--------------------------------------------------------  
Rows: 1  2  3  4  5  6  7  8  
Pins: F0 B5 B4 B3 B2 B1 B0 E7  
--------------------------------------------------------  
Status LEDs: CapsLock +5V ScrollLock NumLock  
Pins:        N/A      5V  N/A        N/A
--------------------------------------------------------
Speaker: 1+ 1-  2+ 2-
Pins:    C6 GND B6 GND
```

Make example for this keyboard (after setting up your build environment):

    make ibm/model_m_122/ibm122m:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
