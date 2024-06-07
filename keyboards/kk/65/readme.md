# KK65

![KK65](https://i.imgur.com/vGBCw5Qh.jpg)

The KK65 is a hot-swappable 68-key keyboard designed and manufactured in the USA.

* Keyboard Maintainer: [Kory Hicks](https://github.com/apricity-spam)
* Hardware Supported: KK65 PCB, ATMega32u4
* Hardware Availability: Coming soon!

Make example for this keyboard (after setting up your build environment):

    make kk/65:default

Flashing example for this keyboard:

    make kk/65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
