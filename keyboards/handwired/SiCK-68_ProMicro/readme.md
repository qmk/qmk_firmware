# SiCK-68 Pro Micro

This firmware is for a SiCK-68 handwired build that uses a Pro Micro instead of a Teensy

Keyboard Maintainer: [The QMK Community](https://github.com/qmk)  
Hardware Supported: Pro Micro  

## Wiring Layout

![Wiring Layout](http://i.imgur.com/NmTCv5u.png)

## Pinout

The following pins are used:
- Columns 1-15: D3, D2, D1, D0, D4, C6, D7, E6, B4, B5, B0, D5, F4, F5, F6
- Rows 1-5: F7, B1, B3, B2, B5
- Note this does use the pins associated with the Tx, Rx LED's


Make example for this keyboard (after setting up your build environment):

    make handwired/SiCK-68_ProMicro:default

To flash the firmware onto the microcontroller, run `make handwired/SiCK-68_ProMicro:default:avrdude`, and press the reset button.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
