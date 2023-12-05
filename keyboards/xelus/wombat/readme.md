# Wombat

Left Hand Fullsized Keyboard designed by Jono.

* Keyboard Maintainer: [Xelus22](https://github.com/Xelus22)
* Hardware Supported: Wombat
* Hardware Availability: Custom keyboard group buys

Make example for this keyboard (after setting up your build environment):

    make xelus/wombat:default

Flashing example for this keyboard:

    make xelus/wombat:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the gold button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
