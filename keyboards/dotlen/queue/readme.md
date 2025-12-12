# Queue.len()

![Queue.len()](https://i.imgur.com/8JKbm6P.png)

A 65% keyboard with multiple layout support.

* Keyboard Maintainer: [Lental](https://github.com/lental)
* Hardware Supported: Custom PCB
* Hardware Availability: Private Group Buy
* Keyboard Layout Editor [Link](https://www.keyboard-layout-editor.com/#/gists/d54fc38f606ce3e990a88044e9b71858)

Make example for this keyboard (after setting up your build environment):

    make dotlen/queue:default

Flashing example for this keyboard:

    make dotlen/queue:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available