# XL Keyboards XL 87 RGB

An 87-key keyboard using an APM32F103CBT6 MCU through the STM32F103-compatible
QMK platform, with a 16 MHz external crystal, the uf2boot bootloader, and 123
WS2812 RGB LEDs: 91 on the top side and 32 on the underside.

* Keyboard Maintainer: [Hiiwwy](https://github.com/Hiiwwy)
* Hardware Supported: XL Keyboards XL 87 RGB
* Hardware Availability: [XL 87 RGB](https://m.tb.cn/h.81WiQXl29FMSp3b)

Make example for this keyboard (after setting up your build environment):

    make xl_keyboards/xl_87_rgb:default

Flashing example for this keyboard:

    make xl_keyboards/xl_87_rgb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in one of the following ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Double-tap the reset button on the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
