# mini_elixivy

![mini_eLiXiVy](https://imgur.com/0lmOFcF.jpg)

A 65% ANSI/ISO keyboard PCB, with a rotary encoder option

* Keyboard Maintainer: [minibois](https://github.com/minibois)
* Hardware Supported: mini_eLiXiVy PCB, KBDFans' 65% plate and case, PCB mount stabilizers
* Hardware Availability: PCB: https://github.com/minibois, BOM: https://octopart.com/bom-tool/allQRgda

Make example for this keyboard (after setting up your build environment):

    make mini_elixivy:default

Flashing example for this keyboard:

    make mini_elixivy:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:
* **Physical reset button**: Briefly press the button on the back of the PCB (or short the reset/ground pads, should a tactile button not be installed)