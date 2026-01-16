# Chiri CE (Compact Edition)

A split ergo 3x6 keyboard with 4 thumb keys made and sold by Keebio. Outer columns can be broken off to convert it to 3x5 layout. [More info at Keebio](https://keeb.io).

* Keyboard Maintainer: [Bakingpy/nooges](https://github.com/nooges)
* Hardware Supported: Chiri CE PCBs w/RP2040 microcontroller
* Hardware Availability: [Keebio](https://keeb.io)

Make example for this keyboard (after setting up your build environment):

    make keebio/chiri_ce/rev1:default

Example of flashing this keyboard:

    make keebio/chiri_ce/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at the top left (for left half) or top right (for right half) and plug in the keyboard
* **Physical reset button**: Press and hold the button on the back of the PCB for at least 1 second and let go
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
