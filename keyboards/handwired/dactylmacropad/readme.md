# DactylMacropad

[Glamour shot](https://i.imgur.com/ONvbIbmh.jpg)

* Keyboard Maintainer: [bwprobably](https://github.com/bwprobably)
* Hardware Supported: ProMicro (Atmega32U4), EC11 Rotary Encoder
* Hardware Availability: [Example Encoder](https://www.amazon.com/dp/B07D3DF8TK/)
[ProMicro](https://www.sparkfun.com/products/12640)

Make example for this keyboard (after setting up your build environment):

    make default:default

Flashing example for this keyboard:

    make default:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
