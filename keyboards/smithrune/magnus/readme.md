# Smith and Rune Magnus

![magnus](https://imgur.com/bemM7ZZh.jpg)

## Introduction

This is the QMK Firmware repository for the Magnus, a keyboard designed by [Smith and Rune](https://smithrune.com/) and PCBs designed by [Gondolindrim](http://github.com/Gondolindrim), who is also the firwmare maintainer.

The Magnus keyboard has two PCB versions: a solderable version (m75s) and a hotswap version (m75h). While M75S has support for a myriad of alternative layouts, including a 7U bottom row and ISO, M75H only supports full and split backspace alternatives. Also, while M75S supports in-switch single-color LEDs and RGB LEDs for underglow light, M75H only supports RGB underglow.

As of July 2023, the Magnus groubuy is already finished.

## How to flash

### Enter bootloader

The DFU state in the bootloader can be accessed in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key, escape in the default keymap) and plug in the keyboard;
* **Physical reset button**: press the button on the front of the PCB, next to caps lock, for at least five seconds;
* **Keycode in layout**: Press the key mapped to `QK_BOOT`; in the default layout, that is top left key ('escape') in layer 1.

### How to compile and flash

After checking what PCB you own and setting up your build environment, you can compile the Magnus default keymap by using one of the options below.

    make smithrune/magnus/m75s:default
    make smithrune/magnus/m75h:default

And use `dfu-util` in the command line or through a GUI like QMK toolbox to upload the firmware to the PCB. To directly flash the PCB after it is put into a DFU state, use:

    make smithrune/magnus/m75s:default:flash
    make smithrune/magnus/m75h:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
