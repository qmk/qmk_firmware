# RP2040-Keyboard-3

![waveshare/rp2040_keyboard_3](https://i.imgur.com/HYoHwVk.jpeg)

RP2040-Keyboard-3 is a high-performance, cost-effective three-key keyboard development board designed by Waveshare.
It features programmable custom key functions and RGB lighting effects.

* Keyboard Maintainer: [zvecr](https://github.com/zvecr)
* Hardware Supported: <https://www.waveshare.com/wiki/RP2040-Keyboard-3>
* Hardware Availability: <https://thepihut.com/products/rp2040-ctrl-c-v-shortcut-keyboard-plus>

Make example for this keyboard (after setting up your build environment):

    make waveshare/rp2040_keyboard_3:default

Flashing example for this keyboard:

    make waveshare/rp2040_keyboard_3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key) and plug in the keyboard
* **Physical reset button**: Press and hold the `BOOT` button, then briefly press the `RESET` button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
