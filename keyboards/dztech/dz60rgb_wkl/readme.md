# DZ60RGB

![dz60rgb](https://cdn.shopify.com/s/files/1/0043/9140/3591/products/TIM_20190130170231_grande.jpg?v=1548839053)

A hotswap 60% RGB keyboard.

* Keyboard Maintainer: [moyi4681](https://github.com/moyi4681)
* Hardware Supported: DZtech DZ60RGB-WKL V1 and V2
* Hardware Availability: [KBDfans](https://kbdfans.com/)

There are three versions of the DZ60RGB-WKL. Please use the appropriate firmware for your board.

* V1: STM32F303 (Arm), takes .bin files
* V2: ATmega32U4 (AVR), takes .hex files
* V2.1: ATmega32U4 (AVR), takes .bin files
  Started shipping in June 2021 as a slightly modified version of v2.

Make example for this keyboard (after setting up your build environment):

    make dztech/dz60rgb_wkl/v1:default # Arm (STM32F303)
    make dztech/dz60rgb_wkl/v2:default # AVR (ATmega32U4)
    make dztech/dz60rgb_wkl/v2_1:default # AVR (ATmega32U4)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
