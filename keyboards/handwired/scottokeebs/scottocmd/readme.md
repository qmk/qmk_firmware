# ScottoCMD

![ScottoCMD](https://i.imgur.com/rxiMZNnh.jpg)

A 40-key ortholinear keyboard with a 6.25u spacebar, 4 dedicated function keys and 0.96" 128x64 OLED display. Case files available [here](https://github.com/joe-scotto/scottokeebs).

*   Keyboard Maintainer: [Joe Scotto](https://github.com/joe-scotto)
*   Hardware Supported: ATmega32U4, 0.96" 128x64 I2C OLED
*   Hardware Availability: [Amazon](https://amazon.com)

Make example for this keyboard (after setting up your build environment):

    make handwired/scottokeebs/scottocmd:default

Flashing example for this keyboard:

    make handwired/scottokeebs/scottocmd:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

*   **Bootmagic reset**: Hold down the key at (1,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
*   **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
*   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
