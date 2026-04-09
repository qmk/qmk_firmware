# RALT65

A drop-in replacement PCB for the Drop Alt 65% keyboard, powered by an STM32F072 MCU.

* Keyboard Maintainer: [Automata02](https://github.com/Automata02/)
* Hardware Supported: RALT65 PCB

Make example for this keyboard (after setting up your build environment):

    make automata02/ralt65:default

Flashing example for this keyboard:

    make automata02/ralt65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

* **DFU mode**: Bridge the BOOT0 solder jumper (SW0) and reset the board to enter STM32 DFU mode.
