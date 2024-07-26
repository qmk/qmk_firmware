# XT8x

![XT8x](https://i.imgur.com/J8QqWWq.png)

A QMK-powered, VIA-enabled TKL PCB with support for ANSI/ISO layout, F12/F13 top row, split Backspace, split Right Shift and 6.25U/7U bottom row. 

* Keyboard Maintainer: kopibeng
* Hardware Supported: A TKL keyboard with STM32F072
* Hardware Availability: N/A

Make example for this keyboard (after setting up your build environment):

    make kopibeng/xt8x:default
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* Physical reset button: Press the RESET switch on top side of PCB.
* Bootmagic reset: Unplug keyboard, hold down ESC key and plug in the keyboard.
* Keycode reset: Press the `QK_BOOT` keycode (default: MO(1) + R keys) in layout if available.
