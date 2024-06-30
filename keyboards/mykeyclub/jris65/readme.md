# JRIS65

![hotswap](https://i.imgur.com/kJzebgd.jpeg)
**Hotswap PCB**

A 65% keyboard sold by Mykeyclub.

* Keyboard Maintainer: [The QMK Community](https://github.com/qmk)
* Hardware Supported: JRIS65 R1 hotswap.
* Hardware Availability: intermitently via group buys from [Mykeyclub](https://www.mykeyclub.com/)

Make example for this keyboard (after setting up your build environment):

    make mykeyclub/jris65/hotswap:default

Flashing example for this keyboard:

    make mykeyclub/jris65/hotswap:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Keycode in layout**: Using the default firmware, assign a key to Reset (`QK_BOOT`) and press the assigned key.
* **Physical reset button**: Briefly press the button on the back of the PCB

The QMK default keymap has FN+Backspace assigned to `QK_BOOT` so you can use that key sequence for subsequent flashing.

## Disclaimer

In May 2024 Mykeyclub was contacted to see if they had interest in contributing firmware to the QMK project they did not. This code is thus community supported.

This firmware has only been tested with JRIS65 R1 hotswap and is likely to work with R2 hotswap. The soldered variant of this PCB requires testing, with actual hardware, before being added.
