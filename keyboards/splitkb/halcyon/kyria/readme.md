# Halcyon Kyria

![splitkb/halcyon/kyria](WIP)

* Keyboard Maintainer: [splitkb.com](https://github.com/splitkb.com)
* Hardware Availability: [splitkb.com](https://splitkb.com).

Make example for this keyboard (after setting up your build environment):

    make splitkb/halcyon/kyria:default

The keyboard can be flashed by copying the resulting `.uf2` file onto the `RPI-RP2` flash drive.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Reset button**: Double-tap the reset button at the top of the controller, right above the USB-C port.
* **Bootloader reset**: Hold down the "Boot" button and plug in the keyboard.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.