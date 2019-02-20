# Laptreus

TODO: Insert cool photo

Laptreus is a 40% bluetooth keyboard in the style of the Atreus, which is specifically designed to sit atop your laptop keyboard.

Maintainer: [Chuck Lauer Vose](https://github.com/vosechu)
MCU: Adafruit Feather 32u4 BLE
Purchase link: GB coming soon
Case link: GB coming soon
Case design files: TODO

## Flashing

**NOTE**: Make sure you don't have a second QMK keyboard plugged in when you do this!

[Default layout documentation](https://github.com/qmk/qmk_firmware/tree/master/keyboards/laptreus/keymaps/default)

To compile and flash to the board:

    make laptreus:default:avrdude

To just compile:

    make laptreus:default

Then use QMK toolbox to write the file

## Changelog

v1.2: Mostly working, but JST connector is a little too tight and the reset switch is not connected.

## Build log

TODO
