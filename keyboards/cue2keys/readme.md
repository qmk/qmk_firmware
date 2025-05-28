# cue2keys

![cue2keys](https://i.imgur.com/hUCVD23.jpeg)

A keyboard that achieves flexible placement and configuration by combining modules as building blocks.

-   Keyboard Maintainer: [esplo](https://github.com/esplo)
-   Hardware Supported: Cue2Keys PCB
-   Hardware Availability: [official website](https://cue2keys.esplo.net/), [online store](https://c2k.booth.pm/items/6659174)

Make example for this keyboard (after setting up your build environment):

    make cue2keys:default

Flashing example for this keyboard:

    make cue2keys:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Physical reset button (connected)**: Briefly double press the RST button on the PCB
-   **Physical reset button (disconnected)**: press and hold the BS button on the PCB, then connect this to the PC
-   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
