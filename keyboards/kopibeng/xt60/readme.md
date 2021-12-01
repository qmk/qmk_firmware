# XT60

![XT60](https://i.imgur.com/LYrorzJ.png)

A QMK-powered, VIA-enabled universal 60% PCB with support for single-colour LED backlight, RGB underglow, as well as various layouts such as split Backspace, split Right Shift, stepped Caps Lock and 6.25U/7U bottom row.

* Keyboard Maintainer: kopibeng
* Hardware Supported: A 60% keyboard with ATMEGA32U4
* Hardware Availability: N/A

Make example for this keyboard (after setting up your build environment):

    make kopibeng/xt60:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* Physical reset button: Press the RESET switch on top side of PCB.
* Bootmagic reset: Unplug keyboard, hold down ESC key and plug in the keyboard.
* Keycode reset: Press the RESET keycode (default: MO(1) + R keys) in layout if available.