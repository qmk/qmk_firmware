# DZ65RGB

A customizable 65% RGB keyboard.

* Keyboard Maintainer: [moyi4681](https://github.com/moyi4681)
* Hardware Supported: DZ65RGB V1,V2 and V3
* Hardware Availability: [KBDfans](https://kbdfans.com/)

There are three versions of the DZ65RGB. Please use the appropriate firmware for your board.

* V1: STM32F303 (Arm), takes .bin files
* V2: ATmega32U4 (AVR), takes .hex files, is31fl3731 rgbmatrix driver
* V3: ATmega32U4 (AVR), takes .bin files, is31fl3741 rgbmatrix driver

## Bootloader mode

To put in bootloader mode, hold the `Esc` key while plugging in the USB cable. or use reset key behind the pcb.

## Making firmware

Make example for this keyboard (after setting up your build environment):

    make dztech/dz65rgb/v1:default # Arm (STM32F303)
    make dztech/dz65rgb/v2:default # AVR (ATmega32U4)
    make dztech/dz65rgb/v3:default # AVR (ATmega32U4)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
