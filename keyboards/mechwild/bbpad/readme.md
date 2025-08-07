# BBPad

![BBPad](https://i.imgur.com/FTrK1TC.png)

A completely normal BlackPill-powered DIY numpad kit.

The `f401` version is the standard for this kit, using an STM32F401 BlackPill. The `f411` version will not run on an STM32F401 BlackPill; if in doubt, use `f401`.

* Keyboard Maintainer: [Kyle McCreery](https://github.com/kylemccreery)
* Hardware Supported: BBPad 1.0
* Hardware Availability: [BBPad on MechWild](https://mechwild.com/product/bbpad/)

Make example for this keyboard (after setting up your build environment):

    make mechwild/bbpad/f401:default
    make mechwild/bbpad/f411:default

Flashing example for this keyboard:

    make mechwild/bbpad/f401:default:flash
    make mechwild/bbpad/f411:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
