# 1upSuper16v3

This keyboard is the Super16v3 from 1upkeyboards, a 4x4 macropad with the option for up to four encoders in the top row.  Notable features include in-switch per-key addressable RGB LEDs and thirty two 1mm underglow RGB LEDs; for bright and smooth lighting effects. The Super16v3 utilises an rp2040 microcontroller, wired using direct pins.

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
