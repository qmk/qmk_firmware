# Evolv Revision Beta PCB QMK firmware

![evolvpic](https://i.imgur.com/IPhmnIL.jpeg)

This is the QMK firmware repository for the Evolv Revision Beta, a 75% with encoder keyboard designed by NathanAlphaMan in a partnership with Gondolindrim.

## How to compile

* Keyboard Maintainer: [gondolindrim](https://github.com/Gondolindrim)
* Hardware Supported: this firmware is for both EVO-S and EVO-H. Both use an STM32F401 microcontroller.
* Hardware Availability: as of november 2025, the Evolv Group Buy has already finished and there is no way to buy a unit anymore. The IC page for the keyboard can be found [here](https://geekhack.org/index.php?topic=104531).

Make example for this keyboard (after setting up your build environment):

    make evolvbeta:default

Flashing example for this keyboard:

    make evolvbeta:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (escape) and plug in the keyboard
* **Physical reset button**: while the PCB is powered, press the button on the back and hold for at least 5 seconds
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if available.

