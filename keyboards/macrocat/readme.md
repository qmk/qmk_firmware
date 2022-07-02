# macrocat

![macrocat](https://i.imgur.com/ItLHGBfh.jpg)

A cat like macro keyboard/numpad.

* Keyboard Maintainer: [catmunch](https://github.com/catmunch)
* Hardware Supported: Fully Supported
* Hardware Availability: [MacroCat Keyboard](https://github.com/catmunch/macrocat)

Make example for this keyboard (after setting up your build environment):

    make macrocat:default

Flashing example for this keyboard:

    make macrocat:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Brand new atmega32u4 chip**: Plug the cable in, it will automatically boot into bootloader
