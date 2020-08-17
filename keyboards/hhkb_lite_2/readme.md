# HHKB Lite 2

![HHKB Lite 2](https://deskthority.net/wiki/images/e/ed/HHKB_Lite_2.jpg)

This is for the [HHKB Lite 2](https://deskthority.net/wiki/HHKB_Lite)
by PFU, identified by model numbers PD-KB200W/U or PD-KB200B/U. It
uses the replacement Teensy 2.0 board from [my other
project](https://github.com/thirteen37/HHKB-Lite-2-Teensy).

Make example for this keyboard (after setting up your build environment):

    make hhkb_lite_2:default

Flashing example for this keyboard:

    make hhkb_lite_2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Details

The `default` keymap is nearly the official standard US QWERTY, except
with the `Delete` key behaving like `BS`, which is as if DIP `SW3` is
set.

While there are two physical `Fn` keys on the keyboard, they are
electrically indistinguishable (same wiring matrix) so they can not be
assigned different keycodes.
