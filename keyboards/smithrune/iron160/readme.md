# Iron 160 QMK folder

![Iron160](https://i.imgur.com/8B2l2pnh.jpg)

## Introduction

This is the QMK Firmware repository for the Iron160 PCB, a keyboard designed by [Smith and Rune](https://smithrune.com/) and PCB designed by [Gondolindrim](http://github.com/Gondolindrim), who is also the firwmare maintainer.

There are two variants of the PCB: a solderable (I160-S) and a hotswap (I160-H) PCB. Both support a myriad of alternative layouts, as well as RGB LEDs for underglow light.

## How to flash

### Enter bootloader

The DFU state in the bootloader can be accessed in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key, escape in the default keymap) and plug in the keyboard;
* **Physical reset button**: press the button on the front of the PCB, next to caps lock, for at least five seconds;
* **Keycode in layout**: Press the key mapped to `QK_BOOT`; in the default layout, that is top left key ('escape') in layer 1.

### How to compile and flash

After checking what PCB you own and setting up your build environment, you can compile the Iron 165R2 default keymap by using one of the options below.

    make smithrune/iron160/iron160_s:default
    make smithrune/iron160/iron160_h:default

And use dfu-util in the command line or through a GUI like QMK toolbox to upload the firmware to the PCB. To directly flash the PCB after it is put into a DFU state, use:


    make smithrune/iron160/iron160_s:default:flash
    make smithrune/iron160/iron160_h:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
