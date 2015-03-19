ADB to USB keyboard converter
=============================
This firmware converts ADB keyboard protocol to USB.
You can use PJRC Teensy for this converter, though, other USB AVR(ATMega32U4, AT90USB64/128 or etc) should work.
But binary size is about 10KB or more it doesn't fit into 8K flash like ATMega8U2.

Discuss: http://geekhack.org/showwiki.php?title=Island:14290


Wiring
------
0. Connect ADB keyboard to Teensy by 3 lines(Vcc, GND, Data). By default Data line uses port PD0.
   This converter uses AVR's internal pull-up, but it seems to be too weak, in particular when you want to use a long or coiled cable.
   The external pull-up resistor(1K-10K Ohm) on Data is strongly recommended.
1. Define following macros for ADB connection in config.h if you use other than port PD0.
   ADB_PORT, ADB_PIN, ADB_DDR, ADB_DATA_BIT
2. make
3. program Teensy


Build
-----
Just make

    $ make clean
    $ make

If your keyboard is ISO layout

    $ make KEYMAP=iso


LOCKING CAPSLOCK
----------------
Many of old ADB keyboards have mechanical push-lock switch for Capslock key and this converter supports the locking Capslock key by default. See README in top directory for more detail about this feature.

Also you may want to remove locking pin from the push-lock switch to use capslock as a normal momentary switch.
http://www.youtube.com/watch?v=9wqnt2mGJ2Y


Keymap
------
You can change a keymap by editing code of keymap.c like following.
This is a keymap for AEK, however, also used for other keyboards.
How to define the keymap is probably obvious. You can find key symbols in keycode.h.
If you want to define some keymaps than just one, see hhkb/keymap.c and
macway/keymap.c as examples. Keymap(layer) switching may needs a bit of
effort at this time.

    /* Default Layer: plain keymap
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.             ,---.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|             |Pwr|
     * `---'   `---------------' `---------------' `---------------' `-----------'             `---'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa| |Ins|Hom|PgU| |NmL|  =|  /|  *|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD| |  7|  8|  9|  -|
     * |-----------------------------------------------------------| `-----------' |---------------|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |               |  4|  5|  6|  +|
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
     * |Ctrl |Alt |Gui |         Space             |Gui |Alt |Ctrl | |Lef|Dow|Rig| |      0|  .|   |
     * `-----------------------------------------------------------' `-----------' `---------------'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,                    PWR,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,EQL, PSLS,PAST,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,  PMNS,
    LCAP,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                                              LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),


Magic command
-------------
To get help press `h` holding Magic key. Magic key is `Power key`.


Notes
-----
Not-extended ADB keyboards have no discrimination between right modifier and left one,
you will always see left control even if you press right control key.
Apple Extended Keyboard and Apple Extended Keyboard II can discriminate both side
modifiers except for GUI key(Windows/Command).

And most ADB keyboard has no diodes in its matrix so they are not NKRO,
though ADB protocol itself supports it. See protocol/adb.c for more info.

If keyboard has ISO layout you need to use ISO keymap with `make KEYMAP=iso`. With ANSI
keymap you will suffer from swapped keys problem.

https://github.com/tmk/tmk_keyboard/issues/35

EOF
