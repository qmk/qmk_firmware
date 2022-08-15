# bajjak

This keyboard is a 6x7 array keyboard, similar in design to the Ergodox EZ.

* Keyboard Maintainer: [Gary Kong](https://github.com/garykong)
* Hardware Supported: bajjak keyboard (ATmega32U4)

Make example for this keyboard (after setting up your build environment):

    make bajjak:default

Flashing example for this keyboard:

    make bajjak:default:flash

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
