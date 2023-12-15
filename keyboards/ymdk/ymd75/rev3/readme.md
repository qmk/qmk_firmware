# YMD75

75% keyboard from YMDK. YMDK sell the board and name it "YMD75".

* Keyboard Maintainer: [Wayne K Jones](github.com/WarmCatUK)
* Hardware Supported: rev3 (ATmega32u4)
* Hardware Availability: <https://www.aliexpress.com/item/32812690592.html>

Make example for this keyboard (after setting up your build environment):

    make ymdk/ymd75/rev3:default

Flashing example for this keyboard:

    make ymdk/ymd75/rev3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
