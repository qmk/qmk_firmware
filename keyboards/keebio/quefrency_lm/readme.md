# Quefrency LM

A split 65XT staggered low-profile keyboard made and sold by Keebio. [More info at Keebio](https://keeb.io).

* Keyboard Maintainer: [Bakingpy/nooges](https://github.com/nooges)
* Hardware Availability: [Keebio](https://keeb.io/)

Make example for this keyboard (after setting up your build environment):

    make keebio/quefrency_lm/rev1:default

Example of flashing this keyboard:

    make keebio/quefrency_lm/rev1:default:flash

Handedness detection is already hardwired onto the PCB, so no need to deal with `EE_HANDS` or flashing .eep files.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in one of these ways:

* **Physical reset button**: Press and hold the button on the back of the PCB for at least 2 seconds and let go, or double-press the button
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

A build guide for this keyboard can be found here: [Keebio Build Guides](https://docs.keeb.io)
