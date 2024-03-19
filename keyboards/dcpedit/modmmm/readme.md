# Mod Mmm

![Mod Mmm](https://i.imgur.com/oMP5RlJ.jpeg)

Replacement PCB for the IBM Model M keyboard.

* Keyboard Maintainer: [dcpedit](https://github.com/dcpedit)
* Hardware Supported: Blackpill STM32F411
* Hardware Availability: https://github.com/dcpedit/mod-mmm

Make example for this keyboard (after setting up your build environment):

    make dcpedit/mod-mmm:default

Flashing example for this keyboard:

    make dcpedit/mod-mmm:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the ESC key (top-left key) and plug in the keyboard
* **Physical reset button**: On the development board, while holding down the BOOT button, press and release the RESET button
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available