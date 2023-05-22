# Quokka

![Quokka](https://i.imgur.com/zqbb56ch.jpeg)

A split ortholinear keyboard designed for the small handed.

* Keyboard Maintainer: [dlford](https://github.com/dlford/), [dlford.io](https://www.dlford.io)
* Hardware Supported: Quokka PCB, Adafruit KB2040
* Hardware Availability: [PCB, Case Data, and Build Guide](https://github.com/dlford/quokka)

Make example for this keyboard (after setting up your build environment):

    make quokka:default

Flashing example for this keyboard:

    make quokka:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Quickly double press and release the reset button on the the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
