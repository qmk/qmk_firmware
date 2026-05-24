# alatus

![alatus](https://i.imgur.com/kVrFpSJ.jpeg)

A low profile 38 key split keyboard featuring rotary encoder and trackpoint support.

* Keyboard Maintainer: [DoomishGuy](https://codeberg.org/DoomishGuy)
* Hardware Supported: RP2040 Pro Micro and compatible
* Hardware Availability: [DoomishGuy/alatus](https://codeberg.org/DoomishGuy/alatus)

Make example for this keyboard (after setting up your build environment):

    make alatus:default

Flashing example for this keyboard:

    make alatus:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the top left/right key (for the left/right splits respectively) and plug in the keyboard.
* **Physical reset button**: Press the reset button below the microcontroller twice in quick succession.
