# BB65

![bb65](https://i.imgur.com/0PrDjuS.png)

BB65 is a completely normal BlackPill-powered 65% DIY kit. It’s got all the letters, a number row, and arrow keys. Basic as it can be.

The `f401` version is the standard for this kit, using an STM32F401 BlackPill. The `f411` version will not run on an STM32F401 BlackPill; if in doubt, use `f401`.

* Keyboard Maintainer: [Kyle McCreery](https://github.com/kylemccreery)
* Hardware Supported: BB65 v1.0
* Hardware Availability: [BB65 on MechWild](https://mechwild.com/product/bb65/)

Make example for this keyboard (after setting up your build environment):

    make mechwild/bb65/f401:default
    make mechwild/bb65/f411:default

Flashing example for this keyboard:

    make mechwild/bb65/f401:default:flash
    make mechwild/bb65/f411:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
