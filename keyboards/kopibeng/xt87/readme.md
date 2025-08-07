# XT87

![XT87](https://i.imgur.com/N1QaXPTh.jpg)

A QMK-powered, VIA-enabled F12 TKL PCB with support for ANSI/ISO layout, split Backspace, split Right Shift and 6.25U/7U bottom row. 

* Keyboard Maintainer: [kopibeng](https://github.com/kopibeng)
* Hardware Supported: A TKL keyboard with STM32F072
* Hardware Availability: [MONOKEI](https://monokei.co)

Make example for this keyboard (after setting up your build environment):

    make kopibeng/xt87:default
	
Flashing example for this keyboard:

	make kopibeng/xt87:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* Physical reset button: Press the RESET switch on top side of PCB.
* Bootmagic reset: Unplug keyboard, hold down ESC key and plug in the keyboard.
* Keycode reset: Press the `QK_BOOT` keycode (default: MO(1) + R keys) in layout if available.
