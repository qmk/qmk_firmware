# XO87 Solderable PCB

![XO87](https://cdn.imweb.me/thumbnail/20201120/c90a5bdb75264.png) 

A TKL custom keyboard made by Monstar Gear.

* Keyboard Maintainer: The QMK Community
* Hardware Supported: XO87 Solderable version
* Hardware Availability: [Monstargear](https://monstargears.com)

Make example for this keyboard (after setting up your build environment):

    make monstargear/xo87/solderable:default

Flashing example for this keyboard:

    make monstargear/xo87/solderable:default:flash
    
The LED matrix is not yet working with this board.  A temporary workaround to allow the caps/scroll/num lock LEDs to work has been added to allow this firmware to be functional without the led matrix.

Please be aware that Monstar Gear has not yet switched to this firmware and any PCB that is running the pre-installed firmware will need to use ISP to flash their board for the first time.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
