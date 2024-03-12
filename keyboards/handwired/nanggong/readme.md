# Nanggong

![nanggong](https://i.imgur.com/vky2f07h.jpeg)

Nanggong is a 63-key/60% handwired ortholinear keyboard built to fulfill my desire for an ortholinear layout while retaining important features such as arrow keys, numbers, and the standard 1.25u Ctrl key. This design caters to the needs of both programmers (with arrow keys) and gamers (featuring number keys and a 1.25u Ctrl size).

The keyboard is built using Arduino Pro Micro Atmega32u4 and QMK Firmware, and firmware has been built to support VIA Software so that this keyboard can manage the keys without having to re-flash and already supports underglow WS2812/WS2812b which can be controlled by VIA Software.

* Keyboard Maintainer: [nanggong](https://github.com/SanmaLD)
* Hardware Supported: Arduino Pro Micro

---

### Pin assignment
```sh
            0     1     2     3     4     5     6     7     8     9     10    11    12
   cols : ["B3", "B2", "B6", "B5", "D7", "E6", "B4", "C6", "D4", "D0", "D1", "D2", "D3"],
   rows : ["D5", "F5", "F6", "F7", "B1"]
```

---

### Compiling the Firmware

Compile example for this keyboard (after setting up your build environment):

    qmk compile -kb handwired/nanggong -km via 

---

### The Defaukt Keymap

* ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
* │ ESC │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │
* ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
* │ Tab │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │
* ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
* │ Cap │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │Enter│
* ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
* │Shift│  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │  ↑  │ Del │
* ├─────┴┬────┴──┬──┴────┬┴─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┼─────┤
* │ ctrl │  Win  │  Alt  │  FN  │   Space   │Prt s│  \  │Bck S│  ←  │  ↓  │  →  │
* └──────┴───────┴───────┴──────┴───────────┴─────┴─────┴─────┴─────┴─────┴─────┘


---

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).