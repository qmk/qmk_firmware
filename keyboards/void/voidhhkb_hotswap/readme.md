# VoidHHKB-Hotswap

![VoidHHKB-Hotswap)](https://i.imgur.com/dxTs8gB.jpeg)

VoidHHKB-Hotswap 60% PCB designed for the [HSKB project](https://github.com/Dev01-D/HSKB).

*   Keyboard Maintainer: [James Wilson](https://github.com/JamesWilson1996)
*   Hardware Supported: STM32F072CBT6
*   Hardware Availability: [HSKB](https://github.com/Dev01-D/HSKB)

# Compiling

Make example for this keyboard (after setting up your build environment):

    make void/voidhhkb_hotswap:default

Flashing example for this keyboard:

    make void/voidhhkb_hotswap:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Bootloader

Enter the bootloader in 3 ways:

*   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
*   **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
*   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
