# Micropad 4x4

![Micropad 4x4](https://imgur.com/ugfJLXJ.jpg)

A budget-friendly 4x4 Macropad

* Keyboard Maintainer: [nibell](https://github.com/Nibell)
* Hardware Supported: Raspberry Pi Pico 
* Hardware Availability: [GitHub](https://github.com/Nibell/Keyboards/tree/main/micropad4x4)

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Hold the button down on the raspberry pi pico while plugging it in. There is no reset button on the pcb.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

Make example for this keyboard (after setting up your build environment):

    make nibell/micropad4x4:default

Flashing example for this keyboard:

    make nibell/macropad4x4:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
