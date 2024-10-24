# SINGA Kohaku R2 (PCB designed by Zeix)

![Layout Compatibility](https://i.imgur.com/2RaSZxG.png)

65% PCB designed to support Kohaku R2.

-   Keyboard Maintainer: [Zeix](https://github.com/itsme-zeix)
-   Hardware Supported: Singa Kohaku R2 (PCB designed by Zeix)
-   Hardware Availability: https://singakbd.com/

Make example for this keyboard (after setting up your build environment):

    make zeix/singa/kohaku:default

Flashing example for this keyboard:

    make zeix/singa/kohaku:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the top left key and plug in the keyboard.
-   **Physical reset button**: Briefly press the `RESET` button twice or short the 'USB_BOOT' and `GND` pads and plug in the keyboard.
-   **Keycode in layout**: Press the key mapped to `QK_BOOT`.
