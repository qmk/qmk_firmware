# czmao_DS17 NumberPad

A right-hand number pad keyboard with RGB matrix lighting.

* Keyboard Maintainer: [micahyy](https://github.com/micahyy)
* Hardware Availability: [Taobao](https://item.taobao.com/item.htm?ft=t&id=887677071508)

Make example for this keyboard (after setting up your build environment):

    make czmao/ds17:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Num Lock key and plug in the keyboard
* **Physical reset button**: Briefly short the reset pins on the back of the PCB
* **Keycode**: Press `FN` + `Num Lock` (if configured in keymap)

## Building

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Changelog

2026-01-11: Fixed LED initialization issue to prevent green light when plugged in after turning off