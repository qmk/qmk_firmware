# MNK65

![MNK65](https://i.imgur.com/YTrMDHjh.jpg)

A QMK-powered, VIA-enabled 65% PCB with support for ANSI/ISO layouts, split Backspace and various bottom row layout configurations.

* Keyboard Maintainer: kopibeng
* Hardware Supported: MONOKEI
* Hardware Availability: https://monokei.co/

Make example for this keyboard (after setting up your build environment):

    make kopibeng/mnk65:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* Physical reset button: Press the RESET switch on top side of PCB.
* Bootmagic reset: Unplug keyboard, hold down ESC key and plug in the keyboard.
* Keycode reset: Press the `QK_BOOT` keycode (default: MO(1) + Home keys) in layout if available.
