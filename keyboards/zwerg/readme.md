# zwerg

![zwerg](https://i.imgur.com/hkFLvd2.jpeg)

A 40% ortholinear split keyboard.

* Keyboard Maintainer: [floookay](https://github.com/floookay)
* Hardware Supported: zwerg pcbs with 0xcb Gemini
* Hardware Availability: <https://github.com/floookay/zwerg>

Make example for this keyboard (after setting up your build environment):

    make zwerg:default

Flashing example for this keyboard:

    make zwerg:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the Gemini controller
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
