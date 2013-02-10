GH60 keyboard firmware
======================
DIY compact keyboard designed and run by komar007 and Geekhack community.

## Threads on Geekhack.org
- [Prototyping](http://geekhack.org/index.php?topic=34959.0)
- [Beta-test](http://geekhack.org/index.php?topic=37570.0)


## Build
Move to this directory then just run `make` like:

   $ make -f Makfile.pjrc


## Keymap
See keymap.c to define your own favourite keymap.

###Keymap with funky layers.
    Layer 0: Default Layer
    ,-----------------------------------------------------------.
    |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
    |-----------------------------------------------------------|
    |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
    |-----------------------------------------------------------|
    |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Return  |
    |-----------------------------------------------------------|
    |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift     |
    |-----------------------------------------------------------|
    |Ctrl|Gui |Alt |      Space             |Alt |Gui |App |Fn1 |
    `-----------------------------------------------------------'

    Layer 1: HHKB mode
    ,-----------------------------------------------------------.
    |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |
    |-----------------------------------------------------------|
    |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Inser|
    |-----------------------------------------------------------|
    |Contro|VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
    |-----------------------------------------------------------|
    |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift     |
    |-----------------------------------------------------------|
    |Ctrl|Gui |Alt |      Space             |Alt |Gui |App |xxx |
    `-----------------------------------------------------------'

    Layer 2: Vi mode
    ,-----------------------------------------------------------.
    |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Backsp |
    |-----------------------------------------------------------|
    |Tab  |Hom|PgD|Up |PgU|End|Hom|PgD|PgU|End|   |   |   |     |
    |-----------------------------------------------------------|
    |Contro|   |Lef|Dow|Rig|   |Lef|Dow|Up |Rig|   |   |Return  |
    |-----------------------------------------------------------|
    |Shift   |   |   |   |   |   |Hom|PgD|PgU|End|xxx|Shift     |
    |-----------------------------------------------------------|
    |Ctrl|Gui |Alt |      Space             |Alt |Gui |App |Ctrl|
    `-----------------------------------------------------------'

    Layer 3: Mouse mode
    ,-----------------------------------------------------------.
    |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Backsp |
    |-----------------------------------------------------------|
    |Tab  |MwL|MwD|McU|MwU|MwR|MwL|MwD|MwU|MwR|   |   |   |     |
    |-----------------------------------------------------------|
    |Contro|   |McL|McD|McR|   |McL|McD|McU|McR|xxx|   |Return  |
    |-----------------------------------------------------------|
    |Shift   |   |   |Mb1|Mb2|Mb3|Mb2|Mb1|   |   |   |Shift     |
    |-----------------------------------------------------------|
    |Ctrl|Gui |Alt |      Space             |Alt |Gui |xxx |Ctrl|
    `-----------------------------------------------------------'
    Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 

### Plain keymap without Fn layer.
This will be useful if you want to use key mapping tool like AHK.
To get this plain keymap run:

    $ make -f Makefile.pjrc plain

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
