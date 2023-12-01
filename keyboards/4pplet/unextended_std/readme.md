# Unextended Standard PCB

PCB for the Unextended Standard Project. The PCB enables use of M0116, M0118, IIc and NeXT keycaps and is designed to fit in the open sourced Unextended case.

* Keyboard Maintainer: [4pplet](https://github.com/4pplet)
* Hardware Supported: [Unextended Standard PCB](https://github.com/4pplet/Unextended-Standard-PCB)

Make example for this keyboard (after setting up your build environment):

    make 4pplet/unextended_std/rev_a:default

Flashing example for this keyboard:

    make 4pplet/unextended_std/rev_a:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader
Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Escape-key and plug in the keyboard
* **Physical reset header**: Briefly short the header labled "BL/reset" on the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
