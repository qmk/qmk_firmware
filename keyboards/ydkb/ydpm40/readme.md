# ydkb/ydpm40

A pair of 40% keyboards, that share the same PCB, designed by yang. Among the two, ydp40 has a Planck-like layout, while ydm40 is more traditional.

* Keyboard Maintainer: [xofyarg](https://github.com/xofyarg)
* Hardware Supported: https://github.com/yangdigi/YDPM40-Keyboard-PCB
* Hardware Availability: https://ydkb.world.taobao.com/

Make example for this keyboard (after setting up your build environment):

    make ydkb/ydpm40:default

Flashing example for this keyboard:

    make ydkb/ydpm40:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

The ATmega328P MCU comes with BootloadHID. To enter it, hold down the
top left key and plug in the keyboard.
