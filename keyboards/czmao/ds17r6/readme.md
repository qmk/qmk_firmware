# CZMAO DS17R6

A 17-key number pad with hot-swappable switches, per-key RGB, and USB-C.

* Keyboard Maintainer: [micahyy](https://github.com/micahyy)
* Hardware Supported: CZMAO DS17R6 (STM32F103)
* Hardware Availability: [CZMAO Shop](https://czmao.com)

Make example for this keyboard (after setting up your build environment):

    make czmao/ds17r6:default

Flashing example for this keyboard:

    make czmao/ds17r6:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset**: Hold the BOOT button and briefly press the RESET button on the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`.
