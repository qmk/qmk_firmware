# 12pad

12-key hotswap macropad with a rotary encoder, by Positron Electronic.

* Keyboard Maintainer: [juarendra](https://github.com/juarendra)
* Hardware Supported: WeAct Blackpill STM32F401 (USB Type-C)
* Hardware Availability: [Positron Electronic](https://github.com/juarendra/12pad-QMK-VIA)

Making the firmware (after copying this folder to `qmk_firmware/keyboards/positron/12pad`):

    qmk compile -kb positron/12pad -km default

VIA-enabled firmware:

    qmk compile -kb positron/12pad -km via

Flashing:

    qmk flash -kb positron/12pad -km via

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the encoder knob (top-left key) and plug in the keyboard
* **Physical reset**: Hold the `BOOT0` button on the Blackpill, tap `NRST` (or plug in USB), then release `BOOT0`
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

Flash with [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases), `qmk flash`, or `dfu-util` directly:

    dfu-util -a 0 -d 0483:df11 -s 0x08000000:leave -D positron_12pad_via.bin

## VIA

The device is auto-detected by [VIA](https://usevia.app/) once the definition is merged upstream.
For manual sideload use
[`12pad_via_definitions.json`](../../../12pad_via_definitions.json) via the Design tab.
