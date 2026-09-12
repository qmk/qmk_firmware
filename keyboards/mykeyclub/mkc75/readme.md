# MKC75

![MKC75](https://i.imgur.com/4YEE0JV.jpeg)

A 75% keyboard sold by MyKeyClub, with a rotary encoder in the top-right corner
and a multi-layout hotswap/solder PCB.

Only one option from each group below can be populated on a single build:
split or 2u backspace, ANSI or ISO enter, 1.25u or 2.25u left shift, and
6.25u / 7u / 3u-1u-3u bottom rows. `LAYOUT_all` contains every switch position
at once and works for any build; the named layouts each describe one buildable
combination of the bottom row.

| Layout | Description |
|-------------------------------|---------------------------------------------------|
| `LAYOUT_all` | every switch position the PCB exposes (used by the default keymap) |
| `LAYOUT_75_ansi` | 6.25u space, 1.25u modifiers |
| `LAYOUT_75_ansi_7u_space` | 7u space, 1.5u modifiers |
| `LAYOUT_75_ansi_split_space` | 3u-1u-3u space, 1.5u modifiers |

All of the above are drawn with the ANSI enter, split backspace and 1.25u left
shift geometry. An ISO enter, 2u backspace or 2.25u left shift build uses the
same matrix cells, so it works with any of these layouts — only the rendered key
sizes differ, and positions your build does not populate simply stay unused.

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
