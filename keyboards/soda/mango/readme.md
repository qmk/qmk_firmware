# mango-17

A customizable 17  keyboard, support both HOTSWAP and SOLDER.

* Keyboard Maintainer: [gezhaoyou](https://github.com/gezhaoyou)
* Hardware Supported: [gezhaoyou](https://github.com/gezhaoyou)

Make example for this keyboard (after setting up your build environment):

    make soda/mango:default

Flashing example for this keyboard:

    make soda/mango:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button: [boot] first, then press button: [reset]  on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
