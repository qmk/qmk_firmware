# split75

![split75](https://i1.wp.com/mechboards.co.uk/wp-content/uploads/2019/10/HTB1qf0aSOLaK1RjSZFxq6ymPFXae.jpg)

This is a port of the QMK firmware for the split75 keyboard, also known as the ve.a taobao split clone. It runs on
ps2avrGB firmware, like the [ps2avrGB keyboard](https://www.keyclack.com/product/gb-ps2avrgb/) or the ones sold
by [Winkeyless](http://winkeyless.kr/product/ps2avrgb-parts/).

Original work performed by Michael L. Walker, all credit goes to him. I've tidied up the keymap (removed 3 extra keys), a couple of functions, info.json and this Readme.

* Keyboard Maintainer: [Michael L. Walker](https://github.com/walkerstop)
* Hardware Availability: https://a.aliexpress.com/_BT9raf https://item.taobao.com/item.htm?id=556970472669&toSite=main

Make example for this keyboard (after setting up your build environment):

    make mt/split75:default

Flashing example for this keyboard:

    make mt/split75:default:flash

or

    bootloadHID -r split75_default.hex

**Reset Key**: Hold down the key located at 3rd left position in the bottom row, commonly programmed as Left Control while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
