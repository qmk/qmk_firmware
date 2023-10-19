# 0xCB New Horizons

65% Keyboard

* Keyboard Maintainer: [Conor Burns](https://github.com/conor-burns)
* Hardware Supported: https://github.com/0xcb-dev/0xCB-NewHorizons
* Hardware Availability: On [KeebSupply](https://keeb.supply/products/0xcb-new-horizons)

![](https://keeb.supply/assets/nh-full.webp)

![](https://keeb.supply/assets/nh-bottom.webp)

To go to bootloader press ESC while plugging in the board.

Make example for this keyboard using an [RP2040 controller](https://keeb.supply/products/0xcb-helios) (after setting up your build environment):

    make 0xcb/newhorizons:default

Flashing example for this keyboard:

    make 0xcb/1337:default:flash
    
Make example for this keyboard using an [Atmega 32u4 controller](https://keeb.supply/products/0xcb-pluto) (after setting up your build environment):

    make 0xcb/newhorizons/32u4:default

Flashing example for this keyboard:

    make 0xcb/1337:default/32u4:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
