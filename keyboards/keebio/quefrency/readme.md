# Quefrency

A split 60/65% staggered keyboard made and sold by Keebio. [More info at Keebio](https://keeb.io).

* Keyboard Maintainer: [Bakingpy/nooges](https://github.com/nooges)
* Hardware Supported: Pro Micro (Rev. 1), ATmega32u4 (Rev. 2 & 3)
* Hardware Availability: [Keebio](https://keeb.io/)

Make example for this keyboard (after setting up your build environment):

    make keebio/quefrency/rev3:default

Example of flashing this keyboard:

    make keebio/quefrency/rev3:default:flash

Handedness detection is already hardwired onto the PCB, so no need to deal with `EE_HANDS` or flashing .eep files.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

A build guide for this keyboard can be found here: [Keebio Build Guides](https://docs.keeb.io)
