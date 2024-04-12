# 15PAD

![15PAD](https://i.imgur.com/J7sZSnx.jpeg)

15PAD is a Macropad With 12 Keys & 3 Rotary Encoder, Designed And Manufactured In INDONESIA.

-   Keyboard Maintainer: [zlabkeeb](https://github.com/zlabkeeb)
-   Hardware Supported: 15Pad PCB, RP2040 ZERO
-   Hardware Availability: (INDONESIA ONLY) [Tokopedia](https://www.tokopedia.com/zahranetid/macropad-15pad-via-compatible)

Make example for this keyboard (after setting up your build environment):

    make zlabkeeb/15pad:default

Flashing example for this keyboard:

    make zlabkeeb/15pad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the top of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

