# General Information

This is more or less a HHKB base layout, but with completely different Fn layers. I don't use most of the HHKB secondary key positions because, honestly, they make no sense to me at all.

Fn key layer is focused mostly on keyboard firmware features (like RGB) as well as some of the necessary alternate functions. It also hold media controls, F-keys and Reset.

Left Tab-Hold layer is focused on nav cluster functionality, and turns Backspace into Delete (and moves Backspace up into the top right 1u position).


# Build instructions

To simply build the firmware file: `make clean && make kbdfans/kbd6x:mekberg`

To build and immediately flash: `make clean && make kbdfans/kbd6x:mekberg:dfu`
