# Waterfowl

The Waterfowl is a 36-key split keyboard inspired by the Kyria and Arch-36.

* Keyboard Maintainer: [CyanDuck](https://github.com/JW2586)
* Hardware Supported: Pro Micro 5V/16MHz and compatible.

Make example for this keyboard (after setting up your build environment):

    make waterfowl:default

Example of flashing this keyboard:

    make waterfowl:default:flash

Enter the bootloader by:
- Press the key mapped to reset (bottom left key in FUNC layer/layer 3)
- Press the reset button on the PCB
- Connect GND and RST pins on pro micro

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
