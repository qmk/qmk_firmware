# TAN67 PCB

A 65% PCB, which controlled by an STM32F072 chipset.

* Keyboard Maintainer: [Pangorin](https://github.com/pangorin)
* Hardware Supported: STM32F072

Make example for this keyboard (after setting up your build environment):

    make pangorin/tan67:default

Flashing example for this keyboard:

    make pangorin/tan67:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
