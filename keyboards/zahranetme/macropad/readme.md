# 8MACROPAD

![8MACROPAD](https://i.imgur.com/s4fdlaY.png)

The 8Macropad is a hot-swappable 6-key And 2 Rotary Encoder Knob, Designed And Manufactured In INDONESIA.

-   Keyboard Maintainer: [ZahraNetme Aka Veriyan](https://github.com/zahranetme)
-   Hardware Supported: 8MACROPAD PCB, PRO MICRO
-   Hardware Availability: Coming Soon!, [TOKOPEDIA](https://www.tokopedia.com/zahranetid)

Make example for this keyboard (after setting up your build environment):

    make zahranetme/macropad/8macropad:default

Flashing example for this keyboard:

    make zahranetme/macropad/8macropad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

-   **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
-   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
