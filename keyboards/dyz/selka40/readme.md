# selka40

![pcb](https://i.imgur.com/pqnEVngh.jpg)

40% (13u) ergo hotswap with multiple layouts for bottom row

-   Keyboard Maintainer: [dayatz](https://github.com/dayatz)
-   Hardware Supported: ATMega32u4

Make example for this keyboard (after setting up your build environment):

    make dyz/selka40:default

Flashing example for this keyboard:

    make dyz/selka40:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold the `Esc` key while plugging in the USB cable
-   **Physical reset button**: Briefly press the button on the back of the PCB
-   **Keycode in layout**: Press the key mapped to `RESET` if it is available
