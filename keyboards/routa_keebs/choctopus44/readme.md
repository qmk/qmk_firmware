# Choctopus44

![Choctopus44](https://raw.githubusercontent.com/SlightHeadache/choctopus44/master/images/choctopus44_grid.png)

The Choctopus44 is 44-key column staggered keyboard.

* Keyboard Maintainer: [SlightHeadache](https://github.com/SlightHeadache)
* Hardware Supported: Choctopus44 PCBs, Pro Micro and compatible controllers supported
* Hardware Availability: [Project repo](https://github.com/SlightHeadache/choctopus44)

Make example for this keyboard (after setting up your build environment):

    make routa_keebs/choctopus44:default

Flashing example for this keyboard:

    make routa_keebs/choctopus44:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* **Physical reset button**: Briefly press the button on the controller or on the top of the PCB. Some controllers might require a double-tap, some may require a long press.
* **Bootmagic lite**: You can also access the bootloader by using Bootmagic Lite commands (see [QMK Documentation - Command](https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_command))