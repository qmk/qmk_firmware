# Let's Split the Atreus

This keymap is a port of the Atreus keymap to the Let's Split keyboard, using a
similar method of handling layer switches as the `default` keymap.


# Layers

The following tables are the layers as implemented.

### Underscores in Layer

Any underscore represents a key that is mapped to `KC_NO`, or no keypress. The
2x3 block in the middle is like this because the Atreus does not have any keys
there. It has been left blank for the user to add her own special keypresses or
macros that she finds useful to have on that particular layer.


## `_QWERTY`

```c
/*
 *  q   w   e    r    t    _    _    y   u   i  o   p
 *  a   s   d    f    g    _    _    h   j   k  l   ;
 *  z   x   c    v    b    _    _    n   m   ,  .   /
 * esc tab gui shift bksp ctrl alt space fn  -  ' enter
 */
 ```


## `_LOWER`

```c
/*
 *  !       @     up     {    }    _     _  pgup    7     8     9    *
 *  #     left   down  right  $    _     _  pgdn    4     5     6    +
 *  [       ]      (     )    &    _     _    `     1     2     3    \
 * lower  insert  gui  shift bksp ctrl  alt space   fn    .     0    =
 */
 ```

## `_RAISE`

```c
/*
 * insert home   up   end  pgup   _     _   up     F7    F8    F9   F10
 *  del   left  down right pgdn   _     _  down    F4    F5    F6   F11
 *   _   volup    _    _   reset  _     _          F1    F2    F3   F12
 *   _   voldn super shift bksp  ctrl  alt space   L0  prtsc scroll pause
 */
 ```
