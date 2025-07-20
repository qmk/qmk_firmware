# Viktus Styrka v2

![viktus/sp111_v2](https://i.imgur.com/ApgZRhgh.png)

A split southpaw fullsize-esque layout. Round 2 of the board has RGB LED indicators.

* Keyboard Maintainer: [BlindAssassin111](https://github.com/blindassassin111)
* Hardware Supported: SP-111 round 2 PCBs only
* Hardware Availability: Space Cables, Ashkeebs, protoTypist, mykeyboard, ilumkb, SwitchKeys

Make example for this keyboard (after setting up your build environment):

    make viktus/sp111_v2:default

Flashing example for this keyboard:

    make viktus/sp111_v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
