# nt210

![nt120 PCB](https://i.imgur.com/DZAfoOlh.jpg)

A custom PCB for the Leopold FC210TP.

* Keyboard Maintainer: [Evelien Dekkers](https://github.com/evyd13)
* Hardware Supported: nt-120 PCB
* Hardware Availability: [Open source on GitHub](https://github.com/evyd13/nt-series/tree/main/nt-210)

Make example for this keyboard (after setting up your build environment):

    make evyd13/nt210:default

Flashing example for this keyboard:

    make evyd13/nt210:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
