# Eden

![Eden](https://i.imgur.com/5He99nkh.jpg)

A 60% mounted with tadpoles designed by The Flying Penguin.

* Keyboard Maintainer: [Zeix](https://github.com/itsme-zeix)
* Hardware Supported: Eden Solder PCB rev1
* Hardware Availability: mecha.store

Make example for this keyboard (after setting up your build environment):

    make zeix/eden:default

Flashing example for this keyboard:

    make zeix/eden:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the `RESET` button twice or short the `USB_BOOT` and `GND` pads and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available