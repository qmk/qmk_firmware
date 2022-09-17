# Yetis keyboard

![yetis](https://i.imgur.com/sM9UuP7h.png)

34 key split keyboard with columnar stagger. Suitable for bigger palms.

* Keyboard Maintainer: [Norbert Pocs](https://github.com/jogme)
* Hardware Supported: Yetis pcb, Frood microcontroller (but any Elite C layout works fine)
* Hardware Availability: [pcb and case](https://github.com/jogme/yetis-keyboard), [frood](https://42keebs.eu/shop/parts/controllers/frood-rp2040-pro-micro-controller)

Make example for this keyboard (after setting up your build environment):

    make yetis:default

Flashing example for this keyboard:

    make yetis:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* Short the pins on the microcontroller manually
