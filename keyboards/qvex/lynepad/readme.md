# QVEX Lynepad

![qvex/lynepad](https://qvex.eu/img/lynepad.jpg)

Macro pad with 11 keys, thumbwheel encoder, and rotary 4-way switch.

* Keyboard Maintainer: [QVEX Tech](https://qvex.eu)
* Hardware Supported: QVEX Lynepad
* Hardware Availability: [QVEX Lynepad on Tindie](https://www.tindie.com/products/qvex_tech/qvex-lynepad-macro-keypad/)

Make example for this keyboard (after setting up your build environment):

    make qvex/lynepad:default

Flashing example for this keyboard:

    make qvex/lynepad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down top left key and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB (rev. 2.x or newer)
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available (usualy bottom right key on layer 4)