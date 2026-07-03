# Kobold

![Kobold](https://i.imgur.com/R8nDodO.jpg)

4x4 macropad running QMK, in the same form factor as a bm16s. Non-standard Choc key spacing.

North-facing RGB, SPI NOR Flash, voltage and current measurement, direct pin matrix, reset to bootloader by holding top 4 keys.

* Keyboard Maintainer: [tzarc](https://github.com/tzarc)
* Hardware Supported: Kobold, r1
* Hardware Availability: [KiCad files](https://github.com/tzarc/keyboards/tree/main/Kobold)

Make example for this keyboard (after setting up your build environment):

    make tzarc/kobold/r1:default

Flashing example for this keyboard:

    make tzarc/kobold/r1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset button**: Simultaneously press the top four keys, or press the physical button on the back marked 'D'.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
