# navpad 1.0

![navpad_10](https://imgur.com/zxElDdWh.jpg)

Useful and easy to build numpad with nav-cluster

* Keyboard Maintainer: [yushakobo](https://github.com/yushakobo)
* Hardware Supported: NavPad 1.0 PCB, Pro Micro
* Hardware Availability: https://shop.yushakobo.jp/products/navpad-10

Make example for this keyboard (after setting up your build environment):

    make yushakobo/navpad/10:default

Flashing example for this keyboard:

    make yushakobo/navpad/10:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
