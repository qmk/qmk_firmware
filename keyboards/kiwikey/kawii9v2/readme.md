# Kawii9 Rev2

![Kawii9 Rev2](https://i.imgur.com/ogYWVq1.jpeg)

Kawii9 rev2 is a keypad with per-key RGB and expandable modules. There are 3 variants:

1. Simple 3x3 keypad,
2. with a 1.3" OLED screen and a rotary encoder,
3. with another rotary encoder and a RGB indicator LED

More infos: https://kiwikey.vn/mechkey/kawii9/

* Keyboard Maintainer: [KiwiKey](https://github.com/kiwikey)
* Hardware Supported: Kawii9 rev2 PCB
* Hardware Availability: from Group-buy, or via KiwiKey Website (https://kiwikey.vn/mechkey/kawii9/)

Make example for this keyboard (after setting up your build environment):

    make kiwikey/kawii9v2:default

Flashing example for this keyboard:
    make kiwikey/kawii9v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
