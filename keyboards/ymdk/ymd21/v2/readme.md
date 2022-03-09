# YMDK YMD21 v2

![YMDK YMD21 v2](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/ymdk/ymd21/v2/New-YMD21-V2-QMK-VIA-21-23-24-Key-RGB-Programmable-Marco-Function-MX-Cherry-Gateron.jpg_Q90.jpg_1_640.jpg)

A 21-to-24-key numpad with RGB Underglow, USB-C, and support for in-switch LEDs.

* Keyboard Maintainer: [The QMK Community](https://github.com/qmk)
* Hardware Supported: YMDK YMD21 v2 (ATmega32U4)
* Hardware Availability: [YMDKey.com](https://ymdkey.com/collections/num-pad-diy/products/new-ymd21-v2-qmk-via-21-23-24-key-rgb-programmable-marco-function-mx-cherry-gateron-switches-numpad-for-lol-battlegrounds), [AliExpress](https://www.aliexpress.com/item/32916152785.html)

Make example for this keyboard (after setting up your build environment):

    make ymdk/ymd21/v2:default

Flashing example for this keyboard:

    make ymdk/ymd21/v2:default:flash

## Bootloader

Enter the bootloader using one of the following methods:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
