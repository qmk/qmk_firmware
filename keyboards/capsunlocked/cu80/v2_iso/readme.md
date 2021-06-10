# CU80 v2 ISO

The CU80 v2 ISO is the PCB for round 2 of the CU80 TKL keyboard, with fixed layout ISO and VIA support.

To place the keyboard into bootloader mode in order to flash it, hold the ESC key while plugging the board in, or use the reset button on the back of the PCB.

* Keyboard maintainer: [rys](https://github.com/rys) & [maz0r](https://github.com/maz0r)
* Hardware supported: [CU80 v2 ISO](https://imgur.com/yMZMt6j)
* Hardware availability: [CapsUnlocked](https://caps-unlocked.com/cu80-round-2/)

Make and flash example for this keyboard (after setting up your build environment):

    make capsunlocked/cu80/v2_iso:default:flash
    make capsunlocked/cu80/v2_iso/rgb:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
