# smolka

![smolka](https://i.imgur.com/5A84GVJh.png)

Smolka is a "40%" keyboard with a single left-hand macro column, and arrow keys, designed by BlindAssassin111 of Viktus Design.

The Smolka has multiple configurations and can support up to two rotary encoders in the left macro column. The PCB supports multiple bottom row configurations and can also be configured to remove the arrow keys and right column to create a near 60% layout (minus number row).


* Keyboard Maintainer: [jrfhoutx](https://github.com/yourusername)
* Hardware Supported: Viktus Smolka PCB
* Hardware Availability: Available only through a group buy in the 40% Discord server. 

Make example for this keyboard (after setting up your build environment):

    make viktus/smolka:default

Flashing example for this keyboard:

    make viktus/smolka:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (1,0) in the matrix (the top key in the macro column) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
