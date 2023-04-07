# Krado66 

![Photo](https://i.imgur.com/Du3bBT9h.jpg)

The Krado66 is a 65%ish ortholinear keyboard the uses standard 65% layout keycaps. It can also be configured to accept standard ANSI keycaps (Full 2.75u Right Shift and 1.25u bottom modifiers.) 

For those that are wondering, "Krado" means "grid" in Esperanto. The board has 66 keys in its default layout. 

* Keyboard Maintainer: [Feags](https://github.com/Feags) / [Krado Industries](https://kradoindustries.com/)
* Hardware Supported: Only Krado66 acrylic case and skeleton cases are supported.
* Hardware Availabilitiy: [Krado Industries](https://kradoindustries.com/)

Make example for this keyboard (after setting up your build environment):

    make kradoindustries/krado66:default

Flashing example for this keyboard:

    make kradoindustries/krado66:default:flash


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available