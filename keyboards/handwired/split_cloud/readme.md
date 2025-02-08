# Split-Cloud handwired keyboard

The Split-Cloud is a split ortholinear 5x12 layout, forked from the Preonic and Nyquist keyboard models. The default layout adds extra options for some added game compatibility, two control keys for QEmu, and adds a steno layer based on the Planck example.

![Split-Cloud](https://i.imgur.com/QoHAFeXh.jpg)

* Keyboard Maintainer: [Cloud Chagnon](https://github.com/coolsa)
* Hardware Supported: Pro Micro
* Hardware Availability: [Repository](https://github.com/coolsa/split-cloud)

Make example for this keyboard:

    make handwired/split_cloud:default

This keyboard uses [Handedness by EEPROM](https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom) as default, and must be configured once on each side. The make commands are:

    make handwired/split_cloud:default:avrdude-split-left
    make handwired/split_cloud:default:avrdude-split-right

[QMK Toolbox](http://qmk.fm/toolbox) can also be used to set EEPROM handedness. Place the controller in bootloader mode and select menu option Tools -> EEPROM -> Set Left/Right Hand

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
