# Djinn

![Djinn](https://i.imgur.com/ArSjkv8.jpg)

The Djinn is a 64-key split keyboard -- dual 4x7 with a 4-key thumb cluster and encoders. It also has a 5-way tactile switch under the thumb. Oh, and two displays.

Keyboard Maintainer: [tzarc](https://github.com/tzarc)  
Hardware Supported: Djinn: rev1, rev2  
Hardware Availability: [Open-source](https://github.com/tzarc/djinn)

Make example for this keyboard (after setting up your build environment):

    make tzarc/djinn/rev2:default

Flashing example for this keyboard:

    make tzarc/djinn/rev2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top-left key and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
