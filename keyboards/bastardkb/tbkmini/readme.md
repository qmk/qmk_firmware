# TBK Mini

* Keyboard Maintainer: [Quentin Lebastard](https://github.com/bastardkb)
* Hardware Supported: BastardKB Blackpill or Pro Micro adapter & compatible development boards
* Hardware Availability: [GitHub](https://github.com/Bastardkb/TBK-Mini)

Make example for this keyboard (after setting up your build environment):

    make bastardkb/tbkmini/blackpill:default
    make bastardkb/tbkmini/promicro:default

Flashing example for this keyboard:

    make bastardkb/tbkmini/blackpill:default:flash
    make bastardkb/tbkmini/promicro:default:flash

Note if using the `promicro` version: If you are using an Elite-C compatible development board, see [here](../readme.md#handedness-pin-on-elite-c-holder) for setting handedness by pin.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the adapter PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
