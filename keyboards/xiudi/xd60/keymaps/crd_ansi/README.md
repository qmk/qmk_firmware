# ANSI Layout

This is the standard ANSI keymap that I use on all of my 60% boards. This keymap
includes a single function layer available by holding the designated key on the
bottom row.

I don't ever use Caps Lock, so that keycode is not mapped anywhere. In place of
the usual Caps Lock key, I have the following bnehaviour encoded: Escape when tapped
and Control when held.

I also have the bottom right mod cluster mapped to navigational direction keys when tapped.
Shift = Up, Alt = Down, Ctrl = Right, Fn = Left. When held, these keys send the usual modifier
signals.

```
/* Base layer
 * ,-----------------------------------------------------------------------------------------.
 * |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | Backspace |
 * |-----------------------------------------------------------------------------------------+
 * |  Tab   |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
 * |-----------------------------------------------------------------------------------------+
 * | Esc/Ctrl|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * |   Shift   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  ?  |  Shift          |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl |  Alt  |  Cmd  |               Space               |  Cmd  |  Fn  |  Alt  |  Ctrl |
 * `-----------------------------------------------------------------------------------------'
 */
```

While holding the function key, you have access to the following layout. Any key
not indicated is considered "transparent" and sends the signal indicated in the
layer below. This function later gets you dedicated access to Escape and Delete
keys, function keys on numbers, WASD directions, other navigation, multimedia
controls, RGB (underglow) controls, and firmware reset (DFU mode).

```
/* Fn layer
 * ,-----------------------------------------------------------------------------------------.
 * | Esc | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |  Del      |
 * |-----------------------------------------------------------------------------------------+
 * |        | Home|  Up | End |     |     |     |     | Mute|     |     | Pg+ | Pg- | Reset  |
 * |-----------------------------------------------------------------------------------------+
 * |         | Left| Down|Right|     |     |     |Brt- |Vol- |Vol+ |Brt+ |     |  RGB Toggle |
 * |-----------------------------------------------------------------------------------------+
 * |           |     |     |     |     |     |     |     |R(Bt-)|R(Bt+)|R(Rot)|              |
 * |-----------------------------------------------------------------------------------------+
 * |      |       |       |                                   |       |      |       |       |
 * `-----------------------------------------------------------------------------------------'
 */

```