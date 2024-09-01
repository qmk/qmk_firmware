# DEPENDING ON WHERE OR WHEN YOU PURCHASED THIS KEYBOARD, YOU MAY HAVE A DIFFERENT MCU AND BOOTLOADER THAN WHAT THIS FIRMWARE IS LOOKING FOR
This code was made for devices with the STM32F072 chip. Some are now being sold with the APM32F072 chip. The VID and PID on these variants are the same. There are 2 ways you find out which one you have. 1: you attempt to flash and get an error saying "device mismatch." 2: you open up the board and read "APM32F072 GEEHY" on the chip. If you have the Geehy chip, you must find and download Geehy Programmer and the APM DFU drivers. After that, the steps for flashing are the same. Put the keyboard into DFU mode, open Geehy Programmer, select your bin file, and click the "Update" button.

# MF-34

A customizable 34  keyboard, support both HOTSWAP and SOLDER.

* Keyboard Maintainer: [gezhaoyou](https://github.com/gezhaoyou)
* Hardware Supported: [gezhaoyou](https://github.com/gezhaoyou)

Make example for this keyboard (after setting up your build environment):

    make magic_force/mf34:default

Flashing example for this keyboard:

    make magic_force/mf34:default:flash

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button: [boot] first, then press button: [reset]  on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
