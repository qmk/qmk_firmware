# CandyPad Number Pad

![CandyPad Keyboard](https://i.imgur.com/W9cfNOm.png)

*A numeric pad with 2x rotary encoders and OLED display, a joint venture by <b>Candy</b>Keys &times; Bine<b>Pad</b>*

* Keyboard Maintainer: [binepad](https://github.com/binepad)
* Hardware Supported: CandyPad Keyboard
* Hardware Availability:  
    - [candykeys.com](https://candykeys.com/product/candypad-keyboard)
    - [binepad.com](https://binepad.com/products/candypad)

Make example for this keyboard (after setting up your build environment):

    make binepad/candypad:default

Flashing example for this keyboard:

    make binepad/candypad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0:0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the PCB button located on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
