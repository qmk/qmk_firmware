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

This keyboard uses the uf2boot bootloader. Enter it by double-tapping the
reset button, by pressing a key mapped to `QK_BOOT`, or by holding the key at
matrix position `0,0` while plugging in the keyboard. Copy the generated UF2
file to the USB mass-storage device presented by the bootloader.

See the [build environment setup](https://docs.qmk.fm/#/newbs_getting_started)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
for more information.
