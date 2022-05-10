# Xenon

![Xenon](https://i.imgur.com/QYMDzGFh.jpg)

Xenon is 60% columnar staggered keyboard.

* Cherry MX and Kailh low profile key switch support
* OLED display
* Full color LED
* Prototype board area (behind the promicro)

* Keyboard Maintainer: [Narinari](https://github.com/narinari)
* Keymap Maintainer: [Kyrremann](https://github.com/Kyrremann)
* Keyboard files can be found here: https://github.com/narinari/xenon-keyboard

Make example for this keyboard (after setting up your build environment):

    make xenon:default

Example of flashing this keyboard:

    make xenon:default:flash

How to enter bootloader (DFU):

Press the reset button next to the TRRS port on the side you are trying to flash (USB must be connected to the Pro Micro that you are flashing).

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the 
[make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with
the [Complete Newbs Guide](https://docs.qmk.fm/#/newbs). 
