# Zodiark Keyboard

![Zodiark Split](https://i.imgur.com/49O8aowl.jpg)

A split keyboard with 5x7 including a thumbcluster, encoders on each side, per key RGB, and 2x I2C headers per side, supporiting 1.3"/.96" 128x64 OLEDs (the 1.3" is an SSH1106 OLED, refer to QMK documentation for limitations), .91" 128x32 OLEDs.

* Keyboard Maintainer: [Aleblazer](https://github.com/Aleblazer/), [Discord Link](https://discord.gg/BCSbXwskVt)
* Hardware Supported: Pro Micro and derivatives
* Hardware Availability: Pending Group Buy - [Discord Link](https://discord.gg/BCSbXwskVt)

Make example for this keyboard (after setting up your build environment):

    make aleblazer/zodiark:default

Flashing example for this keyboard:

    make aleblazer/zodiark:default:flash

Remove TRRS cable from halves, plug into one side, press reset button when asked. Repeat process on the other side.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Credit to Sofle and Josef Adamcik <josef.adamcik@gmail.com> for OLED and layer code.
