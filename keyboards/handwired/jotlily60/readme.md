# jotlily60

![jotlily60](https://i.imgur.com/I68WGmJh.jpg)

A split keyboard kit made by jotix, inspired in the Lily58 keyboard.

* Keyboard Maintainer: [jotix](https://github.com/jotix)
* Hardware Supported: Arduino Pro Micro

---

### Arduino Pro Micro Pinout

| Rows        | 0  | 1  | 2  | 3  | 4  |
|-------------|----|----|----|----|----|
| Arduino pin | A0 | 15 | 14 | 16 | 10 |
| QMK pin     | F7 | B1 | B3 | B2 | B6 |

| Columns     | 0  | 1  | 2  | 3  | 4  | 5  | 6  |
|-------------|----|----|----|----|----|----|----|
| Arduino pin |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
| QMK pin     | D0 | D4 | C6 | D7 | E6 | B4 | B5 |

| Serial      |     |
|-------------|-----|
| Arduino pin | TX0 |
| QMK pin     |  D3 |

---

### Compiling the Firmware

Compile example for this keyboard (after setting up your build environment):
    
    qmk compile -kb handwired/jotlily60 -km default 
   
---

### The Defaukt Keymap

    +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
    |   =   |   1   |   2   |   3   |   4   |   5   |               |   6   |   7   |   8   |   9   |   0   |   -   |
    +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
    |  esc  |   Q   |   W   |   E   |   R   |   T   |               |   Y   |   U   |   I   |   O   |   P   |  tab  |
    +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
    | caps  |   A   |   S   |   D   |   F   |   G   |               |   H   |   J   |   K   |   L   |   ;   |   '   |
    +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    | shift |   Z   |   X   |   C   |   V   |   B   |   {   |   }   |   N   |   M   |   ,   |   .   |   /   | enter |
    +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
                    |  alt  | super |  ctrl | space |   fn  |   fn  | bspc  |  del  |  meh  |  ralt |
                    +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+

---

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
