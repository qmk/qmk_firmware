jeebak's JD45 layout
=======================
NOTE: This is a port of jeebak's planck layout, for jd45.

This WIP keymap attempts to minimize fingers straying away from the home row.
To aid in this endeavor, when additional modifyer keys to switch layers are
needed, they will be mapped to home row keys. The `keymap.c` file will contain
the exact changes. The diagrams in this README shows the highlights of the
changes from the default mappings.

I also decided to change all calls to `persistant_default_layer_set()` to
`default_layer_set()` since this is my personal perference.

## Macros
```
#define ALT_TAB     M(KC_ALT_TAB)
```

## Base Layers (Qwerty/Colemak/Dvorak)
These base layers are mostly the same as the default mappings. The interesting
changes are shown below.

- The `Ctrl/Esc`, will emit an `Escape` when tapped, and act as a `Control` key when held,
- `GUI/;` as `;` and `GUI`,
- `Alt/"` as `"` and `Alt`,
- `Sft/Ent` as `Enter` and `Shift`, and
- `Hyper/Tab` as `Tab` and `Hyper`

A `TODO` item is to see if it can also act as a `CapsLock` when double-tapped.
The arrow keys, which have been moved to the
[TouchCursor](http://martin-stone.github.io/touchcursor/) layer, have been
replaced with the Media keys as shown. The `MC/kc` key activates the
`MouseCursor` layer when held, and emits the corresponding `kc` for its layer,
when tapped.
```
  ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
  |Hyper/Tab|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  | Bksp |
  |---------`------`------`------`------`------`------`------`------`------`------`------`------|
  | Ctrl/Esc |   A  |   S  | MC/D |   F  |   G  |   H  |   J  |   K  |   L  |GUI/; |   Alt/"    |
  |----------`------`------`------`------`------`------`------`------`------`------`------------|
  |   Shift   |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  Sft/Ent  |
  |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
  |   RGUI |  Alt  |  GUI  | Lower | TC/Space | TC/Space |  Raise  |  Vol-  |  Vol+  |   Play   |
   `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
```

## Lower Layer (Symbols and Function Keys)
The symbols and functions keys are essentially the same as the default mapping.
The most notable changes are that the symbol keys from the `RAISE` layer have
been moved here. The remaining Media keys replace those that are now on the
base layers. The `BACKLIT` key has also been moved here.
```
  ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
  |   ~     |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      | Bksp |
  |---------`------`------`------`------`------`------`------`------`------`------`------`------|
  |   [      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |   "|"      |
  |----------`------`------`------`------`------`------`------`------`------`------`------------|
  |   ]       |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   -  |   =  |   [  |   ]  |    \      |
  |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
  | Brite  |       |       |       |          |          |         |  Prev  |  Next  |   Mute   |
   `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
```

## Raise Layer (Numbers and Arithmetic Operators)
All of the numbers and arithmetic operators are available on this layer. Some
keys are duplicated for the convenience of their positions. The `0` and `$`
keys at the far left are for quick access to beginning and end of line in vim.
```
  ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
  |   0     |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      | Bksp |
  |---------`------`------`------`------`------`------`------`------`------`------`------`------|
  |   $      |   4  |   5  |   6  |   .  |   +  |   .  |   4  |   5  |   6  |   *  |   "|"      |
  |----------`------`------`------`------`------`------`------`------`------`------`------------|
  |   =       |   7  |   8  |   9  |   0  |   -  |   .  |   1  |   2  |   3  |   /  |    \      |
  |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
  | Brite  |       |       |       |          |          |         |  Prev  |  Next  |   Mute   |
   `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
```

## TouchCursor layer plus personal customizations
[TouchCursor](http://martin-stone.github.io/touchcursor/) uses the `Space` key
as the modifier, with the `IJKL` home row keys representing the inverted-T of
the arrow keys. All of the default TouchCursor keymappings for the right hand
are represented below. My personalizations include all of the keys shown for
the left hand. Having the `Alt` and `Shift` keys (as well as the `Control` key
from the base layers) readily accessible from the home row allows quick word
jumps and highlighting when used in conjunction with the arrow keys. The
`Alt-Tab` macro is not only useful under Windows, but also under Mac when used
with alternative switchers like [HyperSwitch](https://bahoom.com/hyperswitch).
The `Cmd-Tab` and `Ctrl-Tab` sequences are duplicated for easy access while in
this layer. The `KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, KC_FIND,` and `KC_AGAIN`
keycodes do not seem to work. There are macros in place that'll "automatically"
choose the correct version (`Cmd-Tab` vs. `Alt-Tab`, `Cmd-C` vs. `Ctrl-C`,
etc.) depending on which layout you've currently selected (`AG_NORM` or
`AG_SWAP`) in the `_ADJUST` layer. The `Desk_L` and `Desk_R` macros are what I
use to switch between Virtual Desktops Left/Right. The `Tab_C`, `Tab_N` and
`Tab_R` are for "Close Tab," "New Tab" and "Reopen Closed Tab" for apps such as
Google Chrome.
```
  ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
  | AltTab  |CmdTab|CtlTab| GUI  |Shift |  ~   |Insert| Home |  Up  | End  | Bksp |      |      |
  |---------`------`------`------`------`------`------`------`------`------`------`------`------|
  |          | Alt  |Space |Tab_C | Find |Again | PgUp | Left | Down |Right |Desk_L|  Desk_R    |
  |----------`------`------`------`------`------`------`------`------`------`------`------------|
  |           | Undo | Cut  | Copy |Paste |  `   | PgDn | Del  |Tab_N |Tab_R |iTerm2|           |
  |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
  |        |       |       |       |          |          |         |        |        |          |
   `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
```

## Mouse Layer
The Mouse layer, closely mimics the layout/behaviour of the TouchCursor layer.
The `D` key (on QWERTY) is used to activate this layer. All 16 keycodes for the
mouse from the `doc/keycode.txt` file are represented, and logically located,
IMHO. The left and right click buttons are duplicated; on the right hand side,
for a quick click here and there, and again on the left hand side for when the
buttons need to be held for dragging things or highlighting text, thus allowing
the right hand to be free to use the up/down/left/right actions.
```
  ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
  |         |      |ACCL0 |      |      |      |      |WHL_L |  Up  |WHL_R | BTN2 |      |      |
  |---------`------`------`------`------`------`------`------`------`------`------`------`------|
  |          |ACCL2 | BTN2 |      | BTN1 |ACCL1 |WHL_Up| Left | Down |Right | BTN4 |   BTN5     |
  |----------`------`------`------`------`------`------`------`------`------`------`------------|
  |           |      |      |      | BTN3 |      |WHL_Dn| BTN1 |      |      | BTN3 |           |
  |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
  |        |       |       |       |          |          |         |        |        |          |
   `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
```
