# omega4

![omega4](https://i.imgur.com/tV4iCoD.png)

uniform stagger 4 row board.

-   Keyboard Maintainer: [makenova](https://github.com/makenova)
-   Hardware Supported: [omega4](https://github.com/makenova/omega)
-   Hardware Availability: https://www.cbkbd.com/product/omega4-keyboard-kit

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb makenova/omega/omega4 -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
-   **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
-   **Keycode in layout**: Press the key mapped to `RESET` if it is available
