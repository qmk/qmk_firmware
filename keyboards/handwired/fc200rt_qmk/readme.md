# fc200rt_qmk

![fc200rt_qmk](https://imgur.com/UWKdIcZ)
![fc200rt_qmk_inside](https://imgur.com/0d8U8NE)
A Leopold FC200RT rewired with Teensy 2.0

Uses original row and column matrix, so you can wire the teensy 2.0 to the corrosposnding column and row numbers and flash this firmware to the teensy.

Pinout of Leopold's matrix:

|    | c0   | c1  | c2   | c3 | c4 | c5 | c6   | c7  | c8   | c9   | c10  | c11  | c12  | c13  | c14  | c15  |
|----|------|-----|------|----|----|----|------|-----|------|------|------|------|------|------|------|------|
| r0 | PAUS | Q   | W    | E  | R  | U  | I    | O   | P    | SLCK |      |      |      |      |      |      |
| r1 | LGUI | TAB | CAPS | F3 | T  | Y  | RBRC | F7  | LBRC |      | BSPC |      |      |      |      | LSFT |
| r2 |      | A   |      | D  | F  | J  | K    | L   | SCLN | RGUI | BSLS |      |      |      |      | RSFT |
| r3 |      | ESC | X    | F4 | G  | H  | F6   |     | QUOT | LALT | F11  | SPC  |      |      | UP   |      |
| r4 |      | Z   |      | C  | V  | M  | COMM | DOT |      |      | ENT  |      |      |      |      |      |
| r5 |      |     |      |    | B  | N  |      | APP | SLSH | RALT | F12  | DOWN | RGHT |      | LEFT |      |
| r6 | LCTL | GRV | F1   | F2 | 5  | 6  | EQL  | F8  | MINS |      | F9   | DEL  | INS  | PGUP | HOME |      |
| r7 | F5   | 1   | 2    | 3  | 4  | 7  | 8    | 9   | 0    | PSCR | F10  |      |      | PGDN | END  |      |
|    |      |     |      |    |    |    |      |     |      |      |      |      |      |      |      |      |

Choose any key from the corrosponding row and column and solder it to the pin on the Teensy listed in the firmware config.h

_NOTE: Some of the keys had mislabled columns and rows, so make sure the columns are all connected without diodes to one another, and that the rows are soldered after the diode_

* Keyboard Maintainer: [NaCly](https://github.com/Na-Cly)
* Hardware Supported: The PCBs, controllers supported
* Hardware Availability: Leopold FC200RT + Teensy 2.0

Make example for this keyboard (after setting up your build environment):

    make fc200rt_qmk:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
