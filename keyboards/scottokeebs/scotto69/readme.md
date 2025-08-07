# Scotto69 (PCB Edition)

![Scotto69 (PCB Edition)](https://i.imgur.com/WNtAzcG.jpeg)

The Scotto69 (PCB Edition) is a standard 4x12 ortholinear keyboard with a numpad on the right and 5 macro keys on the left with an optional encoder.

*   Keyboard Maintainer: [Joe Scotto](https://github.com/joe-scotto)
*   Hardware Supported: STM32F072CBT6
*   Hardware Availability: [ScottoKeebs](https://scottokeebs.com)

# Compiling

Make example for this keyboard (after setting up your build environment):

    make handwired/scottokeebs/scotto69:default

Flashing example for this keyboard:

    make handwired/scottokeebs/scotto69:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Bootloader

Enter the bootloader in 3 ways:

*   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
*   **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
*   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
