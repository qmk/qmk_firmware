# Default keymap (W17PAD)

A 17-key numpad with a second control layer for the RGB matrix.

```
Layer 0 (base - numpad)
.-------------------.
|NL |  / |  * |  -  |
|-----+----+----+----|
|  7 |  8 |  9 |     |
|-----+----+----|  + |
|  4 |  5 |  6 |     |
|-----+----+----+----|
|  1 |  2 |  3 |     |
|-----+----+----|Ent |
|  0      . |     |
'-------------------'
```

* `NL` = `LT(1, KC_NUM)` — tap = Num Lock, hold = layer 1.

```
Layer 1 (RGB control)
.-------------------.
|TRNS|TG |NC |NP |   |
|-----+----+----+----|
| HU | HD |   |      |
|-----+----+----|    |
| SU | SD |   |TRNS |
|-----+----+----+----|
| VU | VD |   |      |
|-----+----+----|    |
| SPD  SPD |   |     |
'-------------------'
```

* `RM_HUEU/HUED/SATU/SATD/VALU/VALD` adjust the RGB matrix color.
* `RM_SPDU/RM_SPDD` adjust animation speed, `RM_NEXT/RM_PREV` cycle effects,
  `RM_TOGG` toggles the matrix on/off.
