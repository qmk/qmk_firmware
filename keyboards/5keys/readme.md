# 5keys

![5keys](https://imgur.com/yOkI4HT)

This keyboard is a macro keyboard with five keys.

* Keyboard Maintainer: [mikiya418](https://github.com/mikiya418)
* Hardware Supported: 5keys PCBs, Pro Micro
* Hardware Availability: [Thingiverse](https://www.thingiverse.com/thing:6834908)

Make example for this keyboard (after setting up your build environment):

    make 5keys:default

Flashing example for this keyboard:

    make 5keys:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
