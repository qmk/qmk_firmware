# KB16-01

![KB16-01](https://i.imgur.com/lpq47ELh.png)

A macropad that have 16-key keyboard made by DOIO, which controlled by an Atmega32u4 chipset. The keyboard features per-key RGB, 3 encoder and an OLED screen for displaying useful information.

* Keyboard Maintainer: [HorrorTroll](https://github.com/HorrorTroll)
* Hardware Supported: Atmega32u4

Make example for this keyboard (after setting up your build environment):

    make doio/kb16/rev1:default

Flashing example for this keyboard:

    make doio/kb16/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (1! key) and plug in the keyboard
* **Physical reset button**: Short press the button under Spacebar keycap to enter the Bootloader and flash the firmware
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
