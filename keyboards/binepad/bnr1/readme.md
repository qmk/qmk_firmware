# BINEPAD BNR1

The BNR1 is a multifunction knob, which can be rotated, pressed, and rotated while pressed.

* Keyboard Maintainer: [Binpad](https://github.com/binepad)
* Hardware Supported:
    * **BNR1** & **BNR1 R2** *("V1" ft. ATMega32u4 MCU)*
    * **BNR1 V2** *("V2" ft. STM32F103 MCU)*
* Hardware Availability: [Binepad.com](https://www.binepad.com/bnr1)

Make example for this keyboard (after setting up your build environment):

    make binepad/bnr1/v1:default

  ..or..

    make binepad/bnr1/v2:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the knob while plugging in the keyboard's USB cable
* **Physical reset button**: Briefly press the button on the underside of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` *(or `RESET`)* if it is available
