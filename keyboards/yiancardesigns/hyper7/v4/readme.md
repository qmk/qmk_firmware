# Hyper7 v4

This is a very big pcb... It supports VIA.

* Keyboard Maintainer: [Yiancar](http://yiancar-designs.com/) and on [GitHub](https://github.com/yiancar) 
* Hardware Supported: A very big keyboard with STM32F072RB 
* Hardware Availability: https://mechboards.co.uk/

Make example for this keyboard (after setting up your build environment):

    make yiancardesigns/hyper7/v4:default

Flashing example for this keyboard:

    make yiancardesigns/hyper7/v4:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (3,0) in the matrix (F3) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
