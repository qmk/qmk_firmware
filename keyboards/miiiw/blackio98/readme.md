# MIIIW BlackIO98

![BlackIO98](https://i.imgur.com/XY3AahE.jpg)
![BlackIO98](https://i.imgur.com/WlWAeC9.jpg)

A customizable 98-keys keyboard.

* Keyboard Maintainer: [ArthurCyy](https://github.com/ArthurCyy)
* Hardware Supported: BlackIO98 rev_0100
* Hardware Availability: [MIIIW](https://www.miiiw.com/)

Make example for this keyboard (after setting up your build environment):

    make miiiw/blackio98/rev_0100:default

Flashing example for this keyboard:

    make miiiw/blackio98/rev_0100:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: With the power switch off, hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard.
* **Physical button**: With the power switch off, hold the small metal button on the right side under the spacebar keycap and plug in the keyboard.
* **Keycode in layout**:
  * (Official firmware only) With the power switch on, press and hold the left Shift+ Fn+ upper right DEL.
  * (Unofficial firmware) With the power switch on, press the key mapped to `QK_BOOT` if it is available.
