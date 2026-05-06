# gok TypeK QMK Firmware Folder

![TK](https://i.imgur.com/0ZEbEZt.jpg)

## Introduction

This is the QMK Firmware repository for the Type K, the tented ergo by Gok. The TypeK went through GB on August, 2023. It is supported by a proprietary PCB ecosystem.

## How to flash

### Enter bootloader

The DFU state in the bootloader can be accessed in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key, escape in the default keymap) and plug in the keyboard;
* **Physical reset button**: press the button on the front of the PCB, next to caps lock, for at least five seconds;
* **Keycode in layout**: Press the key mapped to `RESET`; in the default layout, that is top left key ('escape') in layer 1.

### How to compile and flash


After setting up your build environment, you can compile the Iron 165R2 default keymap by using one of the options below.

    make typek:default

And use dfu-util in the command line or through a GUI like QMK toolbox to upload the firmware to the PCB. To directly flash the PCB after it is put into a DFU state, use:

    make typek:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
