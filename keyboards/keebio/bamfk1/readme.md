# BAMFK-1

![BAMFK-1](https://i.imgur.com/DF9dW7dh.png)

PCB for the Big Switch with support for horizontal rotary encoders.

* Keyboard Maintainer: [Keebio](https://github.com/nooges)
* Hardware Supported: BAMFK-1 PCB
* Hardware Availability: [Keebio](https://keeb.io/)

Make example for this keyboard (after setting up your build environment):

    make keebio/bamfk1:default

Flashing example for this keyboard:

    make keebio/bamfk1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Big Switch and plug in the keyboard. This will also clear EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset button**: Briefly press the button on the back of the PCB. It is next to the LED labeled `DR12`.
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create.
