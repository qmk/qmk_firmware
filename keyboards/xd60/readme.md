# QMK Firmware for XIUDI's 60% XD60 PCB

![Top View of a pair of XD60 Keyboard](https://i.imgur.com/3Jq2743.jpg)

## Quantum MK Firmware
For the full Quantum feature list, see [the parent readme.md](/readme.md).

## Additional Notes
The XD60 is essentially a GH60 rev. C, with support for a right-hand arrow cluster. Includes full compatibility with GH60 expansion boards. Board also supports in-switch LEDs (two-pin, single colour), as well as WS2182 LED strips for underglow lighting. Default keymap included, matching configuration on sale page.

Version 2 PCBs include 6 soldered on RGB underglow LEDs on the bottom, and are labelled "XD60v2" on the top. They are otherwise identical to v1 PCBs.

## Known Issues
In-switch backlight LEDs seem to only support 1 brightness level.

## Build
To build the default keymap, simply run `make xd60-default`.
