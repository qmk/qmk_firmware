# QVEX Lynepad 2

![QVEX Lynepad 2.1](https://i.imgur.com/eDvVaE4h.jpeg)

*Macropad with 11 keys, thumbwheel, and a rotary 4-way switch*

* Keyboard Maintainer: [QVEX Tech](https://github.com/QVEX-Tech) ([seflm](https://github.com/seflm))
* Hardware Supported: QVEX Lynepad
* Hardware Availability: [QVEX Lynepad on Tindie](https://www.tindie.com/products/qvex_tech/lynepad-21-hot-swap-macropad-w-joystick/)

Make example for this keyboard (after setting up your build environment):

    make qvex/lynepad:default

Flashing example for this keyboard:

    make qvex/lynepad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

### Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset button**: Briefly press the reset button on the back of the Lynepad using SIM tool (rev.2.0 or newer) 
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
