# Lunakey Pico

![lunakey_pico](https://i.imgur.com/S5N8AFhh.jpg)

This is a 40% split keyboard which has 3x6 vertically staggered keys and 4 thumbnail keys.

* Keyboard Maintainer: [Yoichiro Tanaka](https://github.com/yoichiro)
* Hardware Supported: Lunakey Pico PCB, Raspberry Pi Pico MCU.
* Hardware Availability: https://booth.pm/ja/items/3324672

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb yoichiro/lunakey_pico -km default

Flashing example for this keyboard:

    qmk flash -kb yoichiro/lunakey_pico -km default -bl avrdude

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
