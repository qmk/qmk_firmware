# 0x3E

An 60%-ish Ortholinear Low-profile (Kailh Choc) Keyboard, with Boardwalk-like layout (1.5u outer mod colums, split spacebar) and OLED display

* Keyboard Maintainer: [plut0nium](https://github.com/plut0nium)
* Hardware Supported: 0x3E PCB
* Hardware Availability: [MKUltra](https://mkultra.click)

Make example for this keyboard (after setting up your build environment):

    make plut0nium/0x3e:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## How to reset the board into bootloader mode

The PCB has a dedicated Reset pushbutton on the underside, press it once to reset the board into bootloader mode.
In addition, bootmagic lite is enabled in the default config, holding ESC (upper left key) while plugging the board will start in bootloader.
