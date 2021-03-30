# Mode Eighty

![MODE80](https://i.imgur.com/26uzM3yl.jpg)\
[Image Gallery](https://imgur.com/t/mechanicalkeyboards/8Uf6c2m?nc=1)

The Mode80 is a tenkeyless high-end keyboard sold by [Mode Designs](https://shop.modedesigns.com/).

* Keyboard Maintainer: [Gondolindrim](https://github.com/gondolindrim)
* Hardware Supported: proprietary PCB using STM32F072 controller
* Hardware Availability: you can get a Mode Eighty as of today (dec. 2020) through the in stock sales or special groupbuy editions at https://shop.modedesigns.com/

Make example for this keyboard (after setting up your build environment):

    make mode/eighty/m80h:default # Hotswap
    make mode/eighty/m80s:default # Soldered

Flashing example for this keyboard:

    make mode/eighty/m80h:default:flash # Hotswap
    make mode/eighty/m80s:default:flash # Soldered

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
