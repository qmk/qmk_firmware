# Manibus keyboard

![Imgur](https://i.imgur.com/0l17Xyyl.jpg)

A 5x7 split ergonomic keyboard designed and sold by [Blank Tehnologii](https://blank.computer/).

* Keyboard Maintainer: [Alex Paulescu/SamuraiKek](https://github.com/SamuraiKek)
* Hardware Supported: [ATmega32u4](https://www.digikey.com/en/products/detail/microchip-technology/ATMEGA32U4-AU/1914602)
* Hardware Availability: [Blank Tehnologii](https://blank.computer/)

Make example for this keyboard (after setting up your build environment):

    make blank_tehnologii/manibus:default

Example of flashing this keyboard:

    make blank_tehnologii/manibus:default:dfu-split-left # Left half
    make blank_tehnologii/manibus:default:dfu-split-right # Right half

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
