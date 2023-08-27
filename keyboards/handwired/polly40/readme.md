# Polly40

![Polly40](https://i.imgur.com/QJCQcFAh.jpg)

A handwired 40% keyboard running a Pro micro Atmega32u4 controller

* Keyboard Maintainer: [Paul Enrico N. Viola](https://github.com/PollyV1)
* Hardware Supported: Atmega32u4 controller
* Hardware Availability: https://shopee.ph/Pro-Micro-ATmega32U4-5V-16MHz-USB-Arduino-Compatible-i.20469516.225455828

Make example for this keyboard (after setting up your build environment):

    make handwired/polly40:default

Flashing example for this keyboard:

    make handwired/polly40:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: Short Ground and RST pin
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available