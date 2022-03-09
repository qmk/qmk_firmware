# sulrich crkbd layout

this is the personal keyboard layout of [@sulrich](https://github.com/sulrich),
and is heavily oriented towards operation in the Mac OS environment.

there are no LED rules in this keymap and the OLED display uses the default
corne images

## layout notes

this layout uses a standard QWERTY layout on the default layer followed by a
separate layer for symbols and numbers (and F-keys)

### thumb cluster: left

this contains the Mac OS modifier keys as well as the enter key.  these are
transparently mapped through the remaining layers with the exception of the
enter key which is toggled to backspace on the symbols layer.  

### thumb cluster: right

the largest right thumb button provides the space and the layer toggles.

### default layer
```text
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          TAB,       Q,       W,       E,       R,       T,                            Y,       U,       I,       O,      P,        \,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         LCTL,       A,       S,       D,       F,       G,                            H,       J,       K,       L,       ;,       ',
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         LSFT,       Z,       X,       C,       V,       B,                            N,       M,       ,,       .,       /,    RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             OPT,      CMD,   ENTER,        SPC,   MO(1),   MO(2)
                                      //`--------------------------'  `--------------------------'
```

### symbols layer [1]

this layer contains all of the standard symbols.  the arrow keys are mapped to
the default vi bindings for single character motion (h, j, k, l). 

```text
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          ESC,       !,       @,       {,       },       |,                            ^,       +,       =,       -,       *,        ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             ,       #,     $,         (,       ),       `,                         LEFT,    DOWN,      UP,   RIGHT,        ,   ENTER,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             ,       %,       ^,       [,       ],       ~,                            _,       &,       <,       >,      \,         ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             OPT,      CMD,  BSPACE,        SPC,   MO(1),   MO(2)
                                      //`--------------------------'  `--------------------------'
```

### number/media layer [2]

this layer has all of the numbers and the F-keys mapped to reasonably intuitive
locations.  additionally, media controls allow for quick access to volume and
track changes.

```text
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          ESC,      F1,      F2,      F3,      F4,      F5,                           F6,      F7,      F8,      F9,     F10,     F11,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             ,       1,       2,       3,       4,       5,                            6,       7,       8,       9,       0,     F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             ,    PREV,    PLAY,    NEXT,  VOL_DN,  VOL_UP,                             ,    MUTE,        ,        ,        ,        ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             OPT,      CMD,   ENTER,        SPC,   MO(1),   MO(2)
                                      //`--------------------------'  `--------------------------'

```

