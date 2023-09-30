# syenakeyboards/aswagata

![SyenaKeyboards Aswagata](https://images.tokopedia.net/img/cache/900/VqbcmM/2023/9/30/dc3e20b5-eb94-4f92-8a44-f2f556dcc1ab.jpg)

Aswagata as a macropad has four buttons with default functions: `copy`, `paste`, `cut`, and `select` (for Linux). It can be reconfigured with Via.

* Keyboard Maintainer: [Syenasweta](https://github.com/syenasweta)
* Hardware Supported: RP2040
* Hardware Availability: [Tokopedia (Syenasweta)](https://tokopedia.link/iG6UfrrHvDb)

Make example for this keyboard (after setting up your build environment):

    make syenakeyboards/aswagata:default

Flashing example for this keyboard:

    make syenakeyboards/aswagata:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Copy key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
