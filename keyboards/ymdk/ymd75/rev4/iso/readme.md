# YMD75 V4

75% per key RGB hotswap PCB with North Facing LED.

* Keyboard Maintainer: [zvecr](https://github.com/zvecr)
* Hardware Availability: <https://ymdkey.com/products/ymd-75-84-v4-rgb-hotswap-pcb-plate-north-facing-via-vial-fully-programmable>

Make example for this keyboard (after setting up your build environment):

    make ymdk/ymd75/rev4/iso:default

Flashing example for this keyboard:

    make ymdk/ymd75/rev4/iso:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Quickly double tap the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
