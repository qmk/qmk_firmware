# Metadot Das Keyboard 4

![](https://i.imgur.com/jpriz4t.jpeg)

An unofficial QMK port of the Metadot Das Keyboard 4 (Professional, Professional for
Mac, and Ultimate), based on the onboard NUC123 microcontroller.
The hardware is identical across variants; the keymaps account for macOS vs Windows
and Ultimate's blank keycaps.

* Keyboard Maintainer: [Giuseppe Iannello](https://github.com/giannello)
* Hardware Supported: Das Keyboard 4 (NUC123SD4AN0 onboard MCU)
* Hardware Availability: <https://www.daskeyboard.com/daskeyboard-4-professional>

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb metadot/das_keyboard_4 -km default

Flashing example for this keyboard:

    qmk flash -kb metadot/das_keyboard_4 -km default

See the [build environment setup](getting_started_build_tools) and the
[make instructions](getting_started_make_guide) for more information. Brand new to
QMK? Start with our [Complete Newbs Guide](newbs).

## Layouts

Two keymaps ship with this keyboard:

* `default` — Windows layout.
* `macos_metadot` — Windows layout with the Win/Alt (and Right Alt/Win) keys swapped
  so the modifier order matches a Mac keyboard: `[Ctrl][Option][Cmd]`.

Both layouts map the `Escape`+`1`+`a` combo to QK_BOOT. This is the same combination
of keys used to enter the bootloader when powering-on the keyboard.

## Encoder

The volume knob supports rotation only (it cannot be pressed). Rotate for volume up/down.

## Bootloader

The board ships from the factory with the `hyisp` bootloader already installed.
To interact with it, install [hyisp-util](https://github.com/giannello/hyisp-util):

    pip install hyisp-util

Enter the bootloader by holding `Esc`, `1`, and `a` together and plugging in
the keyboard.

Flashing is performed with `hyisp-util` (`PROGRAM_CMD` in `rules.mk`).
