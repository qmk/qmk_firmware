# KeyNet

![keynet](https://i.imgur.com/SHSUUh8.jpeg)

![keynet](https://i.imgur.com/XOig87S.jpeg)

Keynet is a split, ortholinear (column-staggered) keyboard powered by an Atmega32u4 microcontroller. It uses the Caterina bootloader and features support for rotary encoders, mouse keys, and NKRO. The firmware is configured for a split matrix layout with a custom hand-swap configuration.

* Keyboard Maintainer: [Arthur Frangyan](https://github.com/ArthurFrangyan)
* Addtional Information: [Github](https://github.com/ArthurFrangyan/KeyNet)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb keynet/rev1 -km default

Flashing example for this keyboard for left and right sides:

    qmk flash -kb keynet/rev1 -km default -bl avrdude-split-left
    qmk flash -kb keynet/rev1 -km default -bl avrdude-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOT`, Menu + (0,0) key
* **Physical reset button**: A small hole on the front of the keyboard provides access to the reset (RST) contact. Touching it with a conductive object such as a needle or SIM ejector tool while holding the object is enough to trigger a reset.
