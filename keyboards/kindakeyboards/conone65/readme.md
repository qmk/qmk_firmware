# Conone 65

![Conone65 PCB](https://i.imgur.com/50dKAqh.jpeg)

The Conone 65 is a custom keyboard designed and machined in Belgium.

* Keyboard Maintainer: [Evyd13](https://github.com/evyd13), [Matt Chan](https://github.com/mattchan)
* Hardware Supported: Conone 65 PCB, ATMega32u4
* Hardware Availability: https://www.kindakeyboards.be/conone65

Make example for this keyboard (after setting up your build environment):

    make kindakeyboards/conone65:default

Flashing example for this keyboard:

    make kindakeyboards/conone65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available