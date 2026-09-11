# MKC75

A 75% keyboard sold by MyKeyClub, with a rotary encoder and a multi-layout
hotswap/solder PCB (split backspace, ISO enter, split left shift, and
6.25u / 7u / 3u-1u-3u bottom row options).

The default keymap populates every matrix position the PCB supports, so any
solder/hotswap variant works without further configuration.

* Keyboard Maintainer: [The QMK Community](https://github.com/qmk)
* Hardware Supported: MKC75 hotswap/solder PCB (STM32F072, 8 MHz HSE)
* Hardware Availability: previously via [MyKeyClub](https://www.mykeyclub.com/), no longer sold

Make example for this keyboard (after setting up your build environment):

    make mykeyclub/mkc75:default

Flashing example for this keyboard:

    make mykeyclub/mkc75:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical boot button**: hold the BOOT button on the PCB while plugging in
  the USB cable.
* **Keycode in layout**: assign a key to Reset (`QK_BOOT`) — for example via
  VIA — and press it.

Note: holding **Escape** while plugging in also enters the bootloader, but as
with the original firmware this first clears the stored keymap
(`eeconfig_disable()`), so prefer the BOOT button when you want to keep your
layout.

## Disclaimer

MyKeyClub has ceased trading and never released firmware sources for this
board, so this keyboard definition is community supported.

The reverse engineering and reconstruction behind this definition was assisted
by an LLM ([Qwen Code](https://github.com/QwenLM/qwen-code)).
