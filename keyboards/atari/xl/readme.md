# atari_xl

![Atari XL layout](./keyxl.gif)

Atari pins are numbered 0-23 with 0 closest to back of machine.

matrix, row vs col:
```
P |     8 |  9 |  10 | 11 | 12 | 13 | 14 | 15 |  16 |
I |     0 |  1 |   2 |  3 |  4 |  5 |  6 |  7 |   8 |
-----------------------------------------------------
0 | BREAK |  7 |  [] |  8 |  9 |  0 |  < |  > | DEL |
1 |    [] |  6 |  [] |  5 |  4 |  3 |  2 |  1 | ESC |
2 |    [] |  U |  [] |  I |  O |  P |  - |  = | RET |
3 |    [] |  Y |  [] |  T |  R |  E |  W |  Q | TAB |
4 |  CTRL | F1 |   J |  K |  L |  ; |  + |  * |  F2 |
5 |    [] | [] |   H |  G |  F |  D |  S |  A | CAP |
6 |    [] |  N | SPC |  M |  , |  . |  / |  ◪|  [] |
7 | SHIFT | F3 | HLP |  B |  V |  C |  X |  Z |  F4 |
```

pin 18 on the kb is connected to nothing, maybe +5v
pin 23 on the kb is connected to + on the LED, probably +5v

there is a second direct "matrix" where individual switches are connected to ground (17):
```
 P |    19 |     20 |     21 |    22 |
 I |     0 |      1 |      2 |     3 |
17 | START | SELECT | OPTION | RESET |
```

Pins of the Pico board you should use by default:
```
--------------------------------------------------------
Rows:      0 1 2 3 4  5 6 7
GPIO Pins: 0 1 2 3 4 16 5 6
--------------------------------------------------------
Columns:   8 9 10 11 12 13 14 15 16
GPIO Pins: 7 8  9 10 11 12 15 13 14
--------------------------------------------------------
```
for now the above is excluding reset+option+select+start

Keyboard Maintainer: [moparisthebest](https://github.com/moparisthebest)
Hardware Supported: RPI Pico

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb atari/xl -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
