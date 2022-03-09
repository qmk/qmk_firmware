# croxsplit44

![davanti](https://user-images.githubusercontent.com/41386727/131268038-801cb316-7bb1-486d-8432-be5412ddc31b.jpg)

# A 3d printed 44 key handwired split keyboard
Thanks to ak666666 for the base case layout : https://www.thingiverse.com/thing:4146704
*
* Keyboard Maintainer: https://github.com/Samux6146
* Hardware Supported: handwired, teensy ++ 2.0

Make example for this keyboard (after setting up your build environment):

    make handwired/croxsplit44:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
