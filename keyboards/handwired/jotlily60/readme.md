# jotlily60

![Jotanck](https://i.imgur.com/bBfO4L2.jpg)

A split keyboard kit made by jotix, inspired in the Lily58 keyboard.

Keyboard Maintainer: [jotix](https://github.com/jotix)
Hardware Supported: Arduino Pro Micro

### Arduino Pro Micro Pinout

| Rows        | 0  | 1  | 2  | 3  | 4  |
|-------------|----|----|----|----|----|
| Arduino pin | 6  | 7  | 10 | 16 | 16 |
| QMK pin     | D7 | E6 | B6 | B2 | B2 |

| Columns     | 0  | 1  | 2  | 3  | 4  | 5  | 6   |
|-------------|----|----|----|----|----|----|-----|
| Arduino pin | A3 | A2 | A1 | A0 | 15 | 14 | TX0 |
| QMK pin     | F4 | F5 | F6 | F7 | B1 | B3 | D3  |

### Compiling the Firmware

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb handwired/jotlily60 -km default
   
    # for VIA support
    qmk compile -kb handwired/jotlily60 -km via

### The Defaukt Keymap

![Default Keymap](https://i.imgur.com/xh7Dmd7.png)

To reset the keyboard press Lower+Raise+Q

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
