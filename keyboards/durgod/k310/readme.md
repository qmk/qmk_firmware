# Taurus K310

This code is shared between all K310 variants.  Currently only the base model with no backlight is supported.

This is a standard off-the-shelf Durgod Taurus K310 full-sized 104/105-key
keyboard without backlight.  This supports both the ANSI and ISO variants.

* Keyboard Maintainers: [dkjer](https://github.com/dkjer) and [tylert](https://github.com/tylert)
* Hardware Supported: [Durgod Taurus K310 board with STM32F070RBT6](https://www.durgod.com/product/k310-space-gray/)
* Hardware Availability: [Amazon.com](https://www.amazon.com/Durgod-Taurus-K310-Mechanical-Keyboard/dp/B07TXB4XF3)

## Instructions

### Build

Make command example for this keyboard (after setting up your build environment):

    make durgod/k310/base:default

Flashing example for this keyboard:

    make durgod/k310/base:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

### Initial Flash

Instructions for Flashing from initial Stock Firmware:
* [Initial Flashing](../k3x0/readme.md#initial-flash)
