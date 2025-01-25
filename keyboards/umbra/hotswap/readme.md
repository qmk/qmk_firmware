# UMBRA

![UMBRA](https://i.imgur.com/2d94i6H.jpg)

A multi-mount 60% keyboard with PCB choice featuring popular layouts, underglow, and rotary option.

* Keyboard Maintainer: [IV Works](https://www.iv-works.com/)
* Hardware Supported: [UMBRA](https://www.iv-works.com/i)
* Hardware Availability: [Shop](https://iv-works.com/product-category/umbra/)

Make example for this keyboard (after setting up your build environment):

    make umbra/hotswap:default

Flashing example for this keyboard:

    make umbra/hotswap:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

How to enter bootloader (DFU):
* PCB will arrive flashed. With USB plugged in press Fn+Esc to enter DFU. Flash the firmware and replug the USB cable to fresh boot the PCB.

* If that method fails please locate the RESET header on the back of the PCB just right of the MCU. Short the 2 plated holes for 2 seconds to enter DFU. Flash the firmware and replug the USB cable to fresh boot the PCB.