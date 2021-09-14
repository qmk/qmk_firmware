# KBD67 Mk.II RGB (Hotswap)

A customizable 65% RGB keyboard.

* Keyboard Maintainer: [moyi4681](https://github.com/moyi4681)
* Hardware Supported: KBD67 Mk.II RGB V1, V2, and V3
* Hardware Availability: [kbdfans](https://kbdfans.myshopify.com/)

There are three versions of the KBD67 MKII RGB. Please use the appropriate firmware for your board. 

* V1: STM32F303 (Arm), takes `.bin` files
* V2: ATmega32U4 (AVR), takes `.hex` files
* V3: Atmega32U4 (AVR), takes  `.bin` files

Make example for this keyboard (after setting up your build environment):

    make kbdfans/kbd67/mkiirgb/v1:default # Arm (STM32F303)
    make kbdfans/kbd67/mkiirgb/v2:default # AVR (ATmega32U4)
    make kbdfans/kbd67/mkiirgb/v3:default # AVR (ATmega32U4)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
