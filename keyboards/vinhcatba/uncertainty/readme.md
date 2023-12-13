# uncertainty

![uncertainty](https://i.imgur.com/IKrn37Bh.jpeg)

*This is an open source keyboard with exposed-component design. It has 96% (1800) layout with extra 3 keys on the left for custom macro (default are Copy, Paste and open Calculator). It features OLED screen, RGB Backlight, Encoder and VIA-supported. Powered by a STM32F401 Blackpill.*

* Keyboard Maintainer: [Vinh Le](https://github.com/vinhcatba)
* Hardware Supported: The PCB is [here](https://github.com/vinhcatba/uncertainty), controller supported: STM32F401 Blackpill, SSD1306 128x32 OLED, WS2812B RGB, External EEPROM, Rotary Encoder.
* Hardware Availability: [Open-source hardware](https://github.com/vinhcatba/uncertainty)

Make example for this keyboard (after setting up your build environment):

    make vinhcatba/uncertainty:default

Flashing example for this keyboard:

    make vinhcatba/uncertainty:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset button**: On Blackpill board: Hold `NRST` and `BOOT0` -> Release `NRST` first and **quickly** release `BOOT0` right after.
* **Keycode in layout**: `QK_BOOT` is on the second layer, replacing Escape (top left key).
