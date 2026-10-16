# Forever65 Revision 2 PCB QMK firmware

![foreverpic](https://imgur.com/pUlXRTL.jpg)

This is the QMK firmware repository for the Forever 65 PCB, revision 2. The Forever 65 was a 65% with blocker keyboard designed by DriftMechanics and PheonixStarr. The revision 2 PCB was designed by Gondolindrim.

## How to compile

* Keyboard Maintainer: [gondolindrim](https://github.com/Gondolindrim)
* Hardware Supported: the R2 PCB uses a STM32F401 microcontroller.
* Hardware Availability: as of november 2025, the Forever65 Group Buy has already finished.

Make example for this keyboard (after setting up your build environment):

    make forever65r2:default

Flashing example for this keyboard:

    make forever65r2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (escape) and plug in the keyboard
* **Physical reset button**: while the PCB is powered, press the button on the back and hold for at least 5 seconds
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if available.

