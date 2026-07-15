# sweet16v2

A 4x4 macropad with per-key RGB lighting and underglow.

* Keyboard Maintainer: [ziptyze](https://github.com/ziptyze)
* Hardware Supported: 1upkeyboards Sweet 16 v2
* Hardware Availability: [1upkeyboards](https://1upkeyboards.com/)

Make example for this keyboard (after setting up your build environment):

    make 1upkeyboards/sweet16v2:default

Flashing example for this keyboard:

    make 1upkeyboards/sweet16v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways for atmel-based controllers:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available


Enter the bootloader in 2 ways for rp2040-based controllers:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Bootsel button**: Hold the bootsel button on controller and plug in the keyboard
