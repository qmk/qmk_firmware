# Typ65+

![Typ65+](https://i.imgur.com/WCTwfdF.jpg)

A 65% solderable or hotswap PCB with left side macro column, support for VIA and layer indicator LEDs.

* Keyboard Maintainer: kopibeng
* Hardware Supported: A 65% keyboard with ATMEGA32U4
* Hardware Availability: https://www.axiomstudios.shop/

Make example for this keyboard (after setting up your build environment):

    make kopibeng/typ65:via
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* Physical reset button: Press the RESET switch on top side of PCB.
* Bootmagic reset: Unplug keyboard, hold down ESC key and plug in the keyboard.
* Keycode reset: Press the `QK_BOOT` keycode (default: MO(1) + HOME keys in default layout).
