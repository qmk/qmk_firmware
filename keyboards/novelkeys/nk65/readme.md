# NK65

![NK65](https://i.imgur.com/EXNbVpL.jpg)

> NOTE: For PCBs with revision v1.4 or later please use nk65/v1_4 in the make command.

This is a standard fixed layout 65% PCB. It supports VIA and full per-key RGB.

* Keyboard Maintainer: [Yiancar](http://yiancar-designs.com/) and on [GitHub](https://github.com/yiancar)
* Hardware Supported: A 65% keyboard with STM32F303CC
* Hardware Availability: https://novelkeys.xyz/

Make example for this keyboard (after setting up your build environment):

    make novelkeys/nk65/v1:default

Flashing example for this keyboard:

    make novelkeys/nk65/v1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
