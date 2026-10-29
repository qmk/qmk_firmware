# MKC75

![MKC75](https://i.imgur.com/4YEE0JV.jpeg)

A 75% keyboard designed by MyKeyClub, with a multi-layout hotswap/solder PCB and a top-right slot that takes either a Home switch or a rotary encoder module.

* Keyboard Maintainer: [SEApodEErman](https://github.com/SEApodEErman)
* Hardware Supported: MKC75 hotswap/solder PCB (STM32F072, 8 MHz HSE)
* Hardware Availability: [MyKeyClub](https://www.mykeyclub.com/) (no longer sold — ceased trading, community supported)

Make example for this keyboard (after setting up your build environment):

    make mykeyclub/mkc75:default

Flashing example for this keyboard:

    make mykeyclub/mkc75:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: hold down the key at (0,0) in the matrix (Escape) while plugging in the keyboard. Note this also resets saved EEPROM settings to defaults (firmware in flash is retained, no re-flash needed).
* **Physical boot button**: hold the BOOT button on the PCB while plugging in the USB cable.
* **Keycode in layout**: press the key mapped to `QK_BOOT` (`Fn` + `Escape` in the default keymap).
