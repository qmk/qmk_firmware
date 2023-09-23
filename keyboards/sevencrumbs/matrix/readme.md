# Matrix

![Matrix with illuminated buttons surrounded by parts from a disassembled Matrix](https://seven-crumbs-static.pages.dev/matrix-scene.png)

A rugged four-button macro pad with a per-key customisable RGB backlight.

* Keyboard Maintainer: [Zoid Technology](https://github.com/ZoidTechnology)
* Hardware Availability: Available Q4 2023

Make example for this keyboard (after setting up your build environment):

    make sevencrumbs/matrix:default

Flashing example for this keyboard:

    make sevencrumbs/matrix:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Press and hold all four buttons while connecting the USB cable.
* **Keycode in layout**: Press the button mapped to `QK_BOOT` if it is available.
* **Physical reset**: In the case of firmware corruption, the other methods of entering the bootloader may not work. Open the enclosure and bridge the pads labelled "Boot" with a conductive object while connecting the USB cable.
