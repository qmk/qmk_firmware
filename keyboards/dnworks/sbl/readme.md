# SBL

![SBL](https://i.imgur.com/HqRfr4bh.jpg)

An O ring mount 60%, akin to the otd 356mini

* Keyboard Maintainer: [Zeix](https://github.com/itsme-zeix)
* Hardware Supported: SBL Solder PCB rev1
* Hardware Availability: https://dnworks.co/products/sbl

Make example for this keyboard (after setting up your build environment):

    make dnworks/sbl:default

Flashing example for this keyboard:

    make dnworks/sbl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Short the 'USB_BOOT' button and plug in keyboard or briefly short the `RESET` and `GND` pads on the SWD header twice
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available