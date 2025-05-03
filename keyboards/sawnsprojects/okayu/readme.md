# Okayu

![Okayu](https://i.imgur.com/pRnRHl8h.png)

A Wibu 60% keyboard PCB Design by inspire of Nekomata Okayu and can fit many keyboard case

* Keyboard Maintainer: [Mai The San](https://github.com/maithesan)
* Hardware Supported: Several 60% keyboard (RE60, Krush60, Unikorn, Tinyneko, Bakeneko60...)
* Hardware Availability: NuxrosKB, Salane Discord

Make example for this keyboard (after setting up your build environment):

    make sawnsprojects/okayu:default

Flashing example for this keyboard:

    make sawnsprojects/okayu:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
