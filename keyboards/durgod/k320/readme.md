# Taurus K320

This code is shared between all K320 variants.  Currently only the base model with no backlight is supported.

This is a standard off-the-shelf Durgod Taurus K320 TKL (87/88-key)
keyboard without backlight.  This supports both the ANSI and ISO variants.

* Keyboard Maintainers: [dkjer](https://github.com/dkjer) and [tylert](https://github.com/tylert)
* Hardware Supported: [Durgod Taurus K320 board with STM32F070RBT6](https://www.durgod.com/product/k320-space-gray/)
* Hardware Availability: [Amazon.com](https://www.amazon.com/Durgod-Taurus-Corona-Mechanical-Keyboard/dp/B078H3WPHM)

## Instructions

### Build

Make command example for this keyboard (after setting up your build environment):

    make durgod/k320/base:default

Flashing example for this keyboard:

    make durgod/k320/base:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

### Initial Flash

Instructions for Flashing from initial Stock Firmware:
* [Initial Flashing](../k3x0/readme.md#initial-flash)
