KB Paradise V60 Type R Customised Layout by FollowingGhosts
======================

This is my custom keymap for the Polestar Type R

## Keymap Notes
Supports Underglow lighting with RGB modifier keys and normal backlight
Selectable swap between Alt and OS keys which is stored in EEPROM
CAPSLOCK acts as FN when held/equivalent to MO1
TAB acts as FN2 when held to provide a mouse layer with WASD and Q and E as left and right click respectively
LShift and RShift have Space Cadet Shift enabled

RGB colour setting is set to HSV to bring it in line with (QMK docs)([https://beta.docs.qmk.fm/features/feature_rgblight])
R+/R- are hue, G+/G- are saturation and B+/B- are value

```
 Keymap 0: Default/Windows Layer (Qwerty)
 * ,-----------------------------------------------------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|   Bs  |
 * |-----------------------------------------------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
 * |-----------------------------------------------------------|
 * |CAP/MO1|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
 * |-----------------------------------------------------------|
 * |LShift  |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| RShift   |
 * |-----------------------------------------------------------|
 * |Ctrl|Gui |Alt |      Space              | MO1|Gui |App|Ctrl|
 *  -----------------------------------------------------------'


Keymap 1: FN Layer
   *  -----------------------------------------------------------.
   * |  | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|  Del  |
   * |-----------------------------------------------------------|
   * |     |   |Up |RGB|HUI|SAI|VAI|   |Prt|Scl|Pau|Up|   | Ins  |
   * |-----------------------------------------------------------|
   * |      |Lft|Dwn|Rig|HUD|SAD|VAD|   |Hme|PgU|Lef|Rig|        |
   * |-----------------------------------------------------------|
   * |        |BLD|BLT|BLI|   |VolD|VolU|Mut|End|PgD|Dwn|        |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |AGSW|    |    |
   * '-----------------------------------------------------------'

Mouse Layer
   M1 = Mouse Button 1
   M2 = Mouse Button 2
   WASD are Up Left Right Down respectively
   * ,-----------------------------------------------------------.
   * |   |   |    |   |   |   |   |   |   |   |   |    |    |    |
   * |-----------------------------------------------------------|
   * |     | M1|MUP|M2 |   |   |   |   |   |   |   |MPLY|   |    |
   * |-----------------------------------------------------------|
   * |       |ML |MDN|MR |   |   |   |   |   |   |MNXT|MPRV|     |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                         |    |    |   |    |
   *  -----------------------------------------------------------'
```
### Build
To build this keymap, simply run `make v60_type_r:followingghosts`.
