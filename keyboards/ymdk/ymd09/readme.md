# YMD09

![YMD09](https://ae01.alicdn.com/kf/HTB1x6BATYvpK1RjSZPiq6zmwXXai/9-Key-QMK-Hotswap-YMDK-RGB-Support-Macro-Function-Type-C-MX-Switches-Mechanical-Keyboard-Numpad.jpg)

A 9-key macropad by [YMDK](https://ymdk.aliexpress.com/store/429151) with per-key RGB lighting.

* Keyboard Maintainer: [Patrick Fruh](https://github.com/kaeltis)
* Hardware Supported: YMD09
* Hardware Availability: [AliExpress](https://www.aliexpress.com/i/4000510880374.html)

Make example for this keyboard (after setting up your build environment):

    make ymdk/ymd09:default

Flashing example for this keyboard:

    make ymdk/ymd09:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
