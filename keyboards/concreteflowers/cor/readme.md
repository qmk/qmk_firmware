# saevus cor

![saevus cor](https://i.imgur.com/AOT6mmMl.jpg)

An exploded 65% with a macro column.

* Keyboard Maintainer: [Ramon Imbao](https://github.com/ramonimbao)
* Hardware Supported: ATmega32u4

Make example for this keyboard (after setting up your build environment):

    make saevus/cor:via
    
Flashing example for this keyboard:

    make saevus/cor:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the upper left key and plug in the keyboard
* **Physical reset button**: Briefly press the reset button on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
