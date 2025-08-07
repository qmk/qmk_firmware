# BB40

![BB40](https://i.imgur.com/iikCpBuh.png)

A completely normal BlackPill-powered 40% DIY kit.

The `f401` version is the standard for this kit, using an STM32F401 BlackPill. The `f411` version will not run on an STM32F401 BlackPill; if in doubt, use `f401`.

* Keyboard Maintainer: [Kyle McCreery](https://github.com/kylemccreery)
* Hardware Supported: BB40 v1.0
* Hardware Availability: [BB40 on MechWild](https://mechwild.com/product/bb40/)

Make example for this keyboard (after setting up your build environment):

    make mechwild/bb40/f401:default
    make mechwild/bb40/f411:default

Flashing example for this keyboard:

    make mechwild/bb40/f401:default:flash
    make mechwild/bb40/f411:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
