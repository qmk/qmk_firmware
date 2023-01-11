# MJ6XY 60% Mechanical Keyboard PCB

![MJ6XY rev3](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/melgeek/mj6xy/7084b1fb2e7228c664ee0e481544bd24.webp)

A customizable 60% Mechanical Keyboard PCB which supports multiple layouts.

* Keyboard Maintainer: QMK Community
* Hardware Supported: MJ6XY 60% Mechanical Keyboard PCB
* Hardware Availability: [MelGeek](https://www.melgeek.com/products/melgeek-mj6xy-60-mechanical-keyboard-pcb-melgeek-com)

Make example for this keyboard (after setting up your build environment):

    make melgeek/mj6xy/rev3:default

Flashing example for this keyboard:

    make melgeek/mj6xy/rev3:default:flash

## Bootloader

To reset the board into bootloader mode, do one of the following:

* **Bootmagic reset**: Hold the key at the top left of the keyboard while connecting the USB cable (also erases persistent settings)
Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Tap the Reset switch mounted on the bottom side of the PCB (near the QWERTY `S` and `D` keys)
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
