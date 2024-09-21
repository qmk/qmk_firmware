# shk9

![shk9](https://i.imgur.com/FluRgiHl.jpg)

The SHK9 is a tiny 3x3 macropad! Fully configurable with via.

* Keyboard Maintainer: [Sam Hudson](https://github.com/samsamm777)
* Hardware Supported: SHK9 PCB (ATmega32u4)
* Hardware Availability: http://superhuman.website

Make example for this keyboard (after setting up your build environment):

    make shk9:default

Flashing example for this keyboard:

    make shk9:default:flash

## Bootloader Mode

To reset the board into bootloader mode, remove the pcb from the case buy removing keycaps, and unscrewing the 3 screws. Then (while plugged in) press the switch on the underside of the PCB for a few seconds. The board is now in bootloader mode.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).