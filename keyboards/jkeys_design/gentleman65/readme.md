# Gentleman65

![Render](https://i.imgur.com/uNdJqBuh.jpg)

The Gentleman 65 combines the sleek look of natural wood, with the fun of frosted acrylic to produce a truly unique look that differs from existing boards on the market. The board consists of 2 3mm frosted acrylic layers, topped by 2 layers of 6mm of wood, a frosted acrylic wedge, and 2 feet that give the board an angle of 7°. The board is unique in its inclusion of a top mounting system, something rarely seen on the laser cut board.


* Keyboard Maintainer: [Omar Afzal](https://github.com/0marA)
* Hardware Supported: Gentleman 65 PCB for Gentleman65 & Gentleman 65 Suited Edition hotswap PCB
* Hardware Availability: [Jkeys.Design](https://jkeys.design/)

Getting the board into bootloader mode:

To flash firmware onto this board, you'll need to bring the PCB into bootloader mode. To enter bootloader mode, press the reset button on the back of the PCB twice. The reset button is located in the bottom center near the spacebar switch footprint.

Make example for this keyboard (after setting up your build environment):

    make jkeys_design/gentleman65:default

Flashing example for this keyboard:

    make jkeys_design/gentleman65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
