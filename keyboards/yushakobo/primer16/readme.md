# Primer16

![Primer16](https://i.imgur.com/60cc5Nmh.jpg)

This is 16 keys keyboard.
It is designed for beginners.

* Keyboard Maintainer: [yushakobo](https://github.com/yushakobo)
* Hardware Supported: Quick17 PCBs, Pro Micro (ATmega32u4)
* Hardware Availability: [yushakobo shop](https://shop.yushakobo.jp/products/5386)

Make example for this keyboard (after setting up your build environment):

    make yushakobo/primer16:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

[Build guide](https://github.com/yushakobo/build-documents/tree/master/Primer16)

