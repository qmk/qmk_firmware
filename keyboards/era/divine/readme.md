# DIVINE

DIVINE Keyboard

* Keyboard Maintainer: [ERA](https://github.com/eerraa)
* Hardware Supported: RP2040
* Hardware Availability: [ERA](https://github.com/eerraa)

Make example for this keyboard (after setting up your build environment):

    make era/divine:default

Flashing example for this keyboard:

    make era/divine:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at ESC(0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Short the reset hole of the PCB twice within 1 second.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available