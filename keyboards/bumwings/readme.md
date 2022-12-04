# BumWings

![BumWings](https://i.imgur.com/WwpVsNN.jpg)

BumWings is my first *unibody* (i.e., monoblock) ergonomic keyboard design.  It is based heavily on other ergonomic keyboard concepts, and is strongly influenced by the TypeMatrix keyboards, Ergodox-EZ, and many others.  It features a 14x4 matrix with 54 keys total.

* Keyboard Maintainer: [Matthew A. Schnoor](https://github.com/tubbytwins)
* Hardware Supported: BumWings v001 PCB with Waveshare RP2040-zero board
* Hardware Availability: Open Source license, full KICAD source is [in my GitHub repository](https://github.com/tubbytwins/bumwings-kbd/)

Make example for this keyboard (after setting up your build environment):

    make bumwings/v001:default (or replace with any other layout in the "keymaps" directory)

To flash the keyboard, simply put your RP2040-zero board in firmware update mode by holding the BOOT button and then clicking the RESET button.  When the "RPI-RP2" drive appears, simply copy the ".uf2" file to the drive.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Layout Options

* default (QWERTY)
* dvorak
* colemak-dh
