# Geistmaschine Geist

![Geist](https://i.imgur.com/qpb6Rh9.png)

Geist is a high-end 65% keyboard, featuring a rotary encoder with a large knob.
* Keyboard Maintainer: [ebastler](https://github.com/ebastler)
* Hardware Supported: Geist Multi-Layout and Hot-Swap Rev1 (to access all multi-layout PCB options, use `default` keymap. Hotswap can work with either `default` or `ansi`)
* Hardware Availability: [geistmaschine.io](https://geistmaschine.io/)

Make example for this keyboard (after setting up your build environment):

    qmk compile geistmaschine/geist -km default

Flashing example for this keyboard:

    qmk flash geistmaschine/geist -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
