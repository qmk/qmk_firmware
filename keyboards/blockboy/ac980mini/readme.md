# blockboy/ac980mini

![AC980mini](https://i.imgur.com/1ZAROm2h.png)
![AC980mini kle](https://imgur.com/prgMVo2h.jpg)


An F-Row-Less 1800 project with fixed layout and lots of RGB.

* Keyboard Maintainer: [rooski15](https://github.com/rooski15)
* Hardware Supported: AC980mini
* Hardware Availability: [Aliexpress - Block Boy AC980mini](https://www.aliexpress.com/item/1005003787162850.html)

Make example for this keyboard (after setting up your build environment):

    make blockboy/ac980mini:default

Flashing example for this keyboard:

    make blockboy/ac980mini:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
