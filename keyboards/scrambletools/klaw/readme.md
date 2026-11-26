# KLAW

![KLAW](https://raw.githubusercontent.com/scrambletools/klaw/main/docs/images/klaw_top.png)

A 34-key reversible split keyboard derived from GEIGEIGEIST's KLOR. One PCB
serves both halves: the left build populates one face, the right build the
other. Each half has per-key RGB, an EC11 encoder with push switch, and a
0.96" OLED.

* Keyboard Maintainer: [Scramble Tools](https://github.com/scrambletools)
* Hardware Supported: KLAW PCB with a Pro Micro compatible controller, either
  an ATmega32U4 Pro Micro or a Pro Micro RP2040 such as the Adafruit KB2040
* Hardware Availability: [github.com/scrambletools/klaw](https://github.com/scrambletools/klaw)

Make example for this keyboard (after setting up your build environment):

    make scrambletools/klaw:default

For an RP2040 controller add the matching converter, for example:

    make scrambletools/klaw:default CONVERT_TO=kb2040

Flashing example for this keyboard:

    make scrambletools/klaw:default:flash

Nothing electrical tells the two halves apart, so the firmware keeps each
half's side in EEPROM (`EE_HANDS`). Flash each half once with the matching
split target so the side is stored:

    make scrambletools/klaw:default:uf2-split-left     # or avrdude-split-left
    make scrambletools/klaw:default:uf2-split-right    # or avrdude-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top pinky key of the half and plug it in
* **Physical reset button**: Press the reset button on the PCB (double tap
  with an RP2040 controller)
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Matrix

Rows `C6 D7 E6 B4`, columns `F7 B1 B3 B2 B6` from the pinky to the inner
column, diodes COL2ROW. The right half scans the same matrix and is exposed
as rows 4 to 7. Row 3 holds the two thumb keys (columns 1 and 2) and the
encoder push switch (column 4).

## Layouts

* `LAYOUT`: 36 positions, the 34 keys plus both encoder push switches
* `LAYOUT_split_3x5_2`: the 34 keys only, compatible with the `split_3x5_2`
  community layout

## OLED

Each half shows the name of the active layer for its own side, centred, at
twice the size of the built-in font. A keymap provides the names by
defining `layer_name_klaw(uint8_t layer, bool left)`; without it the layer
number is shown.
