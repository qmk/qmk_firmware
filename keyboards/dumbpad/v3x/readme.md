# dumbpad v3.x - rgb & hotswap

![dumbpad](https://i.imgur.com/ND03FiFl.png)

A 4x4 numpad/macropad with a rotary encoder to the left of the bottom row of keys.

-   Keyboard Maintainer: [imchipwood](https://github.com/imchipwood) // [deveth0](https://github.com/deveth0)
-   Hardware repository: [dumbpad on github](https://github.com/imchipwood/dumbpad)
-   PCB Revisions Supported: v3.1

Make example for this keyboard (after setting up your build environment):

    make dumbpad/v3x:default

Flashing example for this keyboard:

    make dumbpad/v3x:default:flash

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the encoder and plug in the keyboard
-   **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
-   **Keycode in layout**: Press the key mapped to `RESET` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
