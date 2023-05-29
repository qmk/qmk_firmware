# frobiac/blackbowl

![frobiac/blackbowl](https://i.imgur.com/nehpp3fh.jpeg)

Custom 3D-printed and handwired 36-key split-keyboard with trackpoint developed in 2016.

* Keyboard Maintainer: [frobiac](https://github.com/frobiac)
* Hardware Supported: Teensy-2.0, IBM Trackpoint, one MCP23018 per side, one RGB-LED
* Development History: [deskthority.net](https://deskthority.net/viewtopic.php?p=344785#p344785)
* Layout [Alpha KLE](http://www.keyboard-layout-editor.com/#/gists/6a6ec84d59fc346effbe894af159eabd) (same as BlackBowl)
* [Original Firmware](https://github.com/frobiac/adnw)

Make example for this keyboard (after setting up your build environment):

    make frobiac/blackbowl

Flashing example for this keyboard:

    make frobiac/blackbowl:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


The I2C code is based on the code from 'handwired/dactyl',
but reduced to ROW2COL and EXPANDER_COL_REGISTER=GPIOA define choices.
Adjustments were made for the two I2C addresses, one per side.


## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the Teensy by inserting a small pin in the small hole in the switch plate
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available


