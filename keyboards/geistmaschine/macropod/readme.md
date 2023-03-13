# Geistmaschine Macropod

![macropod](https://i.imgur.com/lAsCslA.png)

Macropod is a modular macropad, designed around a central big encoder with a magnetic connector for modularity. The default module uses three MX style keys.
* Keyboard Maintainer: [ebastler](https://github.com/ebastler)
* Hardware Supported: Macropod rev1
* Hardware Availability: [geistmaschine.io](https://geistmaschine.io/)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb geistmaschine/macropod -km default

Flashing example for this keyboard:

    qmk flash -kb geistmaschine/macropod -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the knob on the main module) and plug in the keyboard
* **Physical reset button**: Briefly tap the button marked "RST" on the back of the main module PCB
