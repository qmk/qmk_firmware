# Palmbrain

![takashicompany/Palmbrain](https://i.imgur.com/Og9lYip.jpeg)

Palmbrain is a 34-key split keyboard with a key pitch of 17 mm (0.9 u).  
It can be equipped with BLE Micro Pro and is also compatible with wireless connectivity.

Palmbrainは17mm(0.9u)のキーピッチを採用した34キーの分割型のキーボードです。  
BLE Micro Proを搭載することが可能で、無線化にも対応しています。

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: PCB, Pro Micro development board.
* Hardware Availability: https://github.com/takashicompany/palmbrain

Make example for this keyboard (after setting up your build environment):

    make takashicompany/palmbrain:default

Flashing example for this keyboard:

    make takashicompany/palmbrain:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
