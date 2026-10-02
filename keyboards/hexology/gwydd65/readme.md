# Gwydd65

65% keyboard by Hexology.

* Keyboard Maintainer: [Maelkk](https://github.com/Aeonstrife)
* Hardware Supported: Hexology Gwydd65 Solder PCB, Hexology Gwydd65 Hotswap PCB, RP2040
* Hardware Availability: [Hexology.design Gwydd65 Keyboard](https://www.hexology.design/products/gwydd65-keyboard-kit)

Make example for this keyboard (after setting up your build environment):

    make hexology/gwydd65:default

Flashing example for this keyboard:

    make hexology/gwydd65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset button**: Press and hold the reset button and plug the board in
* **Keycode in layout**: Press the key mapped to `QK_BOOT` on the function layer
