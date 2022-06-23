# Lumberelite

![Lumberelite](https://imgur.com/AUegdQa)

Based off of the brilliant work of [Peej's Lumberjack](https://github.com/peej/lumberjack-keyboard).

An Elite-C version of the Lumberjack with the addition of an OLED screen.

* Keyboard Maintainer: [tjeffree](https://github.com/tjeffree)
* Hardware Supported: Custom PCB, Elite-C or similar (same pinout)

Make example for this keyboard (after setting up your build environment):

    make tjeffree/lumberelite:default

Flashing example for this keyboard:

    make tjeffree/lumberelite:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
