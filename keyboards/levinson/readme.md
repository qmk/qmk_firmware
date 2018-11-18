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

    Add `BOOTLOADER = atmel-dfu` to the `rules.mk` file.

    Hold the reset button on the elite-c board, or the reset button on the board if already assembled.

    Release the button and run `make levinson/rev2:default:dfu`

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

A build guide for this keyboard can be found here: [Levinson Build Guide](https://docs.keeb.io)
