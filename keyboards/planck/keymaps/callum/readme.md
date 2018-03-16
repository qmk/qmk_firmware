# callum’s planck layout

This is a layout for the grid planck, built with a few ideals in mind:

- Consistent and minimal response times should be maintained. Keys that react
  differently depending on whether they are tapped or held, keys that react
  differently if they are double tapped, etc. should be avoided -- they
  inevitably send their keycode later than a normal key -- interrupting the
  immediate feedback from the screen. Therefore we restrict ourselves to
  chording as our only means of getting more than one symbol out of a single
  physical key.

- The hands should never need to leave the home position. The usual culprit for
  this is the arrow cluster, so the arrow cluster should be as close to home as
  possible.

- There should be two of every modifier (one on each side), otherwise certain
  long key combinations become hard to make.

Keys are arranged as follows. Blank keys below may actually contain
undocumented shortcuts specific to my workflow. The base layer can be set to
colemak or qwerty (from the function layer).

```
/* COLEMAK
 * ,-----------------------------------------------------------------------.
 * |Tab  |  Q  |  W  |  F  |  P  |  G  |  J  |  L  |  U  |  Y  |  ;  |  -  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |Bksp |  A  |  R  |  S  |  T  |  D  |  H  |  N  |  E  |  I  |  O  |  '  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |Shift|  Z  |  X  |  C  |  V  |  B  |  K  |  M  |  ,  |  .  |  /  |Shift|
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |FUNC |Super| Alt |Ctrl |SYMB |Enter|Space|MOVE |Ctrl | Alt |Super|FUNC |
 * `-----------------------------------------------------------------------'
 */

/* QWERTY
 * ,-----------------------------------------------------------------------.
 * |Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  -  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |Bksp |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |Shift|  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |Shift|
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |FUNC |Super| Alt |Ctrl |SYMB |Enter|Space|MOVE |Ctrl | Alt |Super|FUNC |
 * `-----------------------------------------------------------------------'
 */

/* SYMB
 * ,-----------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |     |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * | Del |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |     |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     |  ~  |  `  |  +  |  =  |  |  |  \  |  [  |  ]  |  {  |  }  |     |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     |     |     |     |     |     |     |
 * `-----------------------------------------------------------------------'
 */

/* MOVE
 * ,-----------------------------------------------------------------------.
 * |     |     |     |     |     |     |     |Home | Up  | End |     | Esc |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     |     |Left |Down |Right|Caps | Del |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     |     |PgDn |PgUp |     |     |     |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     |     |     |     |     |     |     |
 * `-----------------------------------------------------------------------'
 */

/* FUNC
 * ,-----------------------------------------------------------------------.
 * |Reset| F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 |VolUp|
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |Power| F11 | F12 | F13 | F14 | F15 | F16 | F17 | F18 | F19 | F20 |VolDn|
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     | F21 | F22 | F23 | F24 |     |     |     |     |COLMK|QWRTY|     |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |Prev |Mute |Play |Next |     |     |     |     |
 * `-----------------------------------------------------------------------'
 */
 ```
