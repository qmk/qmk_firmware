# 11squares

![11squares](https://i.imgur.com/qV2gdeq.jpeg)

*The optimal packing of 11 keyswitches. Usable as an 11 key macropad or numpad.*

* Keyboard Maintainer: [keotl](https://github.com/keotl)
* Hardware Supported: [keotl/11squares](https://github.com/keotl/11squares)
* Hardware Availability: [Kicad Project](https://github.com/keotl/11squares)

Make example for this keyboard (after setting up your build environment):

    make keotl/11squares:default

Flashing example for this keyboard:

    make keotl/11squares:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
