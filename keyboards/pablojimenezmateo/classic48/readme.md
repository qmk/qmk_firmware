# pablojimenezmateo/classic48

![pablojimenezmateo/classic48](https://i.imgur.com/czFWWhX.jpeg)

A custom split keyboard with 48 keys and addressable LEDs.

* Keyboard Maintainer: [Pablo Jimenez Mateo](https://github.com/pablojimenezmateo)
* Hardware Supported: RP2040 Pro Micro
* Hardware Availability: https://github.com/pablojimenezmateo/classic48

Make example for this keyboard (after setting up your build environment):

    make pablojimenezmateo/classic48:default

Flashing example for this keyboard:

    qmk flash -kb pablojimenezmateo/classic48 -km default -bl uf2-split-left
    qmk flash -kb pablojimenezmateo/classic48 -km default -bl uf2-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
