# fpad

![fpad](https://i.imgur.com/LPFezWrh.jpeg)

An open source macro keyboard with 4x4 keys, 5 [illuminated rotary encoders](https://www.sparkfun.com/products/15141), and JoyStick.

-   Keyboard Maintainer: [td2sk](https://github.com/td2sk)
-   Hardware Supported: [fpad PCB](https://github.com/td2sk/fpad), ProMicro
-   Hardware Availability: [Design](https://github.com/td2sk/fpad)

Make example for this keyboard (after setting up your build environment):

    make fpad:default

Flashing example for this keyboard:

    make fpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

-   **Physical reset button**: Briefly press the button on the bottom of the ProMicro - some may have pads you must short instead
