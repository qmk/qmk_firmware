# QK65 - Hotswap R2 PCB

![White QK65 R2](https://i.imgur.com/te8LNCf.jpeg)

A 65% made by Qwertykeys.

* Keyboard Maintainer: [Selwyn](https://github.com/Siilwyn)
* Hardware Supported: QK65 hotswap R2 PCB

Make example for this keyboard (after setting up your build environment):

    make qwertykeys/qk65/r2:default

Flashing example for this keyboard:

    make qwertykeys/qk65/r2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in two ways:

* **Bootloader key**: Hold down the `B` key and plug in the keyboard.
Note that the `B` key is hardcoded to the physical QWERTY layout `B` location on the PCB and `QK_BOOT` does not work.
* **Physical reset button**: Briefly press the SW1 button on the back of the PCB.
