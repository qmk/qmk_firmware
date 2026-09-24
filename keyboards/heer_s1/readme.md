# HEER S1

![HEER S1](https://i.imgur.com/rSxQHUi.png)

A 4x4 RP2040 macropad with two EC11 rotary encoders and a 128x64 SH1106 OLED.

* Keyboard Maintainer: [Heer Electronics](https://github.com/heerelectronics)
* Hardware Supported: HEER S1 PCB (RP2040 QFN-56)
* Hardware Availability: https://www.heerelectronics.com

Make example for this keyboard (after setting up your build environment):

    make heer_s1:default

Flashing example for this keyboard:

    make heer_s1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (bottom row of the SYSTEM layer)
