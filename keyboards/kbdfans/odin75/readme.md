# ODIN75
A customizable 75% keyboard.

* Keyboard Maintainer: [moyi4681](https://github.com/moyi4681)
* Hardware Supported: ODIN75
* Hardware Availability: [KBDfans](https://kbdfans.com/products/kbdfans-odin-75-mechanical-keyboard)

## Bootloader mode

Enter the bootloader in 3 ways:

* Bootmagic reset: Hold down the left top key then plug in the USB cable.
* Physical reset button: Hold down the reset button then plug in the USB cable.
* Keycode in layout: Press the key mapped to QK_BOOT if it is available.

## Making firmware

Make example for this keyboard (after setting up your build environment):

    make kbdfans/odin75:default

Flashing example for this keyboard:

    make kbdfans/odin75:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
