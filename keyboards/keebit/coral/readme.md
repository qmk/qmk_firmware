# Coral | Split Keyboard

![keebit/coral](https://user-images.githubusercontent.com/24727447/273894600-d73eba98-1507-43d7-8015-42daecd5f762.jpg)

_A 58 keys (56 MX + 2 EC11) 5x6 column-staggered wired split keyboard using Waveshare RP2040-Zero inspired by corne and sofle_v1_

-   Keyboard Maintainer: [numToStr](https://github.com/numToStr)
-   Hardware Supported: _Coral PCB, Waveshare RP2040-Zero_
-   Hardware Availability: _https://discord.gg/TkazrGqKYn_

Make example for this keyboard (after setting up your build environment):

    make keebit/coral:default

Flashing example for this keyboard:

    make keebit/coral:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
-   **Physical reset button**:
    -   Press and hold the `BOOT` button on the MCU while connecting the board.
    -   Double press the `RESET` button on the MCU when connected, if you already flashed the firmware.
-   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
