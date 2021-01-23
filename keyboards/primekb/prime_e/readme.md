# Prime_E

![Prime_E](https://imgur.com/7Rl4JOAl.jpg)

An ergonomic 45%.

* Keyboard Maintainer: [Holtenc](https://github.com/holtenc/)
* Hardware Supported:
    * [Prime_E Standard](std/) PCBs, ATmega32u4 (in switch LED backlights)
    * [Prime_E RGB](rgb/) PCBs, Atmega32u4 (RGB underglow)
* Hardware Availability: [Store Link](https://www.primekb.com)

Make examples for this keyboard (after setting up your build environment):

    make primekb/prime_e/std:default
    make primekb/prime_e/rgb:default
    make primekb/prime_e/std:via
    make primekb/prime_e/rgb:via

Flashing examples for this keyboard:

    make primekb/prime_e/std:default:flash
    make primekb/prime_e/rgb:default:flash
    make primekb/prime_e/std:via:flash
    make primekb/prime_e/rgb:via:flash

## Accessing Bootloader Mode

To access Bootloader Mode, do one of the following:

* Tap the Reset switch mounted on the bottom side of the PCB
* Hold the Space and B keys while connecting the USB cable

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
