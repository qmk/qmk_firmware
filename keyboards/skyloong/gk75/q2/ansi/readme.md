# The GK75 Q2 ansi is an RGB matrix Keyboard with an encoder.

![GK75 Q2 ansi](https://i.imgur.com/G9PrQtth.png)

## The PCB features:
* QMK & VIA compatibility
* RGB Matrix effect backlight
* Mechanical switches Keyboard and supporting up to 4 encoders which are can be replaced with switches.


The following is the QMK Firmware for the Desktop 75% keylayout -  designed by Dongguan Jizhi Electronic Technology Co., Ltd

* Keyboard Maintainer: [NaturalZh](https://github.com/NaturalZh)
* Hardware Supported: Desktop PCB for Skyloong key layout 75%, STM32F103C8T6
* Hardware Availability:[Skyloong_CN]( http://www.skyloong.com.cn) OR [Skyloong_HK](https://skyloongtech.com)

Make example for this keyboard (after setting up your build environment):

    make skyloong/gk75/q2/ansi:default

Flashing example for this keyboard:

    make skyloong/gk75/q2/ansi:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
