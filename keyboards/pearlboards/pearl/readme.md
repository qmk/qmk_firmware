# Pearl

![Pearl](https://i.imgur.com/xdEtT7uh.jpg)

Pearl is a future-proof premium 40%. This is the second round of it, reworked for 2021. This firmware is for the latest QMK PCB's.

* Keyboard Maintainer: Koobaczech
* Hardware Supported: Pearl
* Availability: https://pearlboards.net/products/pearl-40

Make example for this keyboard (after setting up your build environment):

    make pearlboards/pearl:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the front left of the PCB labeled `RESET`
* **Keycode in layout**: Press the key mapped to `QK_BOOT` in conjunction with the key mapped to `MO(1))` 
