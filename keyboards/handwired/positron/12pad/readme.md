# 12pad

12-key hotswap macropad with a rotary encoder, by Positron Electronic.

* Keyboard Maintainer: [juarendra](https://github.com/juarendra)
* Hardware Supported: WeAct Blackpill STM32F401 (USB Type-C)
* Hardware Availability: [Positron Electronic](https://github.com/juarendra/12pad-QMK-VIA)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb handwired/positron/12pad -km default

Flashing:

    qmk flash -kb handwired/positron/12pad -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the encoder knob (top-left key) and plug in the keyboard
* **Physical reset**: Hold the `BOOT0` button on the Blackpill, tap `NRST` (or plug in USB), then release `BOOT0`
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
