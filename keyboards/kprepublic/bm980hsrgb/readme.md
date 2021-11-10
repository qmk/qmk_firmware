# BM980HSRGB

![BM980HSRGB](https://i.imgur.com/k4NQGLxh.jpeg)

A 1800, hotswap, in switch RGB keyboard from KPRepublic.

* Keyboard Maintainer: [peepeetee](https://github.com/peepeetee)
* Hardware Supported: BM980HSRGB
* Hardware Availability:
  * https://kprepublic.com/products/bm980rgb-bm980-rgb-hot-swappable-custom-mechanical-keyboard-pcb-programmed-qmk-via-firmware-full-rgb-switch-underglow-type-c
  * https://www.aliexpress.com/item/1005002509519466.html
  * https://item.taobao.com/item.htm?id=645862298692

Make example for this keyboard (after setting up your build environment):

    make kprepublic/bm980hsrgb:default

Flashing example for this keyboard:

    make kprepublic/bm980hsrgb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in one of 3 ways:

* Short the two-pad footprint beneath the f12 key while the board is plugged in
* Press the switch labled RST on the back of the PCB, near the MCU, while the board is plugged in
* Hold the Esc key while connecting the USB cable (also erases persistent settings)
