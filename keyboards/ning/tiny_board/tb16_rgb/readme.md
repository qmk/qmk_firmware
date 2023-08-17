# ning/tiny_board/tb16_rgb


A 4*4 tiny keyboard whith rgb lights.

* Keyboard Maintainer: [Ning](https://github.com/ningjx)
* Hardware Supported: The PCB is designed by [Ning](https://github.com/ningjx),with ATMega32U4.
* Hardware Availability: https://oshwhub.com/iqirtryi/atmega32a-kb40

Make example for this keyboard (after setting up your build environment):

    make ning/tiny_board/tb16_rgb:default

Flashing example for this keyboard:

    make ning/tiny_board/tb16_rgb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead

