# 1upocarina

This keyboard is the Super16v3 from 1upkeyboards. It is a 4x4 macropad with the option for up to four encoders in the top row. The keypad features in-switch per-key addressable RGB leds, as well as 32 1mm underglow RGB leds for very bright and smooth lighting effects. The Super16v3 uses an rp2040 microcontroller and direct pins instead of a matrix.

* Keyboard Maintainer: [ziptyze](https://github.com/ziptyze)

Make example for this keyboard (after setting up your build environment):

    make 1upkeyboards/1upsuper16v3:default

Flashing example for this keyboard:

    make 1upkeyboards/1upsuper16v3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix. For this keyboard it is the top left button
* **Physical reset button**: Hold the button on the back of the PCB and plug in the keyboard
