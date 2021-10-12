# CannonKeys DB60

DB60 "Daughterboard 60" Keyboard

* Keyboard Maintainer: [Andrew Kannan](https://github.com/awkannan)
* Hardware Supported: STM32F072CBT6 (or equivalent)

Make example for this keyboard (after setting up your build environment):

    make cannonkeys/db60/rev2:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Some notes about the versions:
The original DB60 was shipped with the J-02. To build that, you will need to use the following command:

    make cannonkeys/db60/j02:default

Solderable DB60s were shipped with keyboards after the J-02. This variant has cutouts along the top and bottom to support O-ring gasket mounting. To build these, you can use this command:

    make cannonkeys/db60/rev2:default
    
Hotswap ANSI DB60s were shipped with the Bakeneko keyboards from CannonKeys. These also have the o-ring gasket mounting points. To build this:

    make cannonkeys/db60/hotswap:default
