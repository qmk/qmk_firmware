# studiokestra/galatea

![studiokestra/galatea](https://i.imgur.com/juPhV1xh.png)

TKL H87/88c compatible PCB with support for the most common layouts.

* Keyboard Maintainer: [Studio Kestra](https://github.com/studiokestra/)
* Hardware Supported: Most H87C compatible keyboards
* Hardware Availability: https://RNDKBD.com; https://geon.works/
* Rev1 firmware is used for Galatea PCBs with no RGB underglow.
* Rev2 firmware is used for Galatea PCBs with RGB underglow.

Make example for this keyboard (after setting up your build environment):

    make studiokestra/galatea/rev1:default

Flashing example for this keyboard:

    make studiokestra/galatea/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
