# CU80

The CU80 is a TKL with two hotswap PCB variants. One fixed layout ISO and one fixed layout ANSI. This single firmware tree supports both, with the `default` being ISO.

To place the keyboard into bootloader mode in order to flash it, hold the ESC key while plugging the board in.

* Keyboard maintainer: [rys](https://github.com/rys)
* Hardware supported: CU80 v2
* Hardware availability: [CapsUnlocked](https://caps-unlocked.com/cu80-round-3/)

Make and flash examples for this keyboard (after setting up your build environment):

ISO layout:

    make capsunlocked/cu80:default:flash
    
ANSI layout:

    make capsunlocked/cu80:ansi:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
