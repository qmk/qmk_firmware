# kk980

![kk980](https://i.imgur.com/NDsBMR6.jpg)

A hotswap 98% RGB Mechanical keyboard.

* Keyboard Maintainer: [sets3n](https://github.com/sets3n)
* Hardware Supported: kk980 PCB
* Hardware Availability: -

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## HEX

Make example for this keyboard (after setting up your build environment):

    make sets3n/kk980:default

## FLASH

Flashing example for this keyboard:

    make sets3n/kk980:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
