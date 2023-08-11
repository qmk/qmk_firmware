# dyz40

![pcb](https://i.imgur.com/XFYzF94h.jpg)

40% 13u hotswap with multiple layouts for bottom row

-   Keyboard Maintainer: [dayatz](https://github.com/dayatz)
-   Hardware Supported: ATMega32u4
-   Hardware Availability: Local Indonesia GB.

Make example for this keyboard (after setting up your build environment):

    make dyz/dyz40:default

Flashing example for this keyboard:

    make dyz/dyz40:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold the `Esc` key while plugging in the USB cable
-   **Physical reset button**: Briefly short the pins under the Enter key
-   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
