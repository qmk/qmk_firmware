Levinson
========

A split 40% split 4x12 ortholinear keyboard made and sold by Keebio. It's essentially a Let's Split with LED backlight support and 2u thumb key support. [More info at Keebio](https://keeb.io).

Keyboard Maintainer: [Bakingpy/nooges](https://github.com/nooges)  
Hardware Supported: Pro Micro, Elite-C  
Hardware Availability: [Keebio](https://keeb.io)  

Make example for this keyboard (after setting up your build environment):

    make levinson/rev2:default

Example of flashing this keyboard with Pro micro:

    make levinson/rev2:default:avrdude

Example of flashing this keyboard with Elite-C:

You'll need to add `BOOTLOADER = atmel-dfu` to your `rules.mk` to ensure that resetting the board works properly.

Hold the reset button on the Elite-C board, or the reset button on the keyboard if already assembled, then release the button and run:

    make levinson/rev2:default:dfu

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

A build guide for this keyboard can be found here: [Levinson Build Guide](https://docs.keeb.io)
