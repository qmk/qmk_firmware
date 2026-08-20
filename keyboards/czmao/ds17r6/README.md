# CZMAO DS17R6

![CZMAO DS17R6](https://imgur.com/placeholder.jpg)

A 17-key number pad with per-key RGB, featuring a STM32F103 controller.

* Keyboard Maintainer: [micahyy](https://github.com/micahyy)
* Hardware Supported: CZMAO DS17R6 (STM32F103, direct matrix, WS2812 RGB)
* Hardware Availability: [CZMAO]()

Make example for this keyboard (after setting up your build environment):

    make czmao/ds17r6:default

Flashing example for this keyboard:

    make czmao/ds17r6:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the FN / Num Lock key) and plug in the keyboard
* **Physical reset button**: Briefly short the reset contacts on the back of the PCB
