# Janus

![Janus](https://i.imgur.com/7Lzhafe.jpg)

A 34-key split ortholinear keyboard, powered by two Seeed XIAO RP2040.

* Keyboard Maintainer: [Steven Karrmann](https://github.com/skarrmann)
* Hardware Supported: Janus PCBs, Seeed XIAO RP2040
* Hardware Availability: [Janus GitHub repository](https://github.com/skarrmann/janus)

Make example for this keyboard (after setting up your build environment):

    make janus:default

Flashing example for this keyboard:

    make janus:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Double tap the reset button on the top of the microcontroller
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
