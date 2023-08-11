# The Bastard Keyboard

A split ergonomic keyboard.

* Keyboard Maintainer: [Bastard Keyboards](https://github.com/Bastardkb/)
* Hardware Supported: elite-C V4
* Hardware Availability: [Bastard Keyboards](https://bastardkb.com/)

Make example for this keyboard (after setting up your build environment):

    make bastardkb/tbk:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

See the [keyboard build instructions](https://docs.bastardkb.com)


## Important information regarding the reset

If you modify this firmware, make sure to always have a `QK_BOOT` key that can be triggered using only the master side ! This way you ensure that you can always flash the keyboard, even if you mess up.

Otherwise if you're stuck, open the case and reset manually by shorting Gnd and Rst, or pressing the RST button.
