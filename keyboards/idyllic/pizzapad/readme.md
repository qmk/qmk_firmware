# Pizza Pad PCB

![Pizza Pad PCB](https://i.imgur.com/eJLuaZY.jpg)

A 3x3 PCB designed for the Idyllic Pretty Pad.

* Keyboard Maintainer: Zykrah
* Hardware Supported: Pizza Pad PCB (using a SEEED XIAO RP2040)
* Hardware Availability: [Mechstock](https://mechstock.com.au/)

Make example for this keyboard (after setting up your build environment):

    make idyllic/pizzapad:default

Flashing example for this keyboard:

    make idyllic/pizzapad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press both the `BOOT` and `RESET` buttons at the same time
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
