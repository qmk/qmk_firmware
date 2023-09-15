# dlip's Taipo Layout Implementation

QMK implementation of the [Taipo](https://inkeys.wiki/en/keymaps/taipo) layout.

## Features

- Supports modifier holds: If you hold the modifier it becomes a hold rather than a one shot key, this allows you to press keys on the other side or use the mouse eg. shift + click
- Multiple modifier combos: Rather than having to press each separetely eg. ctrl, then alt, you can combine the combo into a single keypress.

## Modifications

- Inner and outer thumbs are flipped since I find space to be more natural on the outer thumb
- Uses extra keybindings which use both thumb keys together
- Fn layer key switched to 'insert'
- Adds alternate mappings for ''' and ';' since my ring and pinkie fingers don't get along

## Layout

The input is the combo you would press from the perspective of the right hand (left hand is mirrored). Output is the result when you press the combo by itself, while outer/inner is the result when combined with the inner/outer thumb keys, and both is for both thumb keys together.

```
Input Output Outer Inner Both
#---  r      R     >     Print Screen
----

-#--  s      S     }     Brightness Up
----

--#-  n      N     ]     Brightness Down
----

---#  i      I     )     Play/Pause
----

----  a      A     <     Next Track
#---

----  o      O     {     Volume Up
-#--

----  t      T     [     Volume Down
--#-

----  e      E     (     Previous Track
---#

----  c      C     1     F1
-#-#

----  u      U     2     F2
-##-

----  q      Q     3     F3
#-#-

----  l      L     4     F4
##--

--##  y      Y     5     F5
----

-#-#  f      F     6     F6
----

-##-  p      P     7     F7
----

#-#-  z      Z     8     F8
----

##--  b      B     9     F9
----

----  h      H     0     F10
--##

----  d      D     @     F11
#--#

#--#  g      G     #     F12
----

#---  x      X     ^     Cut
--#-

---#  k      K     +     Copy
-#--

-#--  v      V     *     Paste
---#

--#-  j      J     =     Undo
#---

#---  m      M     $
---#

---#  w      W     &
#---

-#--  /      \     |
--#-

--#-  -      _     %
-#--

---#  ?      !
--#-

--#-  ,      .     ~
---#

#---  ;      :
-#--

----  ;      :
###-

-#--  '      "     `
#---

###-  '      "     `
----

-###  Tab    Del   Ins
----

----  Enter  Esc   AltGr
-###

#---  Gui    Right PgUp Layer 3
#---

-#--  Alt    Up    Home Layer 2
-#--

--#-  Ctrl   Down  End  Layer 1
--#-

---#  Shift  Left  PgDn Layer 0
---#
```

## Usage in keymap

Add to `rules.mk`

```c
USER_NAME := dlip
TAIPO_ENABLE = yes
```

Add to `config.h`

- TAIPO_TAP_TIMEOUT: The length of time in ms you need to press and release a key to be considered a tap, this mostly affects oneshot mods since they only activate on a tap
- ONESHOT_TIMEOUT: The length of time in ms you have to press a key after a oneshot mod before it deactivates

```c
#define TAIPO_TAP_TIMEOUT 150
#define ONESHOT_TIMEOUT 500
```

Add to `keymap.c`:

- Include `dlip.h`

```c
#include "dlip.h"
```

- Add `_TAIPO` to your layers eg.

```c
enum layers {
  _BASE
  _TAIPO,
};
```

- Add layer to your `keymaps` with `TP_*` key mappings eg.

```c
    [_TAIPO] = LAYOUT_split_2x4_2(
       TP_TLP,        TP_TLR,    TP_TLM,       TP_TLI,          TP_TRI,     TP_TRM,     TP_TRR,     TP_TRP,
       TP_BLP,        TP_BLR,    TP_BLM,       TP_BLI,          TP_BRI,     TP_BRM,     TP_BRR,     TP_BRP,
                                 TP_LIT,       TP_LOT,          TP_ROT,     TP_RIT
    ),
```

- Add a layer switch key to your base layer eg. `TO(_TAIPO)`
- Add taipo calls in `process_record_user` and `matrix_scan_user` eg.

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_LAYER_ON(_TAIPO)) {
        return taipo_process_record_user(keycode, record);
    }  else {
        return true;
    }
};

void matrix_scan_user(void) {
    taipo_matrix_scan_user();
}
```