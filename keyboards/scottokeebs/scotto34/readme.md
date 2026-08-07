# Scotto34 (PCB Edition)

![Scotto34 (PCB Edition)](https://i.imgur.com/nTxYa7ih.jpg)

A low profile 34-key split monoblock ortholinear keyboard that uses 18x17mm spaced Choc switches and an exposed controller in the middle.

*   Keyboard Maintainer: [Joe Scotto](https://github.com/joe-scotto)
*   Hardware Supported: Scotto34 (PCB Edition), Raspberry Pi Pico
*   Hardware Availability: [ScottoKeebs](https://scottokeebs.com), [Amazon](https://amazon.com), [AliExpress](https://aliexpress.com)

# Compiling

Make example for this keyboard (after setting up your build environment):

    make scottokeebs/scotto34:default

Flashing example for this keyboard:

    make scottokeebs/scotto34:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Bootloader

Enter the bootloader in 3 ways:

*   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
*   **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
*   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
