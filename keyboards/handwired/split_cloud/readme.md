# Split-Cloud handwired keyboard

The Split-Cloud is a split ortholinear 5x12 layout, forked from the Preonic and Nyquist keyboard models. The default layout adds extra options for some added game compatibility, two control keys for QEmu, and adds a steno layer based on the Planck example.

![Split-Cloud](https://raw.githubusercontent.com/coolsa/cloud-keyboard/main/images/finalProduct.jpg)

* Keyboard Maintainer: [Cloud Chagnon](https://github.com/coolsa)
* Hardware Supported: Pro Micro
* Hardware Availability: [Repository](https://github.com/coolsa/split-cloud)

Make example for this keyboard:

    make handwired/split_cloud:default:avrdude-split-left
    make handwired/split_cloud:default:avrdude-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
