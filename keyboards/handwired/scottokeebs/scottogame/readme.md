# ScottoGame

![ScottoGame](https://i.imgur.com/uXUWY7wh.jpg)

A 40 key handwired ortholinear keyboard. Featuring a split spacebar and a 128x64 OLED with Bongo Cat. Case files available [here](https://github.com/joe-scotto/scottokeebs).

*   Keyboard Maintainer: [Joe Scotto](https://github.com/joe-scotto)
*   Hardware Supported: ATmega32U4
*   Hardware Availability: [Amazon](https://amazon.com)

Make example for this keyboard (after setting up your build environment):

    make handwired/scottokeebs/scottogame:default

Flashing example for this keyboard:

    make handwired/scottokeebs/scottogame:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

*   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
*   **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
*   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available