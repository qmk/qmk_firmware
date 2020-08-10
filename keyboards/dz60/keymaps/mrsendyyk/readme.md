# [Sendy YK](https://github.com/mrsendyyk)'s Keymap
---

## KBDfans DZ60 ANSI Arrow Layout

[dz60/dz60.h](https://github.com/qmk/qmk_firmware/blob/master/keyboards/dz60/dz60.h)

    #define LAYOUT_60_ANSI_Arrow_mrsendyyk

### Layer [0]

```
,-----------------------------------------------------------------------------------------.
| Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | Backspace |
|-----------------------------------------------------------------------------------------+
| Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
|-----------------------------------------------------------------------------------------+
|Caps Lock|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
|-----------------------------------------------------------------------------------------+
| L Shift    |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  R Shift | Up  |  /  |
|-----------------------------------------------------------------------------------------+
| L Ctr |  OS  | Alt  |              Space                  |R Alt|R Ctr|Left |Down |Right|
`-----------------------------------------------------------------------------------------'
```

### Layer [1]

(Press & Hold `R Ctr` Key)

```
,-----------------------------------------------------------------------------------------.
| ` ~ |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  Delete   |
|-----------------------------------------------------------------------------------------+
| Bri Up |     |     | End |Reset|     |     |     | Ins |     |Pr Sc|     |     | Eject  |
|-----------------------------------------------------------------------------------------+
| Bri Down|     |Sc L |     |     |     | Home|     |     |     |     |     |    Mute     |
|-----------------------------------------------------------------------------------------+
| Vol +      |     |     |Calc |     |     |Num L| Mail|     |     |          |Pg U |Pause|
|-----------------------------------------------------------------------------------------+
| Vol - | Rwd  | F Fd |                 Play               |M Stp |     |Prev |Pg D |Next |
`-----------------------------------------------------------------------------------------'
```

### Layer [2]

(Press & Hold `R Alt` Key)

```
,-----------------------------------------------------------------------------------------.
|     |     |     |     |     |     |     |     |     |     |     |     |     |           |
|-----------------------------------------------------------------------------------------+
|        |R Tog|R Mo+|Hue +|Hue -|Sat +|Sat -|Bri +|Bri -|     |     |     |     |        |
|-----------------------------------------------------------------------------------------+
|         |     |     |     |     |     |     |     |     |     |     |     |             |
|-----------------------------------------------------------------------------------------+
|            |     |     |     |BL - |B Tog|BL +|B Cyc|      |     |          |     |     |
|-----------------------------------------------------------------------------------------+
|       |      |      |                                    |      |     |     |     |     |
`-----------------------------------------------------------------------------------------'
```

## RGB Underglow as Caps Lock, Num Lock, and Layer Indicator

[dz60/keymaps/mrsendyyk/keymap.c](https://github.com/qmk/qmk_firmware/blob/master/keyboards/dz60/keymaps/mrsendyyk/keymap.c)

1. Caps Lock Indicator `rgblight_setrgb(255, 110, 0)`
2. Num Lock Indicator (Press & Hold `R Ctr` Key + Press `N` Key) `rgblight_setrgb(100, 255, 100)`
3. Layer Indicator `rgblight_setrgb(225, 8, 0)`

---

Make example for this keyboard (after setting up your build environment):

    make dz60:mrsendyyk
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
