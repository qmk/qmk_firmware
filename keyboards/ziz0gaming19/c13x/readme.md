# c13x

[![c13x](https://i.imgur.com/K0koJJW.jpeg)](https://github.com/qmk/qmk_firmware/tree/master/keyboards/handwired)

*The C-13X is a cute 35% QAZ/Alice-like keyboard, designed by flurpyflurples, but updated by ziz0gaming19 to use ProMicro controller instead.*

* Keyboard Maintainer: [milos](https://github.com/miloslalic19)
* Hardware Supported: ProMicro
* Hardware Availability: *[Aliexpress](https://www.aliexpress.com/item/1005006654641959.html)*

Make example for this keyboard (after setting up your build environment):

    make c13x:default

Flashing example for this keyboard:

    make c13x:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available