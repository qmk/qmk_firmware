# Tandberg TDV 2200 Series
```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐ ┌───┬───┬───┐  ┌───┬───┬───┬───┐
│   │   │   │   │   │   │   │   │   │   │   │   │   │   │     │ │   │   │   │  │   │   │   │   │
└───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴─────┘ ├───┼───┼───┤  ├───┼───┼───┼───┤
                                                                │   │   │   │  │   │   │   │   │
┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ├───┼───┼───┤  ├───┼───┼───┼───┤
│     │   │   │   │   │   │   │   │   │   │   │   │   │   │   │ │   │   │   │  │   │   │   │   │
├───┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┼───┼───┤  ├───┼───┼───┼───┤
│   │   │   │   │   │   │   │   │   │   │   │   │   │   │     │ │   │   │   │  │   │   │   │   │
├───┼───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┴┬──┴┬──┴┬──┴┬──┴─┬───┤ ├───┼───┼───┤  ├───┼───┼───┼───┤
│   │    │   │   │   │   │   │   │   │   │   │   │   │    │   │ │   │   │   │  │   │   │   │   │
├───┴──┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤   │ ├───┼───┼───┤  ├───┼───┼───┼───┤
│      │   │   │   │   │   │   │   │   │   │   │   │      │   │ │   │   │   │  │   │   │   │   │
└──────┴───┴───┼───┴───┴───┴───┴───┴───┴───┴───┼───┴──────┴───┘ ├───┼───┼───┤  ├───┴───┼───┤   │
               │                               │                │   │   │   │  │       │   │   │
               └───────────────────────────────┘                └───┴───┴───┘  └───────┴───┴───┘
```
The TDV 2200 was a series of computer terminals developed by Tandberg in the
late 1970s.

* Keyboard Maintainer: [OleVoip](https://github.com/OleVoip)
* Hardware Supported: Keyboards of the Tandberg TDV 2200 terminal series and 
  similar Siemens keyboards, eg, MTS-2000.
* Hardware Availability: vintage boards at ebay, jumble sales

## How to build the software

Make example for this keyboard (after setting up your build environment):

    make siemens/tdv2200:default

Flashing example for this keyboard:

    make siemens/tdv2200:default:flash

See the
[build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the
[make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
for more information.or

Brand new to QMK? Start with our
[Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Plug-in reset**: Hold down any key of column 0 (typically the one with
  `ESC`, `TAB`, `CAPS`, `\`) and plug in the keyboard
* **Physical reset button**: Open the keyboard case and briefly press the
  button on the controller.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
