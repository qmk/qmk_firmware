# MNK60_STM32

![MNK60_STM32](https://i.imgur.com/ZBDxWj4h.png)

A QMK-powered, VIA-enabled 60% PCB with support for ANSI/ISO layout, split Backspace, split Right Shift, stepped Caps Lock and 6.25U/7U bottom row.

* Keyboard Maintainer: kopibeng
* Hardware Supported: MONOKEI KEI v2
* Hardware Availability: https://monokei.co/

Make example for this keyboard (after setting up your build environment):

    make kopibeng/mnk60_stm32:default

Flashing example for this keyboard:

    make kopibeng/mnk60_stm32:default:flash


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* Physical reset button: Press the RESET switch on top side of PCB.
* Bootmagic reset: Unplug keyboard, hold down ESC key and plug in the keyboard.
* Keycode reset: Press the `QK_BOOT` keycode (default: MO(1) + R key) in layout if available.