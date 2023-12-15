# pisces

![pisces](https://i.imgur.com/rzIhYLZ.png)

(Less than) 40% Ortholinear split keyboard

* Keyboard Maintainer: [knaruo](https://github.com/knaruo)
* Hardware Supported: pisces PCB, ATmega32U2
* Hardware Availability: [PCB and Plate](https://github.com/knaruo/pisces)

Getting the board into bootloader mode:

To be able to flash firmware onto this board, you'll need to bring the micro controller into bootloader mode. Press the reset button (RSTSW1) on the top side of the PCB to enable the bootloader mode.


Make example for this keyboard (after setting up your build environment):

    make pisces:default

Flashing example for this keyboard:

    make pisces:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
