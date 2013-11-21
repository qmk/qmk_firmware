GH60 keyboard firmware
======================
DIY compact keyboard designed and run by komar007 and Geekhack community.

## Threads on Geekhack.org
- [Prototyping](http://geekhack.org/index.php?topic=34959.0)
- [Beta-test](http://geekhack.org/index.php?topic=37570.0)


## Build
Move to this directory then just run `make` like:

    $ make

Use `make -f Makefile.pjrc` if you want to use PJRC stack but I find no reason to do so now.


## Keymap
Several version of keymap are available; `plain`, `poker_bit`, `poker_set`, `hasu` and `poker`(default). See keymap document(you can find in README.md of top) and `keymap_*.c` to define your own favourite keymap.

    $ make KEYMAP=[poker|plain|poker_set|poker_bit|hasu]

### 1. Plain keymap
Even without any Fn layer. This will be useful if you want to use key mapping tool like AHK.

See [keymap_plain.c](keymap_plain.c) for detail.

#### 1.0 Plain Default Layer
    ,-----------------------------------------------------------.
    |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
    |-----------------------------------------------------------|
    |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
    |-----------------------------------------------------------|
    |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
    |-----------------------------------------------------------|
    |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
    |-----------------------------------------------------------|
    |Ctrl|Gui |Alt |      Space             |Alt |Gui |App |Ctrl|
    `-----------------------------------------------------------'

### 2  Poker keymap

[keymap_poker.c](keymap_poker.c) emulates original Poker layer emulation.
[keymap_poker_bit.c](keymap_poker_bit.c) and [keymap_poker_set.c](keymap_poker_set.c) offers better support of Esc and arrow like:

    Fn + Esc = `
    Fn + {left, down, up, right}  = {home, pgdown, pgup, end}

 `poker` keymap supports Colemak, Dvorak and Workmans, use `Magic` + {`1`, `2`, `3`} to switch and `Magic` + `0` to return to Qwerty, where `Magic` is `LShift` + `RShift`.

#### 2.0 Poker Default Layer
    ,-----------------------------------------------------------.
    |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
    |-----------------------------------------------------------|
    |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
    |-----------------------------------------------------------|
    |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
    |-----------------------------------------------------------|
    |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
    |-----------------------------------------------------------|
    |Ctrl|Gui |Alt |      Space             |Fn  |Gui |App |Ctrl|
    `-----------------------------------------------------------'

#### 2.1 Poker Fn Layer
    ,-----------------------------------------------------------.
    |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|       |
    |-----------------------------------------------------------|
    |     |FnQ| Up|   |   |   |   |   |   |Cal|   |Hom|Ins|     |
    |-----------------------------------------------------------|
    |      |Lef|Dow|Rig|   |   |Psc|Slk|Pau|   |Tsk|End|        |
    |-----------------------------------------------------------|
    |        |Del|   |Web|Mut|VoU|VoD|   |PgU|PgD|Del|   Up     |
    |-----------------------------------------------------------|
    |    |    |    |         FnS            |Fn  |Left|Down|Righ|
    `-----------------------------------------------------------'



### 3. Hasu keymap
This is my keymap with HHKB, Vi cursor and Mousekey layer. See [keymap_hasu.c](keymap_hasu.c) for detail.

#### 3.0 Funky Default Layer
    ,-----------------------------------------------------------.
    |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
    |-----------------------------------------------------------|
    |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
    |-----------------------------------------------------------|
    |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|*L3|  '|Return  |
    |-----------------------------------------------------------|
    |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|*L2|Shift     |
    |-----------------------------------------------------------|
    |Ctrl|Gui |Alt |      Space             |Alt |*L3 |*L3 |*L1 |
    `-----------------------------------------------------------'

#### 3.1 Funky HHKB mode
    ,-----------------------------------------------------------.
    |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |
    |-----------------------------------------------------------|
    |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Inser|
    |-----------------------------------------------------------|
    |Contro|VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
    |-----------------------------------------------------------|
    |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift     |
    |-----------------------------------------------------------|
    |Ctrl|Gui |Alt |      Space             |Alt |Gui |App |*L0 |
    `-----------------------------------------------------------'

#### 3.2 Funky Vi mode
    ,-----------------------------------------------------------.
    |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Backsp |
    |-----------------------------------------------------------|
    |Tab  |Hom|PgD|Up |PgU|End|Hom|PgD|PgU|End|   |   |   |     |
    |-----------------------------------------------------------|
    |Contro|   |Lef|Dow|Rig|   |Lef|Dow|Up |Rig|   |   |Return  |
    |-----------------------------------------------------------|
    |Shift   |   |   |   |   |   |Hom|PgD|PgU|End|*L0|Shift     |
    |-----------------------------------------------------------|
    |Ctrl|Gui |Alt |      Space             |Alt |Gui |App |Ctrl|
    `-----------------------------------------------------------'

#### 3.3 Funky Mouse mode
    ,-----------------------------------------------------------.
    |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Backsp |
    |-----------------------------------------------------------|
    |Tab  |MwL|MwD|McU|MwU|MwR|MwL|MwD|MwU|MwR|   |   |   |     |
    |-----------------------------------------------------------|
    |Contro|   |McL|McD|McR|   |McL|McD|McU|McR|*L0|   |Return  |
    |-----------------------------------------------------------|
    |Shift   |   |   |Mb1|Mb2|Mb3|Mb2|Mb1|   |   |   |Shift     |
    |-----------------------------------------------------------|
    |Ctrl|Gui |Alt |      Space             |Alt |*L0 |*L0 |Ctrl|
    `-----------------------------------------------------------'
    Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
