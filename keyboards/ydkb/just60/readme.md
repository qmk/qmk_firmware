# Just60

Just60 keyboard produced by Yang. The keyboard comes with a custom Mass Storage Device bootloader and a TMK based firmware from ydkb.io.

To use a QMK based firmware, you might want to install a QMK bootloader. The PCB exposes 6 pins for ISP(In-System Programming), and they are located just under the ATMega32U4 chip. From left to right, the pins are `VCC`, `SCLK`, `MOSI`, `MISO`, `RESET`, `GND`. The `GND` is the square one. You could program the flash with any AVR programmer, or a Raspberry Pi with `avrdude`.

Backlight LEDs and Bluetooth are not working yet.

* Keyboard Maintainer: [Jianfei Wang](https://github.com/thinxer)
* Hardware Supported: Just60 (atmega32u4)
* Hardware Availability: https://item.taobao.com/item.htm?id=564176654249

Make example for this keyboard (after setting up your build environment):

    make ydkb/just60:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
