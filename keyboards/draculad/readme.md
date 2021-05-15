# DracuLad

![DracuLad](https://github.com/mangoiv/draculad/blob/master/pictures/rev1/both_sides_showcase.jpg?raw=true)

*A 34-36 key split keyboard*
- 36 keys, two of them can be replaced by rotary encoders making it support 34-36 keys and 2-4 encoders.
- bright RGB Underglow with WS2812B LEDs
- one SSD1306 OLED per side
- aggressive pinky stagger similar to the Kyria but with an alternative thumb cluster to raise comfort for large hands
- support for MX and Choc switches

* Keyboard Maintainer: [MangoIV](https://github.com/MangoIV)
* Hardware Supported: [DracuLad PCBs and cases](https://github.com/MangoIV/dracuLad), [the Pimoroni trackball](https://shop.pimoroni.com/products/trackball-breakout)
* Hardware Availability: [MangoIV's GitHub](https://github.com/MangoIV/dracuLad)

Make example for this keyboard (after setting up your build env):

    make draculad:default

or for the version using the Pimoroni trackball:

    make draculad:pimoroni

Flashing example for DFU and Caterina respectively (replace `default` with the name of your keymap):

    make draculad:default:dfu
    make draculad:default:flash

When flashing the first time using handedness by EEPROM, use the [QMK guide for that topic](https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom).

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
