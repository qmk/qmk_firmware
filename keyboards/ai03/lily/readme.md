# Lily

![Lily](https://i.imgur.com/nIhwT2V.png)

PCB for Gok's Lily keyboard

* Keyboard Maintainer: [ai03](https://github.com/ai03-2725)
* Hardware Supported: Lily PCB
* Hardware Availability: Through Lily group buy

Make example for this keyboard (after setting up your build environment):

    make ai03/lily:default

Flashing example for this keyboard:

    make ai03/liily:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset**: Double tap the button on the bottom on the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
