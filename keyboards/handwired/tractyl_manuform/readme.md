# Tractyl Manuform (4x6, 5x6)

the [Dactyl-Manuform](https://github.com/tshort/dactyl-keyboard) is a split curved keyboard based on the design of [adereth dactyl](https://github.com/adereth/dactyl-keyboard) and thumb cluster design of the [manuform](https://geekhack.org/index.php?topic=46015.0) keyboard, the hardware is similar to the let's split keyboard. all information needed for making one is in the first link.
![Imgur](https://i.imgur.com/kDNVTI4l.jpeg)

* Keyboard Maintainer: [drashna](https://github.com/drashna)
* Hardware Supported: Teensy 2.0++, WeAct BlackPill F411

Make example for this keyboard (after setting up your build environment):

    make handwired/tractyl_manuform/5x6_right/f411/drashna:default

Flashing example for this keyboard:

    make handwired/tractyl_manuform/5x6_right/f411/drashna:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
