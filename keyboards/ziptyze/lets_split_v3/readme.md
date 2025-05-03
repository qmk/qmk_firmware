# Let's Split v3

![Let's Split v3](https://i.imgur.com/ksZ64dKh.jpg)

Version 3 of the Let's Split keyboard, originally designed by Wootapatoot. This version features identical PCBs for both halves powered by an RP2040 controller. Each half features full hot swap capability as well as in-switch addressable LEDs and 39 1mm underglow LEDs.

* Keyboard Maintainer: [ziptyze](https://github.com/ziptyze)
* Hardware Supported: Let's Split v3 PCB
* Hardware Availability: [1upkeyboards](https://1upkeyboards.com/shop/keyboard-kits/diy-40-kits/lets-split-v3/#choose-your-kit)

Make example for this keyboard (after setting up your build environment):

    make ziptyze/lets_split_v3:default

Flashing example for this keyboard:

    make ziptyze/lets_split_v3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix, the top left key, and plug in the keyboard
* **BOOTSEL button**: Hold down the reset button on the PCB, and plug in the keyboard
