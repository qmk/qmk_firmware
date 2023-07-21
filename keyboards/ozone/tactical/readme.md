# Ozone Tactical

![Ozone Tactical](https://www.ozonegaming.com/uploads/PRODUCTS/tactical/fotos/ozone_tactical_1.jpg)

A 65% Spanish-ISO Wireless Mechanical Keyboard.

Brought to you by: [SonixQMK](https://github.com/SonixQMK/qmk_firmware)
Layout by: [Pablo Martinez Bernal](https://github.com/elpekenin)

* Hardware Supported: Ozone Tactical (SN32F248BF)
* Hardware Availability: [Ozone](https://www.ozonegaming.com/es/product/tactical)
* Layout by [Pablo Martinez Bernal](https://github.com/elpekenin) based of the Keychron K6 RGB ISO implementation by [Philip Mourdjis](https://github.com/PhilipMourdjis)

# Install
1. If your keyboard currently has stock firmware installed, put your keyboard first into bootloader by shorting the boot pin (bottom side, 3rd from left) to GND (i.e. USB housing) before plugging your keyboard to the PC. Placing a `QK_BOOT` keycode in your keymap is highly recommended.
1. Download and run [Sonix Flasher](https://github.com/SonixQMK/sonix-flasher/releases/tag/v0.2.5).
1. In Sonix Flasher, select `SN32F24x` under 'Device'. And select `0x00` as the qmk offset.
1. Click 'Flash QMK...' and flash your .bin file. 

* * *

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
