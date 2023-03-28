# Basic I/O Instruments Kamilia

Kamilia is a HHKB-like MUTE-MOUNT custom keyboard, come with a USB/BLE duo-mode PCB which is fully compatible with KARA from RAMA WORKS.

![Baisc I/O Instrument Kamilia](https://i.imgur.com/HR1tQHIh.jpg)

* Keyboard Maintainer: [Basic I/O Instruments (Scott Wei)](https://github.com/scottywei)
* Hardware Supported: [Basic I/O Instruments (Scott Wei)](https://github.com/scottywei)
* Hardware Availability: https://www.zfrontier.com/app/flow/ElYvxoxxVgx0

Make example for this keyboard (after setting up your build environment):

    make bioi/kamilia:default

Flashing example for this keyboard:

    make bioi/kamilia:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
