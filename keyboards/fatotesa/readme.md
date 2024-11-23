# fatotesa

![fatotesa](https://i.imgur.com/LbxQcU2.png)

This is the QMK firmware for the [fat-o-tesa](https://github.com/stefangluszek/fat-o-tesa) keyboard.

* Keyboard Maintainer: [Stefan Gluszek](https://github.com/stefangluszek)

Make example for this keyboard (after setting up your build environment):

    make fatotesa:default

Flashing example for this keyboard:

    make fatotesa:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (4,1) in the matrix and plug in the keyboard - this is somewhat unusual choice but our split halves are not symmetrical and we can't use (0,0) but instead a key that maps to the same matrix position regardless of which part is being connected to the computer and flashed.
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
