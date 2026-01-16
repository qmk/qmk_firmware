# Iron180 V2 PCBs QMK firmware folder

## Introduction

This is the QMK Firmware repository for the Iron180 PCB, a keyboard designed by [Smith and Rune](https://smithrune.com/) and PCB designed by [Gondolindrim](http://github.com/Gondolindrim).

The Iron180 PCB PCB had two versions. The first version used an STM32F072 microcontroller, and was available only in solderable version; it also supports ALPS switches, in-switch single-color LEDs and a multi-layout design for default or 7U bottom row, ISO layout, split backspace and right shift.

The second version used an STM32F401 microcontroller and was available in hotswap and solderable version. The solderable version removes in-switch LED support and ALPS support, but keeps all layout compatibilities of the first version. The hotswap incarnation removes ISO layout support.

As of November 2020, the only way to obtain an Iron180 was through the [Group Buy](https://geekhack.org/index.php?topic=109513) which is already over and all spots were filled. There was a sale for the V2 PCBs in october, 2023.

## How to compile

After setting up your build environment, you can compile the Iron180 default keymap by using:

    make smithrune/iron180v2/<version>/default

Where `<version>` can be `v2s` or `v2h`.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## How to enter into bootloader DFU
Enter the bootloader DFU mode in 3 ways:
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape in the default keymap) and plug in the keyboard
* **Physical reset button**: press and hold the reset button on the back of the PCB for five seconds
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (Escape key on layer 1 in the default keymap)
