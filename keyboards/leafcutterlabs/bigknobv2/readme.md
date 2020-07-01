# bigknobv2

![](https://i.imgur.com/8ZBC23k.jpg)

Macropad Media Controller with USB-C + RGB underglow + Hotswap and support for up to 40mm knob

* Keyboard Maintainer: [Craig Gardner](https://github.com/leafcutterlabs)
* Hardware Supported: bigknobv2
* Hardware Availability: [Reddit](https://www.reddit.com/r/mechmarket/comments/gp8y3y/uscahbigknobv2_prototype_usbc_qmk_4_key_hotswap/)

Notes:

* Due to a hardware error, USB-C is not reversible (i.e., it only works in one orientation)
* Due to `TAP_DANCE_ENABLE = yes`, the [QMK Configurator](https://config.qmk.fm/) will not be able to compile firmware (i.e., you must compile manually)

Make example for this keyboard (after setting up your build environment):

    make leafcutterlabs/bigknobv2:default 

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
