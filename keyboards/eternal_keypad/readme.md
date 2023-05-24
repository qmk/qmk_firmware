# eternal_keypad

![eternal_keypad](https://i.imgur.com/BAzc343.png)

A 36 key gaming keypad that can be assembled and configured for both left and right handed mouse users.

* Keyboard Maintainer: [duckyb](https://github.com/duckyb)
* Hardware Supported: ETERNAL Keypad
* Hardware Availability: Open Source, files available on [gitHub](https://github.com/duckyb/eternal-keypad)

Make example for this keyboard (after setting up your build environment):

    make eternal_keypad:default

Flashing example for this keyboard:

    make eternal_keypad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,1) in the matrix (the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `RESET` if it is available (activated by holding the lower right key and tapping the lower left key)
* **Physical reset button**: Briefly sort the pads labeled "RST" and "GND" on the micro-controller
