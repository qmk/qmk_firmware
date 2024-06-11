# Gas75

A 75% exploded keyboard made by ML, which controlled by an Atmega32u4 chipset.

* Keyboard Maintainer: ML
* Hardware Supported: Atmega32u4
* Hardware Availability: https://item.taobao.com/item.htm?ft=t&id=652142230132

Make example for this keyboard (after setting up your build environment):

    make ml/gas75:default

Flashing example for this keyboard:

    make ml/gas75:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
