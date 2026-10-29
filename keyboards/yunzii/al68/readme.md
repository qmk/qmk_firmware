# MK AL68


![AL68](https://i.imgur.com/mhiYDh3.png)

A customizable 68keys keyboard.

* Keyboard Maintainer: [Jeff](https://github.com/yunziikeyboard)
* Hardware Supported: [yunzii](https://www.yunzii.com)
* Hardware Availability: [yunzii](https://www.yunzii.com)

Make example for this keyboard (after setting up your build environment):

    make yunzii/al68:default

Flashing example for this keyboard:

    make yunzii/al68:default:flash

See the build environment setup and the make instructions for more information. Brand new to QMK? Start with our Complete Newbs Guide.

## Bootloader ESC the bootloader in 3 ways:
* **Bootmagic reset: Hold down Enter in the keyboard then replug
* **Physical reset button: Briefly press the button on the back of the PCB
* **Keycode in layout: Press the key mapped to QK_BOOT