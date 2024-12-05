# MarcoPad

![marcopad](https://i.imgur.com/AnC9SeW.png)

*A compact 3x3 keys macropad built with RP-2040 Zero*

* Keyboard Maintainer: [pelegrini.ca](https://pelegrini.ca/marcopad)
* Hardware Supported: [MarcoPad](https://pelegrini.ca/marcopad)
* Hardware Availability: [MarcoPad](https://pelegrini.ca/marcopad)

Make example for this keyboard (after setting up your build environment):

    make marcopad:default

Flashing example for this keyboard:

    make marcopad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key) and plug in the keyboard
* **Physical reset button**: Using 2 paperclips, press and hold the BOOT button, then short press the RESET button on the back of the MarcoPad
* **Physical reset button + plug in**: Using a paperclip, press and hold the BOOT button, then plug in the MarcoPad
