# OSAv2 Numpad - Topre

![osav2_numpad_topre](https://i.imgur.com/G6yNtJMh.png)

An OSAv2 Numpad in topre flavor.

-   Keyboard Maintainer: BlindAssassin111
-   Hardware Supported: OSAv2 Numpad Topre PCB
-   Hardware Availability: Viktus Design LLC

Make example for this keyboard (after setting up your build environment):

    make viktus/osav2_numpad_topre:default

Flashing example for this keyboard:

    make viktus/osav2_numpad_topre:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
