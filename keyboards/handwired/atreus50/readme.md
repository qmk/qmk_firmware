# Handwired Atreus50

This firmware is for a handwired Atreus50 using an Arduino Pro Micro.

Keyboard Maintainer: [The QMK Community](https://github.com/qmk)  
Hardware Supported: Arduino Pro Micro  

## Pinout

The following pins are used:
- Columns 1-13: D4, D7, E6, B4, B5, B6, B2, B3, B1, F7, F6, F5, F4
- Rows 1-4: D3, D2, D1, D0

## Compiling and loading the firmware

Make example for this keyboard (after setting up your build environment):

    make handwired/atreus50:default

To flash the firmware onto the microcontroller, run `make avrdude`, and press the reset button.

    make handwired/atreus50:default:avrdude

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
