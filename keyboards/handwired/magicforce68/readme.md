# Magicforce 68 Handwired

This firmware is for a Magicforce 68 that's had its PCB removed and is handwired with an Arduino Micro. NOTE: The Arduino Micro is different than the Arduino *Pro* Micro.

Keyboard Maintainer: [The QMK Community](https://github.com/qmk)  
Hardware Supported: magicforce68, Arduino Micro  

## Wiring Layout

![Wiring Layout](http://i.imgur.com/NmTCv5u.png)

## Pinout

The following pins are used:
- Columns 1-15: B2, B0, D3, D2, D1, D0, D4, C6, D7, E6, B4, B5, B6, B7, D6
- Rows 1-5: F0, F1, F4, F5, F6

Make example for this keyboard (after setting up your build environment):

    make handwired/magicforce68:default

To flash the firmware onto the microcontroller, run `make handwired/magicforce68:default:avrdude`, and press the reset button.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
