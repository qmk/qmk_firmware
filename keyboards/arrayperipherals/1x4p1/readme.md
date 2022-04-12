# [1x4] + 1 Macropad

![[1x4] + 1 Macropad](https://images.squarespace-cdn.com/content/v1/5f5e7d5dc43c166c56c0ae39/1606977576841-KIT0TOI6L3FO8FTS4ZHB/ke17ZwdGBToddI8pDm48kDk1dm1oSR9gCa1mX4KqzjN7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0luj0xCD0oh5KMc0gpox0u-wQWxfQHg04OxgQwaUq2yiAcNt5Kg2tE9yEtYfM4xwaw/DSC_0116.jpg)

A macropad with a 1x4 matrix array with an additional rotary that also functions as a button. [More info at arrayperipherals.com](https://www.arrayperipherals.com/)

* Keyboard Maintainer: [David Doan](https://github.com/daviddoan)
* Hardware Supported: Adafruit ItsyBitsy 32u4
* Hardware Availability: [arrayperipherals.com](https://www.arrayperipherals.com/)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Resetting macropad into bootloader mode.

The stock version of the macropad has bootmagic lite enabled. To trigger the bootloader, the first key (key furthest way from the rotary) needs to be held down when plugging the keyboard in. 
NOTE: Using bootmagic lite will always reset the EEPROM, so you will lose any settings that have been saved.
