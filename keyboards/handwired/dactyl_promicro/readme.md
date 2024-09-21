# Dactyl (Pro Micro)

![Dactyl](https://i.imgur.com/a7uY1eSh.png)

A split body, concave shaped key well, columnar keyboard with a 6 key thumb cluster that takes inspiration from the Kinesis Advantage keyboard range. This rendition of the *Dactyl* requires two micro controllers rather than the [original implementation](/keyboards/handwired/dactyl/) of a micro controller and I/O expander.

* Keyboard Maintainer: [Matt Adereth](https://github.com/adereth)
* Hardware Supported: Pro Micro controller, or clones of
* Hardware Availability: [GitHub](https://github.com/adereth/dactyl-keyboard)

Make example for this keyboard (after setting up your build environment):

    make handwired/dactyl_promicro:default

Flashing example for this keyboard:

    make handwired/dactyl_promicro:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Optional Hardware

A speaker can be hooked-up to either side to the `5` (`C6`) pin and `GND`, and turned on via `AUDIO_ENABLE`.

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
