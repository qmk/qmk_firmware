# h88_g2

[h88_g2](https://i.imgur.com/t7chDf8h.png)

New generation of the h88 keyboard PCB platform with an STM32 microcontroller.

* Keyboard Maintainer: [Josh Hinnebusch](https://github.com/hineybush)
* Hardware Supported: H88 G2 PCB w/ STM32F072 MCU
* Hardware Availability: [hineybush.com](https://hineybush.com)

Make example for this keyboard (after setting up your build environment):

    make hineybush/h88_g2:default

Flashing example for this keyboard:

    make hineybush/h88_g2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix Escape and plug in the keyboard.
* **Physical reset button**: Press the button on the back of the PCB for a minumum of 3 seconds, then release.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
