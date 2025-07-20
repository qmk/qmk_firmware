# hotdox76

*An Ergodox style keyboard with per key RGB.*

* Keyboard Maintainer: [Drashna Jael're](https://github.com/Drashna Jael're)
* Hardware Supported: Hotdox 76v2
* Hardware Availability: https://github.com/Oh-My-Mechanical-Keyboard 

Make example for this keyboard (after setting up your build environment):

    make hotdox76v2:default

Flashing example for this keyboard:

    make hotdox76v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
