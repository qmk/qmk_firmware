# th1800

![th1800](https://i.imgur.com/7LZUCgBl.png)

The project use atmega32a, through hole component, 1800 compact layout, open source.

* Keyboard Maintainer: [Team Mechlovin](https://github.com/mechlovin)
* Hardware Supported: th1800 PCB, ATmega32A
* Hardware Availability: [PCB](https://github.com/mechlovin/PCB/tree/master/1800-Compact)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/th1800:default

Flashing example for this keyboard:

    make mechlovin/th1800:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

**Reset Key:** To put the Th1800 into bootloader, push reset swith on the top of the PCB.

IF87_rev2 used USBasploader from [Erovia tutorial](https://erovia.github.io/posts/thk/#bootloader), thank you [Erovia](https://github.com/Erovia).
