KB Paradise V60 Type R Customised Layout by FollowingGhosts
======================

This is my custom layout for the Polestar Type R

## Keymap Notes
Supports Underglow lighting with RGB modifier keys and normal backlight
Selectable swap between Alt and OS keys which is stored in EEPROM
CAPSLOCK acts as FN when held
TAB acts as FN2 when held to provide a mouse layer with WASD and Q and E as left and right click respectively
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
   * |     |   |Up |RGB|RUp|BUp|GUp|   |Prt|Scl|Pau|Up|   | Ins  |
   * |-----------------------------------------------------------|
   * |      |Lft|Dwn|Rig|RdD|BlD|GrD|   |Hme|PgU|Lef|Rig|        |
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
   * |     | M1|MUP|M2 |   |   |   |   |   |   |   |    |   |    |
   * |-----------------------------------------------------------|
   * |       |ML |MDN|MR |   |   |   |   |   |   |    |   |      |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                         |    |    |   |    |
   *  -----------------------------------------------------------'
```
### Build
To build this keymap, simply run `make KEYMAP=FollowingGhosts`.
