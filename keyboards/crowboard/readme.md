# crowboard

![crowboard](https://i.imgur.com/Rg7IYPwh.jpg)

RP2040 based 36 key keyboard

* Keyboard Maintainer: [doesntfazer](https://github.com/doesntfazer)
* Hardware Supported: Raspberry Pi Pico
* Hardware Availability: keyboarddweebs.net

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Hold the button down on the raspberry pi pico while plugging it in. There is no reset button on the pcb.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

Make example for this keyboard (after setting up your build environment):

    make crowboard:default

Flashing example for this keyboard:

    make crowboard:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


