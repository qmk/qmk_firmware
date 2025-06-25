# Dactyl Cyngus 1.0

A split keyboard with 3x5 or 3x6 vertically staggered keys and 3 thumb keys. (I've only tested 3x5). The default layout is a qwerty Miryoku layout. Firmware is basically corne with mouse controls enabled and no LEDs.

Keyboard Maintainer: [juhakaup](https://github.com/juhakaup)
Hardware Supported: Cyngus v1.0
Hardware Availability: [cyngus v1.0](https://github.com/juhakaup/keyboards/tree/main/Cygnus%20v1.0)

Make example for this keyboard (after setting up your build environment):

`make juhakaup/cygnus:default`

Flashing example for this keyboard:

`make juhakaup/cygnus:default:flash`


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button through the reset hole in the case
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available