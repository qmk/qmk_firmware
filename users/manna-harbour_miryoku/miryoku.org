# After making changes to code or tables call org-babel-tangle (C-c C-v t).

#+Title: Miryoku [[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/logos/miryoku-roa-32.png]]

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/cover/miryoku-kle-cover.png]]

Miryoku is an ergonomic, minimal, orthogonal layout for ergo or ortho keyboards,
implemented as part of the QMK firmware.

The layout is maintained in emacs org-mode tables and converted to QMK keymap
data structures using embedded python scripts.  It is mapped onto keyboards with
different physical layouts as a subset without code duplication using the QMK
userspace feature and C macros.

Please see the [[https://github.com/manna-harbour/qmk_firmware/blob/miryoku/users/manna-harbour_miryoku/miryoku.org][development branch]] for any [[https://github.com/qmk/qmk_firmware/compare/master...manna-harbour:miryoku][updates not yet merged into QMK]].

To checkout the development branch in your existing QMK build environment:
#+BEGIN_SRC sh :tangle no
git remote add manna-harbour git@github.com:manna-harbour/qmk_firmware.git # ssh
git remote add manna-harbour https://github.com/manna-harbour/qmk_firmware.git # https
git fetch manna-harbour
git checkout --track manna-harbour/miryoku
#+END_SRC

Additional implementations and visualisations are provided outside QMK in the
[[https://github.com/manna-harbour/miryoku/blob/master/README.org][Miryoku (Extras) repository]].


* Contents                                                              :TOC_3:
- [[#layout][Layout]]
  - [[#general-principles][General Principles]]
  - [[#details][Details]]
  - [[#layers][Layers]]
    - [[#base][Base]]
    - [[#nav][Nav]]
    - [[#mouse][Mouse]]
    - [[#mouse-buttons-overlay][Mouse Buttons Overlay]]
    - [[#media][Media]]
    - [[#num][Num]]
    - [[#sym][Sym]]
    - [[#fun][Fun]]
    - [[#alternative-layouts][Alternative Layouts]]
- [[#code-generation][Code Generation]]
  - [[#table-conversion-scripts][Table Conversion Scripts]]
    - [[#table-layout-taphold][table-layout-taphold]]
    - [[#table-layout-half][table-layout-half]]
    - [[#table-layout-full][table-layout-full]]
    - [[#table-enums][table-enums]]
    - [[#table-keycode-mappings][table-keycode-mappings]]
  - [[#data][Data]]
    - [[#symbol-names][symbol-names]]
    - [[#mods][mods]]
    - [[#nonkc][nonkc]]
    - [[#header][header]]
    - [[#license-qmk][license-qmk]]
- [[#subset-mapping][Subset Mapping]]
  - [[#userspace][Userspace]]
    - [[#usersmanna-harbour_miryokurulesmk][users/manna-harbour_miryoku/rules.mk]]
    - [[#usersmanna-harbour_miryokuconfigh][users/manna-harbour_miryoku/config.h]]
    - [[#usersmanna-harbour_miryokumanna-harbour_miryokuh][users/manna-harbour_miryoku/manna-harbour_miryoku.h]]
    - [[#usersmanna-harbour_miryokumanna-harbour_miryokuc][users/manna-harbour_miryoku/manna-harbour_miryoku.c]]
  - [[#layouts][Layouts]]
    - [[#60_ansi][60_ansi]]
    - [[#ergodox][ergodox]]
    - [[#ortho_4x10][ortho_4x10]]
    - [[#ortho_4x12][ortho_4x12]]
    - [[#ortho_5x12][ortho_5x12]]
    - [[#ortho_5x15][ortho_5x15]]
    - [[#planck_mit][planck_mit]]
    - [[#split_3x5_3][split_3x5_3]]
    - [[#split_3x6_3][split_3x6_3]]
  - [[#keyboards][Keyboards]]
    - [[#atreus][atreus]]
    - [[#ergotravel][ergotravel]]
    - [[#for_science][for_science]]
    - [[#gergo][gergo]]
    - [[#handwireddactyl_manuform4x5][handwired/dactyl_manuform/4x5]]
    - [[#handwireddactyl_manuform5x6][handwired/dactyl_manuform/5x6]]
    - [[#keebioiris][keebio/iris]]
    - [[#keyboardioatreus][keyboardio/atreus]]
    - [[#kyria][kyria]]
    - [[#lily58][lily58]]
    - [[#moonlander][moonlander]]
    - [[#redox_w][redox_w]]
    - [[#sofle][sofle]]
    - [[#torn][torn]]
  - [[#customisation][Customisation]]
    - [[#examples][Examples]]
- [[#experimental-features][Experimental Features]]
  - [[#bilateral-combinations][Bilateral Combinations]]
  - [[#retro-shift][Retro Shift]]
- [[#documentation][Documentation]]
- [[#contact][Contact]]

* Layout

** General Principles

- Use layers instead of reaching.
- Use both hands instead of contortions.
- Use the home positions as much as possible.
- Make full use of the thumbs.
- Avoid unnecessary complication.


** Details

- 5 columns, 3 rows, 3 thumb keys, 2 hands.
- Can be used on almost any split or non-split ergo or ortho keyboard.
- Includes all keys found on a US layout TKL keyboard, plus media keys and mouse
  emulation.
- Home row is the middle row, home thumb key is the middle thumb key.
- Maximum 1-u movement from home position for fingers and thumbs, and only along
  one axis (except for the inner index finger column which is deprioritised
  compared with the home columns).
- Dual-function modifiers on home row, mirrored on both hands.
- Dual-function layer change on thumbs.
- Layers are designed orthogonally with a single purpose per hand and are
  accessed by holding a thumb key on the opposite hand.
- All layers on the same hand are based on the same basic key arrangement.
- Holding layer change and modifiers on one hand combined with a single key
  press on the other hand can produce any combination of modifiers and single
  keys without any finger contortions.
- Single function mods are also defined on layers on the same hand as the layer
  change thumb key so layer change and mods can be held in any order or
  simultaneously without race conditions.
- As mods are only enabled on the opposite hand, auto-repeat is available on the
  home row on layers for use with cursor and mouse keys.
- Tap-hold auto-repeat is disabled to permit faster tap-hold switching on
  thumbs, but thumb tap keys are mirrored onto some layers for use with
  auto-repeat.  On other layers thumb keys are redefined with important
  functions for that layer.
- Auto Shift for numbers and symbols.


** Layers

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/layers/miryoku-kle-reference.png]]

The layers are maintained in tables.  ~U_NP~ indicates the key is not present
and is used to fill in the table around the thumb keys.  The grid arrangement of
the tables does not imply a particular physical layout.

Basic keycodes are entered without the ~KC_~ prefix.  Symbols can be entered
as-is, except for '-' (~MINS~), '.' (~DOT~), '|' (~PIPE~), and '"' (~DQUO~).
Empty cells are unused.

The base layer is maintained as separate tables for tap alphas, tap thumbs, and
hold.  Other layers are specified as a single hand including thumbs.  Tables are
combined to produce the keymap for each layer.

Mods (and reset) will be available on sub layers on the same hand as the layer
change thumb key.  Unknown names are considered to be layer names.


*** Base

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/layers/miryoku-kle-base.png]]

The base layer alphas are Colemak Mod-DH.  Dot, comma, slash, and apostrophe are
included with the alphas.  The primary, secondary, and tertiary thumb keys are
backspace, enter, delete on the right and space, tab, escape on the left.

Alternative alpha arrangements are also available.


**** Tap


***** Alphas

#+NAME: colemakdh
| Q     | W     | F     | P     | B     | J     | L     | U     | Y     | '     |
| A     | R     | S     | T     | G     | M     | N     | E     | I     | O     |
| Z     | X     | C     | D     | V     | K     | H     | ,     | DOT   | /     |


***** Thumbs

#+NAME: thumbs
| U_NP  | U_NP  | ESC   | SPC   | TAB   | ENT   | BSPC  | DEL   | U_NP  | U_NP  |


**** Hold

#+NAME: hold
| RESET |       |       |       |       |       |       |       |       | RESET |
| LGUI  | LALT  | LCTL  | LSFT  |       |       | LSFT  | LCTL  | LALT  | LGUI  |
|       | ALGR  |       |       |       |       |       |       | ALGR  |       |
| U_NP  | U_NP  | MEDIA | NAV   | MOUSE | SYM   | NUM   | FUN   | U_NP  | U_NP  |


*** Nav

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/layers/miryoku-kle-nav.png]]

Primary right-hand layer (left home thumb) is navigation and editing.  Cursor
keys are on the home position, line and page movement below, clipboard above,
caps lock and insert on the inner column.  Thumb keys are duplicated from the
base layer to avoid having to layer change mid edit and to enable auto-repeat.

Alternative clipboard key mappings and navigation key arrangements are
available.

#+NAME: nav-r
| U_RDO | U_PST | U_CPY | U_CUT | U_UND |
| CAPS  | LEFT  | DOWN  | UP    | RGHT  |
| INS   | HOME  | PGDN  | PGUP  | END   |
| ENT   | BSPC  | DEL   | U_NP  | U_NP  |


*** Mouse

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/layers/miryoku-kle-mouse.png]]

Secondary right-hand layer is mouse emulation.  Mouse movement mirrors cursor
navigation on home and wheel mirrors line / page movement below.  Buttons are on
the thumbs (L, M, R).  Mouse movement, click, and drag, with modifiers, can be
performed from the home position.  Clipboard keys are duplicated from the Nav
layer.

#+NAME: mouse-r
| U_RDO | U_PST | U_CPY | U_CUT | U_UND |
|       | MS_L  | MS_D  | MS_U  | MS_R  |
|       | WH_L  | WH_D  | WH_U  | WH_R  |
| BTN1  | BTN3  | BTN2  | U_NP  | U_NP  |


*** Mouse Buttons Overlay

Available for automatic activation depending on keyboard hardware and
configuration.  Not activated manually.

#+NAME: mbo
| U_RDO | U_PST | U_CPY | U_CUT | U_UND | U_RDO | U_PST | U_CPY | U_CUT | U_UND |
| LGUI  | LALT  | LCTL  | LSFT  |       |       | LSFT  | LCTL  | LALT  | LGUI  |
|       |       |       |       |       |       |       |       |       |       |
| U_NP  | U_NP  | BTN2  | BTN3  | BTN1  | BTN1  | BTN3  | BTN2  | U_NP  | U_NP  |


*** Media

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/layers/miryoku-kle-media.png]]

Tertiary right-hand layer is media control, with volume up / down and next /
prev mirroring the navigation keys.  Pause, stop and mute are on thumbs.  RGB
control is on the top row (combine with shift to invert).  Unused keys are
available for other related functions.

#+NAME: media-r
| RGB_TOG | RGB_MOD | RGB_HUI | RGB_SAI | RGB_VAI |
|         | MPRV    | VOLD    | VOLU    | MNXT    |
|         |         |         |         |         |
| MSTP    | MPLY    | MUTE    | U_NP    | U_NP    |


*** Num

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/layers/miryoku-kle-num.png]]

Primary left-hand layer (right home thumb) is numerals and symbols.  Numerals
are in the standard numpad locations with symbols in the remaining positions.
Dot is duplicated from the base layer.

#+NAME: num-l
| [    | 7    | 8    | 9    | ]    |
| ;    | 4    | 5    | 6    | =    |
| `    | 1    | 2    | 3    | \    |
| U_NP | U_NP | DOT  | 0    | MINS |


*** Sym

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/layers/miryoku-kle-sym.png]]

Secondary left-hand layer has shifted symbols in the same locations to reduce
chording when using mods with shifted symbols.  Open parenthesis is duplicated
next to close parenthesis.

#+NAME: sym-l
| {    | &    | *    | (    | }    |
| :    | $    | %    | ^    | +    |
| ~    | !    | @    | #    | PIPE |
| U_NP | U_NP | (    | )    | _    |


*** Fun

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/layers/miryoku-kle-fun.png]]

Tertiary left-hand layer has function keys mirroring the numerals on the primary
layer with extras on the pinkie column, plus system keys on the inner column.
App (menu) is on the tertiary thumb key and other thumb keys are duplicated from
the base layer to enable auto-repeat.


#+NAME: fun-l
| F12  | F7   | F8   | F9   | PSCR |
| F11  | F4   | F5   | F6   | SLCK |
| F10  | F1   | F2   | F3   | PAUS |
| U_NP | U_NP | APP  | SPC  | TAB  |


*** Alternative Layouts

The defaults are recommended, but alternative layouts are provided to
accommodate existing muscle memory and platform differences.


**** Alphas

To select, append the corresponding option to the ~make~ command line when
building, e.g. ~MIRYOKU_ALPHAS=QWERTY~.


***** Colemak

~MIRYOKU_ALPHAS=COLEMAK~

#+NAME: colemak
| Q    | W    | F    | P    | G    | J    | L    | U    | Y    | '    |
| A    | R    | S    | T    | D    | H    | N    | E    | I    | O    |
| Z    | X    | C    | V    | B    | K    | M    | ,    | DOT  | /    |


***** Colemak Mod-DHk

~MIRYOKU_ALPHAS=COLEMAKDHK~

#+NAME: colemakdhk
| Q    | W    | F    | P    | B    | J    | L    | U    | Y    | '    |
| A    | R    | S    | T    | G    | K    | N    | E    | I    | O    |
| Z    | X    | C    | D    | V    | M    | H    | ,    | DOT  | /    |


***** Dvorak

~MIRYOKU_ALPHAS=DVORAK~

#+NAME: dvorak
| '    | ,    | DOT  | P    | Y    | F    | G    | C    | R    | L    |
| A    | O    | E    | U    | I    | D    | H    | T    | N    | S    |
| /    | Q    | J    | K    | X    | B    | M    | W    | V    | Z    |


***** Halmak

~MIRYOKU_ALPHAS=HALMAK~

#+NAME: halmak
| W    | L    | R    | B    | Z    | '    | Q    | U    | D    | J    |
| S    | H    | N    | T    | ,    | DOT  | A    | E    | O    | I    |
| F    | M    | V    | C    | /    | G    | P    | X    | K    | Y    |


***** Workman

~MIRYOKU_ALPHAS=WORKMAN~

#+NAME: workman
| Q    | D    | R    | W    | B    | J    | F    | U    | P    | '    |
| A    | S    | H    | T    | G    | Y    | N    | E    | O    | I    |
| Z    | X    | M    | C    | V    | K    | L    | ,    | DOT  | /    |


***** QWERTY

~MIRYOKU_ALPHAS=QWERTY~

#+NAME: qwerty
| Q    | W    | E    | R    | T    | Y    | U    | I    | O    | P    |
| A    | S    | D    | F    | G    | H    | J    | K    | L    | '    |
| Z    | X    | C    | V    | B    | N    | M    | ,    | DOT  | /    |


**** Nav


***** vi-Style

To select, append ~MIRYOKU_NAV=VI~ to the ~make~ command line when building.
Not available with ~MIRYOKU_LAYERS=FLIP~.


****** Nav

#+NAME: nav-r-vi
| U_RDO | U_PST | U_CPY | U_CUT | U_UND |
| LEFT  | DOWN  | UP    | RGHT  | CAPS  |
| HOME  | PGDN  | PGUP  | END   | INS   |
| ENT   | BSPC  | DEL   | U_NP  | U_NP  |


****** Mouse

#+NAME: mouse-r-vi
| U_RDO | U_PST | U_CPY | U_CUT | U_UND |
| MS_L  | MS_D  | MS_U  | MS_R  |       |
| WH_L  | WH_D  | WH_U  | WH_R  |       |
| BTN1  | BTN3  | BTN2  | U_NP  | U_NP  |


****** Media

#+NAME: media-r-vi
| RGB_TOG | RGB_MOD | RGB_HUI | RGB_SAI | RGB_VAI |
| MPRV    | VOLD    | VOLU    | MNXT    |         |
|         |         |         |         |         |
| MSTP    | MPLY    | MUTE    | U_NP    | U_NP    |


***** Inverted-T

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/layers/miryoku-kle-reference-flip-invertedt.png]]

To select, append ~MIRYOKU_NAV=INVERTEDT~ to the ~make~ command line when
building.  Only available with ~MIRYOKU_LAYERS=FLIP~.


****** Nav

#+NAME: nav-l-invertedt
| PGUP  | HOME  | UP    | END   | INS   |
| PGDN  | LEFT  | DOWN  | RGHT  | CAPS  |
| U_UND | U_CUT | U_CPY | U_PST | U_RDO |
| U_NP  | U_NP  | DEL   | BSPC  | ENT   |


****** Mouse

#+NAME: mouse-l-invertedt
| WH_U  | WH_L  | MS_U  | WH_R  |       |
| WH_D  | MS_L  | MS_D  | MS_R  |       |
| U_UND | U_CUT | U_CPY | U_PST | U_RDO |
| U_NP  | U_NP  | BTN2  | BTN3  | BTN1  |


****** Media

#+NAME: media-l-invertedt
|         |         | VOLU    |         |         |
|         | MPRV    | VOLD    | MNXT    |         |
| RGB_MOD | RGB_HUI | RGB_SAI | RGB_VAI | RGB_TOG |
| U_NP    | U_NP    | MUTE    | MPLY    | MSTP    |


**** Clipboard

Keycodes are translated according to the following tables.

By default, the main clipboard keys (cut, copy, and paste) use the CUA bindings
and should work in general unix and windows applications, emacs, and terminal
emulators.  The additional keys (undo, redo) usually require rebinding in the
application.

To select, append the corresponding option to the ~make~ command line when
building, e.g. ~MIRYOKU_CLIPBOARD=WIN~.


***** Default

#+NAME: clipboard
| U_RDO | AGIN      |
| U_PST | S(KC_INS) |
| U_CPY | C(KC_INS) |
| U_CUT | S(KC_DEL) |
| U_UND | UNDO   |


***** Fun Cluster

~MIRYOKU_CLIPBOARD=FUN~

#+NAME: clipboard-fun
| U_RDO | AGIN |
| U_PST | PSTE |
| U_CPY | COPY |
| U_CUT | CUT  |
| U_UND | UNDO |


***** Mac

~MIRYOKU_CLIPBOARD=MAC~

#+NAME: clipboard-mac
| U_RDO | SCMD(KC_Z) |
| U_PST | LCMD(KC_V) |
| U_CPY | LCMD(KC_C) |
| U_CUT | LCMD(KC_X) |
| U_UND | LCMD(KC_Z) |


***** Windows

~MIRYOKU_CLIPBOARD=WIN~

#+NAME: clipboard-win
| U_RDO | C(KC_Y) |
| U_PST | C(KC_V) |
| U_CPY | C(KC_C) |
| U_CUT | C(KC_X) |
| U_UND | C(KC_Z) |


**** Layers


***** Flip

Flip base layer thumb keys and sub layers between right and left hands.

To select, append ~MIRYOKU_LAYERS=FLIP~ to the ~make~ command line when building.


****** Thumbs

#+NAME: thumbs-flip
| U_NP | U_NP | DEL  | BSPC | ENT  | TAB  | SPC  | ESC  | U_NP | U_NP |


****** Hold

#+NAME: hold-flip
| RESET |       |       |       |       |       |       |       |       | RESET |
| LGUI  | LALT  | LCTL  | LSFT  |       |       | LSFT  | LCTL  | LALT  | LGUI  |
|       | ALGR  |       |       |       |       |       |       | ALGR  |       |
| U_NP  | U_NP  | FUN   | NUM   | SYM   | MOUSE | NAV   | MEDIA | U_NP  | U_NP  |


****** Nav

#+NAME: nav-l
| HOME  | PGDN  | PGUP  | END   | INS   |
| LEFT  | DOWN  | UP    | RGHT  | CAPS  |
| U_UND | U_CUT | U_CPY | U_PST | U_RDO |
| U_NP  | U_NP  | DEL   | BSPC  | ENT   |


****** Mouse

#+NAME: mouse-l
| WH_L  | WH_D  | WH_U  | WH_R  |       |
| MS_L  | MS_D  | MS_U  | MS_R  |       |
| U_UND | U_CUT | U_CPY | U_PST | U_RDO |
| U_NP  | U_NP  | BTN2  | BTN3  | BTN1  |


****** Mouse Buttons Overlay

#+NAME: mbo-flip
|       |       |       |       |       |       |       |       |       |       |
| LGUI  | LALT  | LCTL  | LSFT  |       |       | LSFT  | LCTL  | LALT  | LGUI  |
| U_RDO | U_PST | U_CPY | U_CUT | U_UND | U_RDO | U_PST | U_CPY | U_CUT | U_UND |
| U_NP  | U_NP  | BTN2  | BTN3  | BTN1  | BTN1  | BTN3  | BTN2  | U_NP  | U_NP  |


****** Media

#+NAME: media-l
| RGB_MOD | RGB_HUI | RGB_SAI | RGB_VAI | RGB_TOG |
| MPRV    | VOLD    | VOLU    | MNXT    |         |
|         |         |         |         |         |
| U_NP    | U_NP    | MUTE    | MPLY    | MSTP    |


****** Num

#+NAME: num-r
| [    | 7    | 8    | 9    | ]    |
| =    | 4    | 5    | 6    | ;    |
| \    | 1    | 2    | 3    | `    |
| MINS | 0    | DOT  | U_NP | U_NP |


****** Sym

#+NAME: sym-r
| {    | &    | *    | (    | }    |
| +    | $    | %    | ^    | :    |
| PIPE | !    | @    | #    | ~    |
| _    | (    | )    | U_NP | U_NP |


****** Fun

#+NAME: fun-r
| PSCR | F7   | F8   | F9   | F12  |
| SLCK | F4   | F5   | F6   | F11  |
| PAUS | F1   | F2   | F3   | F10  |
| TAB  | SPC  | APP  | U_NP | U_NP |


*** COMMENT Templates

#+NAME: tem
| <l4> | <l4> | <l4> | <l4> | <l4> | <l4> | <l4> | <l4> | <l4> | <l4> |
|------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |      |      |
| U_NP | U_NP |      |      |      |      |      |      | U_NP | U_NP |


Duplicate base layer tap keys on thumbs rather than trans to enable auto-repeat.

#+NAME: tem-r
| <l4> | <l4> | <l4> | <l4> | <l4> |
|------+------+------+------+------|
|      |      |      |      |      |
|      |      |      |      |      |
|      |      |      |      |      |
| ENT  | BSPC | DEL  | U_NP | U_NP |

#+NAME: tem-l
| <l4> | <l4> | <l4> | <l4> | <l4> |
|------+------+------+------+------|
|      |      |      |      |      |
|      |      |      |      |      |
|      |      |      |      |      |
| U_NP | U_NP | ESC  | SPC  | TAB  |


* Code Generation


** Table Conversion Scripts


*** table-layout-taphold

Produce base layer from separate tap and hold tables.

#+NAME: table-layout-taphold
#+BEGIN_SRC python :var alphas_table=colemakdh :var thumbs_table=thumbs :var hold_table=hold :var symbol_names_table=symbol-names :var mods_table=mods :var nonkc_table=nonkc :tangle no :results verbatim
width = 19
mods_dict = dict.fromkeys(mods_table[0])
nonkc_tuple = tuple(nonkc_table[0])
symbol_names_dict = {}
for symbol, name, shifted_symbol, shifted_name in symbol_names_table:
  symbol_names_dict[symbol] = name
  symbol_names_dict[shifted_symbol] = shifted_name
results = ''
for tap_row, hold_row in zip(alphas_table + thumbs_table, hold_table):
  results += '    '
  for tap, hold in zip(tap_row, hold_row):
    if tap == '':
      code = 'U_NU'
    elif tap in symbol_names_dict:
      code = symbol_names_dict[tap]
    else:
      code = tap
    if not str(code).startswith(nonkc_tuple):
      code = 'KC_' + str(code)
    if hold in mods_dict:
      code = str(hold) + '_T(' + code + ')'
    elif hold != '' and hold != 'U_NP' and hold != 'RESET':
      code = 'LT(' + str(hold) + ', ' + code + ')'
    results += (code + ', ').ljust(width)
  results = results.rstrip(' ') + '\n'
results = results.rstrip('\n, ')
return results
#+END_SRC

#+RESULTS: table-layout-taphold
:     KC_Q,              KC_W,              KC_F,              KC_P,              KC_B,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,
:     LGUI_T(KC_A),      LALT_T(KC_R),      LCTL_T(KC_S),      LSFT_T(KC_T),      KC_G,              KC_M,              LSFT_T(KC_N),      LCTL_T(KC_E),      LALT_T(KC_I),      LGUI_T(KC_O),
:     KC_Z,              ALGR_T(KC_X),      KC_C,              KC_D,              KC_V,              KC_K,              KC_H,              KC_COMM,           ALGR_T(KC_DOT),    KC_SLSH,
:     U_NP,              U_NP,              LT(MEDIA, KC_ESC), LT(NAV, KC_SPC),   LT(MOUSE, KC_TAB), LT(SYM, KC_ENT),   LT(NUM, KC_BSPC),  LT(FUN, KC_DEL),   U_NP,              U_NP


*** table-layout-half

Produce sub layers given layer name and corresponding table for single hand and
incorporating mods and reset from base layer.  Layer names must end with 'R' or
'L'.  A layer with shifted symbols can also be generated.

#+NAME: table-layout-half
#+BEGIN_SRC python :var hold_table=hold :var mode="r" :var half_table=nav-r :var symbol_names_table=symbol-names :var mods_table=mods :var nonkc_table=nonkc :var shift="false" :tangle no :results verbatim
width = 9
mods_dict = dict.fromkeys(mods_table[0])
nonkc_tuple = tuple(nonkc_table[0])
symbol_names_dict = {}
shifted_symbol_names_dict = {}
for symbol, name, shifted_symbol, shifted_name in symbol_names_table:
  symbol_names_dict[symbol] = name
  symbol_names_dict[shifted_symbol] = shifted_name
  shifted_symbol_names_dict[symbol] = shifted_name
length = len(half_table[0])
results = ''
for half_row, hold_row in zip(half_table, hold_table):
  results += '    '
  hold_row_l, hold_row_r = hold_row[:length], hold_row[length:]
  for lr, hold_row_lr in ('l', hold_row_l), ('r', hold_row_r):
    if lr == mode:
      for half in half_row:
        if half == '':
          code = 'U_NU'
        elif shift == "true" and half in shifted_symbol_names_dict:
          code = shifted_symbol_names_dict[half]
        elif half in symbol_names_dict:
          code = symbol_names_dict[half]
        else:
          code = half
        if not str(code).startswith(nonkc_tuple):
          code = 'KC_' + str(code)
        results += (str(code) + ', ').ljust(width)
    else:
      for hold in hold_row_lr:
        if hold == '' or hold != 'U_NP' and hold != 'RESET' and hold not in mods_dict:
          code = 'U_NA'
        else:
          code = hold
        if not str(code).startswith(nonkc_tuple):
          code = 'KC_' + str(code)
        results += (str(code) + ', ').ljust(width)
  results = results.rstrip(' ') + '\n'
results = results.rstrip('\n, ')
return results
#+END_SRC

#+RESULTS: table-layout-half
:     RESET,   U_NA,    U_NA,    U_NA,    U_NA,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
:     KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
:     U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,
:     U_NP,    U_NP,    U_NA,    U_NA,    U_NA,    KC_ENT,  KC_BSPC, KC_DEL,  U_NP,    U_NP


*** table-layout-full

Produce full layer from single table.  Fill for unused keys is configurable.

#+NAME: table-layout-full
#+BEGIN_SRC python :var table=mbo :var fill="TRNS" :var symbol_names_table=symbol-names :var nonkc_table=nonkc :tangle no :results verbatim
width = 9
symbol_names_dict = {}
nonkc_tuple = tuple(nonkc_table[0])
for symbol, name, shifted_symbol, shifted_name in symbol_names_table:
  symbol_names_dict[symbol] = name
  symbol_names_dict[shifted_symbol] = shifted_name
results = ''
for row in table:
  results += '    '
  for key in row:
    if key == '':
      code = fill
    elif key in symbol_names_dict:
      code = symbol_names_dict[key]
    else:
      code = key
    if not str(code).startswith(nonkc_tuple):
      code = 'KC_' + str(code)
    results += (code + ', ').ljust(width)
  results = results.rstrip(' ') + '\n'
results = results.rstrip('\n, ')
return results
#+END_SRC

#+RESULTS: table-layout-full
:     U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
:     KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS, KC_TRNS, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
:     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
:     U_NP,    U_NP,    KC_BTN2, KC_BTN3, KC_BTN1, KC_BTN1, KC_BTN3, KC_BTN2, U_NP,    U_NP


*** table-enums

Produce layer enums from layer names in hold table.

#+NAME: table-enums
#+BEGIN_SRC python :var hold_table=hold :var mods_table=mods :tangle no
mods_dict = dict.fromkeys(mods_table[0])
results = 'enum layers { BASE, MBO, '
for hold_row in hold_table:
  for hold in hold_row:
    if hold not in mods_dict and hold != '' and hold != 'U_NP' and hold != 'RESET':
      results += hold + ', '
results = results.rstrip(', ') + ' };'
return results
#+END_SRC

#+RESULTS: table-enums
: enum layers { BASE, MBO, MEDIA, NAV, MOUSE, SYM, NUM, FUN };


*** table-keycode-mappings

Produce keycode mappings according to the provided table.

#+NAME: table-keycode-mappings
#+BEGIN_SRC python :var table=clipboard :var symbol_names_table=symbol-names :var nonkc_table=nonkc :tangle no
nonkc_tuple = tuple(nonkc_table[0])
symbol_names_dict = {}
for symbol, name, shifted_symbol, shifted_name in symbol_names_table:
  symbol_names_dict[symbol] = name
  symbol_names_dict[shifted_symbol] = shifted_name
results = ''
for f,t in table:
  if t == '':
    code = 'U_NU'
  elif t in symbol_names_dict:
    code = symbol_names_dict[t]
  else:
    code = t
  if not str(code).startswith(nonkc_tuple):
    code = 'KC_' + str(code)
  results += '#define ' + f + ' ' + code + '\n'
return results
#+END_SRC

#+RESULTS: table-keycode-mappings
: #define U_RDO KC_AGIN
: #define U_PST S(KC_INS)
: #define U_CPY C(KC_INS)
: #define U_CUT S(KC_DEL)
: #define U_UND KC_UNDO


*** COMMENT python-version

C-c C-c in code block to update

#+NAME: python-version
#+BEGIN_SRC python :tangle no
import sys
return sys.version
#+END_SRC

#+RESULTS: python-version
: 3.9.4 (default, Apr  9 2021, 01:15:05) 
: [GCC 5.4.0 20160609]


** Data


*** symbol-names

Symbol, name, and shifted symbol mappings for use in tables.

#+NAME: symbol-names
| `    | GRV  | ~    | TILD |
| "-"  | MINS | _    | UNDS |
| =    | EQL  | +    | PLUS |
| [    | LBRC | {    | LCBR |
| ]    | RBRC | }    | RCBR |
| \    | BSLS | PIPE | PIPE |
| ;    | SCLN | :    | COLN |
| '    | QUOT | DQUO | DQUO |
| ,    | COMM | <    | LT   |
| "."  | DOT  | >    | GT   |
| /    | SLSH | ?    | QUES |
| 1    | 1    | !    | EXLM |
| 2    | 2    | @    | AT   |
| 3    | 3    | #    | HASH |
| 4    | 4    | $    | DLR  |
| 5    | 5    | %    | PERC |
| 6    | 6    | ^    | CIRC |
| 7    | 7    | &    | AMPR |
| 8    | 8    | *    | ASTR |
| 9    | 9    | (    | LPRN |
| 0    | 0    | )    | RPRN |


*** mods

Modifiers usable in hold table.  Need to have the same name for ~KC_~ and ~_T~
versions.

#+NAME: mods
| LSFT | LCTL | LALT | LGUI | ALGR |


*** nonkc

Keycodes that match any of these prefixes will not have ~KC_~ automatically
prepended.

#+NAME: nonkc
| U_ | RGB_ | RESET | S( | C( | SCMD( | LCMD( |


*** header

Header for tangled files.

#+NAME: header
#+BEGIN_SRC C :main no :tangle no
Copyright 2019 Manna Harbour
https://github.com/manna-harbour/miryoku
generated from users/manna-harbour_miryoku/miryoku.org  -*- buffer-read-only: t -*-
#+END_SRC


*** license-qmk

License for tangled QMK C source files.

#+NAME: license-qmk
#+BEGIN_SRC C :main no :tangle no
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#+END_SRC


* Subset Mapping

The keymap, build options, and configuration are shared between keyboards.  The
layout is mapped onto keyboards with different physical layouts as a subset.


** Userspace

The keymap is defined for ~LAYOUT_miryoku~ which is 10x4, with the outer 2
positions on the bottom row unused and the rest of the bottom row being the
thumb keys.


*** [[./rules.mk][users/manna-harbour_miryoku/rules.mk]]

Build options.  Automatically included.

#+BEGIN_SRC makefile :noweb yes :padline no :tangle rules.mk
# <<header>>

MOUSEKEY_ENABLE = yes # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
AUTO_SHIFT_ENABLE = yes # Auto Shift

SRC += manna-harbour_miryoku.c # keymap

# alternative layouts:

# alphas
ifneq ($(strip $(MIRYOKU_ALPHAS)),)
  OPT_DEFS += -DMIRYOKU_ALPHAS_$(MIRYOKU_ALPHAS)
endif

# nav
ifneq ($(strip $(MIRYOKU_NAV)),)
  OPT_DEFS += -DMIRYOKU_NAV_$(MIRYOKU_NAV)
endif

# clipboard
ifneq ($(strip $(MIRYOKU_CLIPBOARD)),)
  OPT_DEFS += -DMIRYOKU_CLIPBOARD_$(MIRYOKU_CLIPBOARD)
endif

# layers
ifneq ($(strip $(MIRYOKU_LAYERS)),)
  OPT_DEFS += -DMIRYOKU_LAYERS_$(MIRYOKU_LAYERS)
endif

# subset mappings
ifneq ($(strip $(MIRYOKU_MAPPING)),)
  OPT_DEFS += -DMIRYOKU_MAPPING_$(MIRYOKU_MAPPING)
endif
#+END_SRC


*** [[./config.h][users/manna-harbour_miryoku/config.h]]

Config options.  Automatically included.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle config.h
// <<header>>

<<license-qmk>>

#pragma once

// default but used in macros
#undef TAPPING_TERM
#define TAPPING_TERM 200

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// Auto Shift
#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define AUTO_SHIFT_NO_SETUP

// Recommended for heavy chording.
#define QMK_KEYS_PER_SCAN 4

// Mouse key speed and acceleration.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY          0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL       16
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY    0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED      6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    64
#+END_SRC


*** [[./manna-harbour_miryoku.h][users/manna-harbour_miryoku/manna-harbour_miryoku.h]]

Keymap-related definitions.  Included from ~manna-harbour_miryoku.c~.  Can be
included from keymap or layout ~keymap.c~ if needed.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle manna-harbour_miryoku.h
// <<header>>

<<license-qmk>>

#pragma once

#include QMK_KEYBOARD_H

#define U_NP KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used

<<table-enums()>>

#if defined MIRYOKU_CLIPBOARD_FUN
<<table-keycode-mappings(table=clipboard-fun)>>
#elif defined MIRYOKU_CLIPBOARD_MAC
<<table-keycode-mappings(table=clipboard-mac)>>
#elif defined MIRYOKU_CLIPBOARD_WIN
<<table-keycode-mappings(table=clipboard-win)>>
#else
<<table-keycode-mappings(table=clipboard)>>
#endif


#+END_SRC


*** [[./manna-harbour_miryoku.c][users/manna-harbour_miryoku/manna-harbour_miryoku.c]]

Contains the keymap.  Added from ~rules.mk~.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle manna-harbour_miryoku.c
// <<header>>

<<license-qmk>>

#include "manna-harbour_miryoku.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#if defined MIRYOKU_LAYERS_FLIP
  [BASE] = LAYOUT_miryoku(
  #if defined MIRYOKU_ALPHAS_COLEMAK
<<table-layout-taphold(alphas_table=colemak, thumbs_table=thumbs-flip, hold_table=hold-flip)>>
  #elif defined MIRYOKU_ALPHAS_COLEMAKDHK
<<table-layout-taphold(alphas_table=colemakdhk, thumbs_table=thumbs-flip, hold_table=hold-flip)>>
  #elif defined MIRYOKU_ALPHAS_DVORAK
<<table-layout-taphold(alphas_table=dvorak, thumbs_table=thumbs-flip, hold_table=hold-flip)>>
  #elif defined MIRYOKU_ALPHAS_HALMAK
<<table-layout-taphold(alphas_table=halmak, thumbs_table=thumbs-flip, hold_table=hold-flip)>>
  #elif defined MIRYOKU_ALPHAS_WORKMAN
<<table-layout-taphold(alphas_table=workman, thumbs_table=thumbs-flip, hold_table=hold-flip)>>
  #elif defined MIRYOKU_ALPHAS_QWERTY
<<table-layout-taphold(alphas_table=qwerty, thumbs_table=thumbs-flip, hold_table=hold-flip)>>
  #else
<<table-layout-taphold(alphas_table=colemakdh, thumbs_table=thumbs-flip, hold_table=hold-flip)>>
  #endif
  ),
  #if defined MIRYOKU_NAV_INVERTEDT
  [NAV] = LAYOUT_miryoku(
<<table-layout-half(half_table=nav-l-invertedt, mode="l", hold_table=hold-flip)>>
  ),
  [MOUSE] = LAYOUT_miryoku(
<<table-layout-half(half_table=mouse-l-invertedt, mode="l", hold_table=hold-flip)>>
  ),
  [MEDIA] = LAYOUT_miryoku(
<<table-layout-half(half_table=media-l-invertedt, mode="l", hold_table=hold-flip)>>
  ),
  #else
  [NAV] = LAYOUT_miryoku(
<<table-layout-half(half_table=nav-l, mode="l", hold_table=hold-flip)>>
  ),
  [MOUSE] = LAYOUT_miryoku(
<<table-layout-half(half_table=mouse-l, mode="l", hold_table=hold-flip)>>
  ),
  [MEDIA] = LAYOUT_miryoku(
<<table-layout-half(half_table=media-l, mode="l", hold_table=hold-flip)>>
  ),
  #endif
  [MBO] = LAYOUT_miryoku(
<<table-layout-full(table=mbo, fill="TRNS")>>
  ),
  [NUM] = LAYOUT_miryoku(
<<table-layout-half(half_table=num-r, mode="r", hold_table=hold-flip)>>
  ),
  [SYM] = LAYOUT_miryoku(
<<table-layout-half(half_table=sym-r, mode="r", hold_table=hold-flip)>>
  ),
  [FUN] = LAYOUT_miryoku(
<<table-layout-half(half_table=fun-r, mode="r", hold_table=hold-flip)>>
  )
,
#else
  [BASE] = LAYOUT_miryoku(
  #if defined MIRYOKU_ALPHAS_COLEMAK
<<table-layout-taphold(alphas_table=colemak)>>
  #elif defined MIRYOKU_ALPHAS_COLEMAKDHK
<<table-layout-taphold(alphas_table=colemakdhk)>>
  #elif defined MIRYOKU_ALPHAS_DVORAK
<<table-layout-taphold(alphas_table=dvorak)>>
  #elif defined MIRYOKU_ALPHAS_HALMAK
<<table-layout-taphold(alphas_table=halmak)>>
  #elif defined MIRYOKU_ALPHAS_WORKMAN
<<table-layout-taphold(alphas_table=workman)>>
  #elif defined MIRYOKU_ALPHAS_QWERTY
<<table-layout-taphold(alphas_table=qwerty)>>
  #else
<<table-layout-taphold(alphas_table=colemakdh)>>
  #endif
  ),
  #if defined MIRYOKU_NAV_VI
  [NAV] = LAYOUT_miryoku(
<<table-layout-half(half_table=nav-r-vi, mode="r")>>
  ),
  [MOUSE] = LAYOUT_miryoku(
<<table-layout-half(half_table=mouse-r-vi, mode="r")>>
  ),
  [MEDIA] = LAYOUT_miryoku(
<<table-layout-half(half_table=media-r-vi, mode="r")>>
  ),
  #else
  [NAV] = LAYOUT_miryoku(
<<table-layout-half(half_table=nav-r, mode="r")>>
  ),
  [MOUSE] = LAYOUT_miryoku(
<<table-layout-half(half_table=mouse-r, mode="r")>>
  ),
  [MEDIA] = LAYOUT_miryoku(
<<table-layout-half(half_table=media-r, mode="r")>>
  ),
  #endif
  [MBO] = LAYOUT_miryoku(
<<table-layout-full(table=mbo-flip, fill="TRNS")>>
  ),
  [NUM] = LAYOUT_miryoku(
<<table-layout-half(half_table=num-l, mode="l")>>
  ),
  [SYM] = LAYOUT_miryoku(
<<table-layout-half(half_table=sym-l, mode="l")>>
  ),
  [FUN] = LAYOUT_miryoku(
<<table-layout-half(half_table=fun-l, mode="l")>>
  )
#endif
};
#+END_SRC


** Layouts

To use the keymap on a keyboard supporting the layouts feature, ~LAYOUT_miryoku~
is defined as a macro mapping onto the layout's own ~LAYOUT~ macro, leaving the
unused keys as ~KC_NO~.

For keyboards supporting multiple layouts for which subset mappings are
available, select the layout with ~FORCE_LAYOUT~ in the ~make~ command line when
building.  E.g.:

#+BEGIN_SRC sh :tangle no
make planck/rev6:manna-harbour_miryoku:flash FORCE_LAYOUT=planck_mit # planck_mit
make planck/rev6:manna-harbour_miryoku:flash FORCE_LAYOUT=ortho_4x12 # ortho_4x12
#+END_SRC


*** 60_ansi

An angled ortho split layout is mapped onto the row-staggered keyboard.  The
rows are moved up to better position the thumb keys, the hands are separated as
much as possible, and the left hand column angle is reversed to reduce ulnar
deviation of the wrists.

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/mapping/miryoku-kle-mapping-60_ansi.png]]

An alternative subset mapping is also provided without reverse column angle.  To
select this mapping, append ~MIRYOKU_MAPPING=NOREVERSEANGLE~ to the ~make~
command line when building.

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/mapping/miryoku-kle-mapping-60_ansi-noreverseangle.png]]

Keyboards supporting this layout: alps64, amj60, bakeneko60, bm60poker, bm60rgb, do60, dp60, dz60, facew, gskt00, infinity60, jm60, kc60, kc60se, ok60, org60, paladin64, panc60, reviung61, smk60, v60_type_r, yd60mq, 1upkeyboards/1up60hse, 1upkeyboards/1up60rgb, 40percentclub/luddite, acheron/keebspcb, acheron/lasgweloth, ai03/polaris, akegata_denki/device_one, atxkb/1894, bioi/g60ble, bt66tech/bt66tech60, cannonkeys/an_c, cannonkeys/instant60, cannonkeys/practice60, clawsome/coupe, dm9records/tartan, duck/eagle_viper, evyd13/plain60, exclusive/e6_rgb, gh60/revc, gh60/satan, gh60/v1p3, handwired/xealousbrown, hineybush/h60, hs60/v1, keebio/wtf60, noxary/260, playkbtw/pk60, ryloo_studio/m0110, thevankeyboards/bananasplit, wilba_tech/zeal60, xd60/rev2, xd60/rev3, cannonkeys/db60/hotswap, cannonkeys/db60/j02, cannonkeys/db60/rev2, exclusive/e6v2/le, exclusive/e6v2/oe, foxlab/leaf60/universal, handwired/co60/rev1, handwired/co60/rev7, handwired/swiftrax/nodu, hs60/v2/ansi, inett_studio/sqx/universal, melgeek/mj61/rev1, melgeek/mj61/rev2, melgeek/mj63/rev1, melgeek/mj63/rev2, sentraq/s60_x/default, sentraq/s60_x/rgb.

Example build command lines:

#+BEGIN_SRC sh :tangle no
make dz60:manna-harbour_miryoku:flash # dz60
make dz60:manna-harbour_miryoku:flash MIRYOKU_MAPPING=NOREVERSEANGLE  # dz60, without reverse column angle
#+END_SRC


**** [[../../layouts/community/60_ansi/manna-harbour_miryoku/config.h][layouts/community/60_ansi/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/60_ansi/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#if defined MIRYOKU_MAPPING_NOREVERSEANGLE
#define LAYOUT_miryoku(\
K00,  K01,  K02,  K03,  K04,                    K05,  K06,  K07,  K08,  K09,\
K10,  K11,  K12,  K13,  K14,                    K15,  K16,  K17,  K18,  K19,\
K20,  K21,  K22,  K23,  K24,                    K25,  K26,  K27,  K28,  K29,\
N30,  N31,  K32,  K33,  K34,                    K35,  K36,  K37,  N38,  N39\
)\
LAYOUT_60_ansi(\
K00,  K01,  K02,  K03,  K04,  XXX,  XXX,  XXX,  K05,  K06,  K07,  K08,  K09,  XXX,\
   K10,  K11,  K12,  K13,  K14,  XXX,  XXX,  XXX,  K15,  K16,  K17,  K18,  K19,  XXX,\
     K20,  K21,  K22,  K23,  K24,  XXX,  XXX,  XXX,  K25,  K26,  K27,  K28,  K29,\
  XXX,        K32,  K33,  K34,  XXX,  XXX,  XXX,  XXX,  K35,  K36,  K37,  XXX,\
  XXX,  XXX,  XXX,              XXX,              XXX,  XXX,        XXX,  XXX\
)
#else
#define LAYOUT_miryoku(\
            K00,  K01,  K02,  K03,  K04,        K05,  K06,  K07,  K08,  K09,\
            K10,  K11,  K12,  K13,  K14,        K15,  K16,  K17,  K18,  K19,\
            K20,  K21,  K22,  K23,  K24,        K25,  K26,  K27,  K28,  K29,\
            N30,  N31,  K32,  K33,  K34,        K35,  K36,  K37,  N38,  N39\
)\
LAYOUT_60_ansi(\
XXX,  XXX,  K00,  K01,  K02,  K03,  K04,  XXX,  K05,  K06,  K07,  K08,  K09,  XXX,\
   XXX,  K10,  K11,  K12,  K13,  K14,  XXX,  XXX,  K15,  K16,  K17,  K18,  K19,  XXX,\
     K20,  K21,  K22,  K23,  K24,  XXX,  XXX,  XXX,  K25,  K26,  K27,  K28,  K29,\
  XXX,        XXX,  K32,  K33,  K34,  XXX,  XXX,  XXX,  K35,  K36,  K37,  XXX,\
  XXX,  XXX,  XXX,              XXX,              XXX,  XXX,        XXX,  XXX\
)
#endif
#+END_SRC


**** [[../../layouts/community/60_ansi/manna-harbour_miryoku/keymap.c][layouts/community/60_ansi/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/60_ansi/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** ergodox

For the ergodox layout, the main 5x3 alphas are used as usual. The primary and
secondary thumb keys are the inner and outer 2u thumb keys and the tertiary
thumb key is the innermost key of the partial bottom row.  The remaining keys
are unused.

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/mapping/miryoku-kle-mapping-ergodox.png]]

Keyboards supporting this layout: ergodone, ergodox_ez, ergodox_infinity, hotdox.

Example build command lines:

#+BEGIN_SRC sh :tangle no
make ergodox_infinity:manna-harbour_miryoku:flash # ergodox_infinity
make ergodox_ez:manna-harbour_miryoku:flash # ergodox_ez
#+END_SRC


**** [[../../layouts/community/ergodox/manna-harbour_miryoku/config.h][layouts/community/ergodox/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/ergodox/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku(\
     K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09,\
     K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19,\
     K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29,\
     N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39\
)\
LAYOUT_ergodox_pretty(\
XXX, XXX, XXX, XXX, XXX, XXX, XXX,      XXX, XXX, XXX, XXX, XXX, XXX, XXX,\
XXX, K00, K01, K02, K03, K04, XXX,      XXX, K05, K06, K07, K08, K09, XXX,\
XXX, K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19, XXX,\
XXX, K20, K21, K22, K23, K24, XXX,      XXX, K25, K26, K27, K28, K29, XXX,\
XXX, XXX, XXX, XXX, K32,                          K37, XXX, XXX, XXX, XXX,\
                         XXX, XXX,      XXX, XXX,\
                              XXX,      XXX,\
                    K33, K34, XXX,      XXX, K35, K36\
)
#+END_SRC


**** [[../../layouts/community/ergodox/manna-harbour_miryoku/keymap.c][layouts/community/ergodox/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/ergodox/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** ortho_4x10

Keyboards supporting this layout: newgame40, nimrod, marksard/rhymestone, pabile/p40.

Example build command lines:

#+BEGIN_SRC sh :tangle no
make marksard/rhymestone:manna-harbour_miryoku:flash # marksard/rhymestone
#+END_SRC


**** [[../../layouts/community/ortho_4x10/manna-harbour_miryoku/config.h][layouts/community/ortho_4x10/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/ortho_4x10/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define LAYOUT_miryoku(\
K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,\
N30,   N31,   K32,   K33,   K34,   K35,   K36,   K37,   N38,   N39\
)\
LAYOUT_ortho_4x10(\
K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,\
KC_NO, KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   KC_NO, KC_NO\
)
#+END_SRC


**** [[../../layouts/community/ortho_4x10/manna-harbour_miryoku/keymap.c][layouts/community/ortho_4x10/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/ortho_4x10/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** ortho_4x12

For the ortho_4x12 layout, the middle two columns, and the 2 keys on each end of
the bottom row are unused.  This allows the hands to be positioned without ulnar
deviation of the wrists.

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/mapping/miryoku-kle-mapping-ortho_4x12.png]]

For split keyboards using this layout the halves can be positioned and rotated
for each hand and so an alternative mapping is provided.  The right half is as
follows: The rightmost column bottom 3 keys is the pinkie column.  The middle 4
columns top 3 rows are for the remaining fingers.  The pinkie column is one row
lower than the other columns to provide some column stagger.  The bottom row
left 3 keys are the thumb keys.  The remaining keys are unused.  To select this
mapping, append ~MIRYOKU_MAPPING=SPLIT~ to the ~make~ command line when
building.

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/mapping/miryoku-kle-mapping-ortho_4x12-split.png]]

An alternative with extended thumb position but without pinkie column stagger is
also provided.  To select this mapping, append ~MIRYOKU_MAPPING=EXTENDED_THUMBS~
to the ~make~ command line when building.

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/mapping/miryoku-kle-mapping-ortho_4x12-extended_thumbs.png]]

Keyboards supporting this layout: chimera_ls, contra, efreet, jj40, jnao, lets_split, lets_split_eh, meira, niu_mini, quark, tau4, telophase, vitamins_included, zlant, 40percentclub/4x4, 40percentclub/nori, acheron/shark, boardsource/4x12, cannonkeys/ortho48, dm9records/plaid, evyd13/eon40, evyd13/pockettype, handwired/floorboard, handwired/jotanck, handwired/wulkan, kbdfans/kbd4x, keebio/levinson, keebio/wavelet, mechstudio/ud_40_ortho, planck/ez, planck/light, planck/rev1, planck/rev2, planck/rev3, planck/rev4, planck/rev5, planck/rev6, planck/thk, rgbkb/zygomorph, zvecr/split_blackpill, zvecr/zv48, keebio/nyquist/rev1, keebio/nyquist/rev2, keebio/nyquist/rev3, montsinger/rebound/rev1, montsinger/rebound/rev2, montsinger/rebound/rev3, montsinger/rebound/rev4, signum/3_0/elitec, spaceman/pancake/feather, spaceman/pancake/promicro, ymdk/ymd40/v2.

Example build command lines:

#+BEGIN_SRC sh :tangle no
make planck/rev6:manna-harbour_miryoku:flash FORCE_LAYOUT=ortho_4x12 # planck, ortho_4x12
make planck/rev6:manna-harbour_miryoku:flash FORCE_LAYOUT=ortho_4x12 MIRYOKU_MAPPING=EXTENDED_THUMBS # planck, ortho_4x12, extended thumbs
make keebio/levinson:manna-harbour_miryoku:flash MIRYOKU_MAPPING=SPLIT # levinson
make keebio/levinson:manna-harbour_miryoku:flash MIRYOKU_MAPPING=EXTENDED_THUMBS # levinson, extended thumbs
#+END_SRC


**** [[../../layouts/community/ortho_4x12/manna-harbour_miryoku/config.h][layouts/community/ortho_4x12/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/ortho_4x12/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#if defined MIRYOKU_MAPPING_SPLIT
#define LAYOUT_miryoku(\
K00,   K01,   K02,   K03,   K04,                 K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,                 K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,                 K25,   K26,   K27,   K28,   K29,\
N30,   N31,   K32,   K33,   K34,                 K35,   K36,   K37,   N38,   N39\
)\
LAYOUT_ortho_4x12(\
KC_NO, K01,   K02,   K03,   K04,   KC_NO, KC_NO, K05,   K06,   K07,   K08,   KC_NO,\
K00,   K11,   K12,   K13,   K14,   KC_NO, KC_NO, K15,   K16,   K17,   K18,   K09,\
K10,   K21,   K22,   K23,   K24,   KC_NO, KC_NO, K25,   K26,   K27,   K28,   K19,\
K20,   KC_NO, KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   KC_NO, KC_NO, K29\
)
#elif defined MIRYOKU_MAPPING_EXTENDED_THUMBS
#define LAYOUT_miryoku(\
K00,   K01,   K02,   K03,   K04,                 K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,                 K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,                 K25,   K26,   K27,   K28,   K29,\
N30,   N31,   K32,   K33,   K34,                 K35,   K36,   K37,   N38,   N39\
)\
LAYOUT_ortho_4x12(\
K00,   K01,   K02,   K03,   K04,   KC_NO, KC_NO, K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,   KC_NO, KC_NO, K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,   KC_NO, KC_NO, K25,   K26,   K27,   K28,   K29,\
KC_NO, KC_NO, KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   KC_NO, KC_NO, KC_NO\
)
#else
#define LAYOUT_miryoku(\
K00,   K01,   K02,   K03,   K04,                 K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,                 K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,                 K25,   K26,   K27,   K28,   K29,\
N30,   N31,   K32,   K33,   K34,                 K35,   K36,   K37,   N38,   N39\
)\
LAYOUT_ortho_4x12(\
K00,   K01,   K02,   K03,   K04,   KC_NO, KC_NO, K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,   KC_NO, KC_NO, K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,   KC_NO, KC_NO, K25,   K26,   K27,   K28,   K29,\
KC_NO, KC_NO, K32,   K33,   K34,   KC_NO, KC_NO, K35,   K36,   K37,   KC_NO, KC_NO\
)
#endif
#+END_SRC


**** [[../../layouts/community/ortho_4x12/manna-harbour_miryoku/keymap.c][layouts/community/ortho_4x12/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/ortho_4x12/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** ortho_5x12

As per ortho_4x12 but the top row is unused.

Keyboards supporting this layout: fractal, jj50, jnao, boardsource/5x12, cannonkeys/atlas_alps, cannonkeys/ortho60, handwired/jot50, handwired/riblee_f401, handwired/riblee_f411, handwired/rs60, keycapsss/o4l_5x12, peej/lumberjack, preonic/rev1, preonic/rev2, preonic/rev3, rgbkb/zygomorph, keebio/nyquist/rev1, keebio/nyquist/rev2, keebio/nyquist/rev3.

Example build command lines:

#+BEGIN_SRC sh :tangle no
make preonic/rev3:manna-harbour_miryoku:flash # preonic/rev3
make preonic/rev3:manna-harbour_miryoku:flash MIRYOKU_MAPPING=EXTENDED_THUMBS # preonic/rev3, extended thumbs
make keebio/nyquist/rev3:manna-harbour_miryoku:flash MIRYOKU_MAPPING=SPLIT # nyquist/rev3, split
make keebio/nyquist/rev3:manna-harbour_miryoku:flash MIRYOKU_MAPPING=EXTENDED_THUMBS # nyquist/rev3, extended thumbs

#+END_SRC


**** [[../../layouts/community/ortho_5x12/manna-harbour_miryoku/config.h][layouts/community/ortho_5x12/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/ortho_5x12/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#if defined MIRYOKU_MAPPING_SPLIT
#define LAYOUT_miryoku(\
K00,   K01,   K02,   K03,   K04,                 K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,                 K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,                 K25,   K26,   K27,   K28,   K29,\
N30,   N31,   K32,   K33,   K34,                 K35,   K36,   K37,   N38,   N39\
)\
LAYOUT_ortho_5x12(\
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,\
KC_NO, K01,   K02,   K03,   K04,   KC_NO, KC_NO, K05,   K06,   K07,   K08,   KC_NO,\
K00,   K11,   K12,   K13,   K14,   KC_NO, KC_NO, K15,   K16,   K17,   K18,   K09,\
K10,   K21,   K22,   K23,   K24,   KC_NO, KC_NO, K25,   K26,   K27,   K28,   K19,\
K20,   KC_NO, KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   KC_NO, KC_NO, K29\
)
#elif defined MIRYOKU_MAPPING_EXTENDED_THUMBS
#define LAYOUT_miryoku(\
K00,   K01,   K02,   K03,   K04,                 K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,                 K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,                 K25,   K26,   K27,   K28,   K29,\
N30,   N31,   K32,   K33,   K34,                 K35,   K36,   K37,   N38,   N39\
)\
LAYOUT_ortho_5x12(\
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,\
K00,   K01,   K02,   K03,   K04,   KC_NO, KC_NO, K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,   KC_NO, KC_NO, K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,   KC_NO, KC_NO, K25,   K26,   K27,   K28,   K29,\
KC_NO, KC_NO, KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   KC_NO, KC_NO, KC_NO\
)
#else
#define LAYOUT_miryoku(\
K00,   K01,   K02,   K03,   K04,                 K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,                 K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,                 K25,   K26,   K27,   K28,   K29,\
N30,   N31,   K32,   K33,   K34,                 K35,   K36,   K37,   N38,   N39\
)\
LAYOUT_ortho_5x12(\
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,\
K00,   K01,   K02,   K03,   K04,   KC_NO, KC_NO, K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,   KC_NO, KC_NO, K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,   KC_NO, KC_NO, K25,   K26,   K27,   K28,   K29,\
KC_NO, KC_NO, K32,   K33,   K34,   KC_NO, KC_NO, K35,   K36,   K37,   KC_NO, KC_NO\
)
#endif
#+END_SRC


**** [[../../layouts/community/ortho_5x12/manna-harbour_miryoku/keymap.c][layouts/community/ortho_5x12/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/ortho_5x12/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** ortho_5x15

For the ortho_5x15 layout, the top row, middle 5 columns, and the 2 keys on each
end of the bottom row are unused.  This allows the hands to be positioned
without ulnar deviation of the wrists.

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/mapping/miryoku-kle-mapping-ortho_5x15.png]]

An alternative subset mapping is also provided with the thumb keys shifted
across one position in the direction of thumb extension.  To select this
mapping, append ~MIRYOKU_MAPPING=EXTENDED_THUMBS~ to the ~make~ command line
when building.

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/mapping/miryoku-kle-mapping-ortho_5x15-extended_thumbs.png]]

Keyboards supporting this layout: atomic, geminate60, idobo, punk75, xd75, 40percentclub/5x5, 40percentclub/i75, cannonkeys/ortho75, sendyyeah/75pixels.

Example build command lines:

#+BEGIN_SRC sh :tangle no
make atomic:manna-harbour_miryoku:flash # atomic
make atomic:manna-harbour_miryoku:flash MIRYOKU_MAPPING=EXTENDED_THUMBS # atomic, extended thumbs
make idobo:manna-harbour_miryoku:flash # idobo
#+END_SRC


**** [[../../layouts/community/ortho_5x15/manna-harbour_miryoku/config.h][layouts/community/ortho_5x15/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/ortho_5x15/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#if defined MIRYOKU_MAPPING_EXTENDED_THUMBS
#define LAYOUT_miryoku(\
K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09,\
K10, K11, K12, K13, K14,                          K15, K16, K17, K18, K19,\
K20, K21, K22, K23, K24,                          K25, K26, K27, K28, K29,\
N30, N31, K32, K33, K34,                          K35, K36, K37, N38, N39\
)\
LAYOUT_ortho_5x15(\
XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,\
K00, K01, K02, K03, K04, XXX, XXX, XXX, XXX, XXX, K05, K06, K07, K08, K09,\
K10, K11, K12, K13, K14, XXX, XXX, XXX, XXX, XXX, K15, K16, K17, K18, K19,\
K20, K21, K22, K23, K24, XXX, XXX, XXX, XXX, XXX, K25, K26, K27, K28, K29,\
XXX, XXX, XXX, K32, K33, K34, XXX, XXX, XXX, K35, K36, K37, XXX, XXX, XXX\
)
#else
#define LAYOUT_miryoku(\
K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09,\
K10, K11, K12, K13, K14,                          K15, K16, K17, K18, K19,\
K20, K21, K22, K23, K24,                          K25, K26, K27, K28, K29,\
N30, N31, K32, K33, K34,                          K35, K36, K37, N38, N39\
)\
LAYOUT_ortho_5x15(\
XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,\
K00, K01, K02, K03, K04, XXX, XXX, XXX, XXX, XXX, K05, K06, K07, K08, K09,\
K10, K11, K12, K13, K14, XXX, XXX, XXX, XXX, XXX, K15, K16, K17, K18, K19,\
K20, K21, K22, K23, K24, XXX, XXX, XXX, XXX, XXX, K25, K26, K27, K28, K29,\
XXX, XXX, K32, K33, K34, XXX, XXX, XXX, XXX, XXX, K35, K36, K37, XXX, XXX\
)
#endif
#+END_SRC

#+RESULTS:


**** [[../../layouts/community/ortho_5x15/manna-harbour_miryoku/keymap.c][layouts/community/ortho_5x15/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/ortho_5x15/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** planck_mit

The middle two columns including the middle 2u key, and the 2 keys on each end
of the bottom row are unused.

Keyboards supporting this layout: bm40hsrgb, contra, efreet, jj40, latin47ble, mt40, niu_mini, quark, zlant, dm9records/plaid, evyd13/eon40, handwired/aranck, handwired/heisenberg, kbdfans/kbd4x, planck/ez, planck/light, planck/rev1, planck/rev2, planck/rev3, planck/rev4, planck/rev5, planck/rev6, planck/thk, spaceman/pancake/feather, spaceman/pancake/promicro.

Example build command lines:

#+BEGIN_SRC sh :tangle no
make planck/ez:manna-harbour_miryoku:flash # planck ez
make planck/rev6:manna-harbour_miryoku:flash FORCE_LAYOUT=planck_mit # planck rev6, mit

#+END_SRC

**** [[../../layouts/community/planck_mit/manna-harbour_miryoku/config.h][layouts/community/planck_mit/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/planck_mit/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define LAYOUT_miryoku(\
K00,   K01,   K02,   K03,   K04,                 K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,                 K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,                 K25,   K26,   K27,   K28,   K29,\
N30,   N31,   K32,   K33,   K34,                 K35,   K36,   K37,   N38,   N39\
)\
LAYOUT_planck_mit(\
K00,   K01,   K02,   K03,   K04,   KC_NO, KC_NO, K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,   KC_NO, KC_NO, K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,   KC_NO, KC_NO, K25,   K26,   K27,   K28,   K29,\
KC_NO, KC_NO, K32,   K33,   K34,      KC_NO,     K35,   K36,   K37,   KC_NO, KC_NO\
)
#+END_SRC


**** [[../../layouts/community/planck_mit/manna-harbour_miryoku/keymap.c][layouts/community/planck_mit/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/planck_mit/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** split_3x5_3

Keyboards supporting this layout: arch_36, boardsource/microdox, centromere, crkbd, eek, miniaxe, minidox/rev1, pteron36, squiggle/rev1, suihankey/split/rev1.

Example build command lines:

#+BEGIN_SRC sh :tangle no
make crkbd:manna-harbour_miryoku:flash # crkbd
make minidox:manna-harbour_miryoku:flash # minidox
#+END_SRC


**** [[../../layouts/community/split_3x5_3/manna-harbour_miryoku/config.h][layouts/community/split_3x5_3/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/split_3x5_3/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define LAYOUT_miryoku(\
K00,   K01,   K02,   K03,   K04,          K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,          K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,          K25,   K26,   K27,   K28,   K29,\
N30,   N31,   K32,   K33,   K34,          K35,   K36,   K37,   N38,   N39\
)\
LAYOUT_split_3x5_3(\
K00,   K01,   K02,   K03,   K04,          K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,          K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,          K25,   K26,   K27,   K28,   K29,\
              K32,   K33,   K34,          K35,   K36,   K37\
)
#+END_SRC


**** [[../../layouts/community/split_3x5_3/manna-harbour_miryoku/keymap.c][layouts/community/split_3x5_3/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/split_3x5_3/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** split_3x6_3

The outer columns are unused.

Keyboards supporting this layout: centromere, crkbd, bastardkb/tbkmini.

Example build command lines:

#+BEGIN_SRC sh :tangle no
make bastardkb/tbkmini:manna-harbour_miryoku:flash # bastardkb/tbkmini
make crkbd:manna-harbour_miryoku:flash # crkbd
#+END_SRC


**** [[../../layouts/community/split_3x6_3/manna-harbour_miryoku/config.h][layouts/community/split_3x6_3/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/split_3x6_3/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define LAYOUT_miryoku(\
       K00,   K01,   K02,   K03,   K04,          K05,   K06,   K07,   K08,   K09,\
       K10,   K11,   K12,   K13,   K14,          K15,   K16,   K17,   K18,   K19,\
       K20,   K21,   K22,   K23,   K24,          K25,   K26,   K27,   K28,   K29,\
       N30,   N31,   K32,   K33,   K34,          K35,   K36,   K37,   N38,   N39\
)\
LAYOUT_split_3x6_3(\
KC_NO, K00,   K01,   K02,   K03,   K04,          K05,   K06,   K07,   K08,   K09,   KC_NO,\
KC_NO, K10,   K11,   K12,   K13,   K14,          K15,   K16,   K17,   K18,   K19,   KC_NO,\
KC_NO, K20,   K21,   K22,   K23,   K24,          K25,   K26,   K27,   K28,   K29,   KC_NO,\
                     K32,   K33,   K34,          K35,   K36,   K37\
)
#+END_SRC


**** [[../../layouts/community/split_3x6_3/manna-harbour_miryoku/keymap.c][layouts/community/split_3x6_3/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../layouts/community/split_3x6_3/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


** Keyboards

To use the keymap on a keyboard which does not support the layouts feature,
~LAYOUT_miryoku~ is defined as a macro mapping onto the keyboard's own ~LAYOUT~
macro, leaving the unused keys as ~KC_NO~.


*** atreus

Only the main 5x3 alphas and the inner 3 thumb keys are used.

To build for this keyboard,

#+BEGIN_SRC sh :tangle no
make atreus:manna-harbour_miryoku:flash
#+END_SRC


**** [[../../keyboards/atreus/keymaps/manna-harbour_miryoku/config.h][keyboards/atreus/keymaps/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/atreus/keymaps/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku(\
K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09,\
K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19,\
K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29,\
N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39\
)\
LAYOUT(\
K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09,\
K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19,\
K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29,\
XXX, XXX, XXX, K32, K33, K34,      K35, K36, K37, XXX, XXX, XXX\
)
#+END_SRC


**** [[../../keyboards/atreus/keymaps/manna-harbour_miryoku/keymap.c][keyboards/atreus/keymaps/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/atreus/keymaps/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** ergotravel

To build for this keyboard,

#+BEGIN_SRC sh :tangle no
make ergotravel:manna-harbour_miryoku:flash
#+END_SRC


**** [[../../keyboards/ergotravel/keymaps/manna-harbour_miryoku/config.h][keyboards/ergotravel/keymaps/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/ergotravel/keymaps/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku( \
     K00, K01, K02, K03, K04,                 K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,                 K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,                 K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,                 K35, K36, K37, N38, N39 \
) \
LAYOUT( \
XXX, K00, K01, K02, K03, K04, XXX,       XXX, K05, K06, K07, K08, K09, XXX, \
XXX, K10, K11, K12, K13, K14, XXX,       XXX, K15, K16, K17, K18, K19, XXX, \
XXX, K20, K21, K22, K23, K24, XXX,       XXX, K25, K26, K27, K28, K29, XXX, \
XXX, XXX, XXX, K32,      K33, K34,       K35, K36,      K37, XXX, XXX, XXX  \
)
#+END_SRC


**** [[../../keyboards/ergotravel/keymaps/manna-harbour_miryoku/keymap.c][keyboards/ergotravel/keymaps/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/ergotravel/keymaps/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** for_science

The top row is unused.

To build for this keyboard,

#+BEGIN_SRC sh :tangle no
make for_science:manna-harbour_miryoku:flash
#+END_SRC


**** [[../../keyboards/for_science/keymaps/manna-harbour_miryoku/config.h][keyboards/for_science/keymaps/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/for_science/keymaps/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku(\
K00, K01, K02, K03, K04,     K05, K06, K07, K08, K09,\
K10, K11, K12, K13, K14,     K15, K16, K17, K18, K19,\
K20, K21, K22, K23, K24,     K25, K26, K27, K28, K29,\
N30, N31, K32, K33, K34,     K35, K36, K37, N38, N39\
)\
LAYOUT(\
XXX, XXX, XXX, XXX, XXX,     XXX, XXX, XXX, XXX, XXX,\
K00, K01, K02, K03, K04,     K05, K06, K07, K08, K09,\
K10, K11, K12, K13, K14,     K15, K16, K17, K18, K19,\
K20, K21, K22, K23, K24,     K25, K26, K27, K28, K29,\
          K32, K33, K34,     K35, K36, K37\
)
#+END_SRC


**** [[../../keyboards/for_science/keymaps/manna-harbour_miryoku/keymap.c][keyboards/for_science/keymaps/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/for_science/keymaps/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** gergo

Only the main 5x3 alphas and the outer 3 thumb keys are used.

To build for this keyboard,

#+BEGIN_SRC sh :tangle no
make gergo:manna-harbour_miryoku:flash
#+END_SRC


**** [[../../keyboards/gergo/keymaps/manna-harbour_miryoku/config.h][keyboards/gergo/keymaps/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/gergo/keymaps/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku(\
     K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09,\
     K10, K11, K12, K13, K14,                          K15, K16, K17, K18, K19,\
     K20, K21, K22, K23, K24,                          K25, K26, K27, K28, K29,\
     N30, N31, K32, K33, K34,                          K35, K36, K37, N38, N39\
)\
LAYOUT_gergo(\
XXX, K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09, XXX,\
XXX, K10, K11, K12, K13, K14, XXX,                XXX, K15, K16, K17, K18, K19, XXX,\
XXX, K20, K21, K22, K23, K24, XXX, XXX,      XXX, XXX, K25, K26, K27, K28, K29, XXX,\
                    K32, K33, K34, XXX,      XXX, K35, K36, K37\
)
#+END_SRC


**** [[../../keyboards/gergo/keymaps/manna-harbour_miryoku/keymap.c][keyboards/gergo/keymaps/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/gergo/keymaps/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** handwired/dactyl_manuform/4x5

Only the main 5x3 alphas and the main 3 thumb keys are used.

To build for this keyboard,

#+BEGIN_SRC sh :tangle no
make handwired/dactyl_manuform/4x5:manna-harbour_miryoku:flash
#+END_SRC


**** [[../../keyboards/handwired/dactyl_manuform/4x5/keymaps/manna-harbour_miryoku/config.h][keyboards/handwired/dactyl_manuform/4x5/keymaps/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/handwired/dactyl_manuform/4x5/keymaps/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku(\
K00, K01, K02, K03, K04,                         K05, K06, K07, K08, K09,\
K10, K11, K12, K13, K14,                         K15, K16, K17, K18, K19,\
K20, K21, K22, K23, K24,                         K25, K26, K27, K28, K29,\
N30, N31, K32, K33, K34,                         K35, K36, K37, N38, N39\
)\
LAYOUT( \
K00, K01, K02, K03, K04,                         K05, K06, K07, K08, K09,\
K10, K11, K12, K13, K14,                         K15, K16, K17, K18, K19,\
K20, K21, K22, K23, K24,                         K25, K26, K27, K28, K29,\
     XXX, XXX,                                             XXX, XXX, \
               K32, K33,                         K36, K37, \
                         K34, XXX,     XXX, K35, \
                         XXX, XXX,     XXX, XXX \
)
#+END_SRC


**** [[../../keyboards/handwired/dactyl_manuform/4x5/keymaps/manna-harbour_miryoku/keymap.c][keyboards/handwired/dactyl_manuform/4x5/keymaps/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/handwired/dactyl_manuform/4x5/keymaps/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** handwired/dactyl_manuform/5x6

Only the main 5x3 alphas and the main 3 thumb keys are used.

To build for this keyboard,

#+BEGIN_SRC sh :tangle no
make handwired/dactyl_manuform/5x6:manna-harbour_miryoku:flash
#+END_SRC


**** [[../../keyboards/handwired/dactyl_manuform/5x6/keymaps/manna-harbour_miryoku/config.h][keyboards/handwired/dactyl_manuform/5x6/keymaps/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/handwired/dactyl_manuform/5x6/keymaps/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku(\
     K00, K01, K02, K03, K04,                         K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,                         K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,                         K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,                         K35, K36, K37, N38, N39 \
) \
LAYOUT_5x6( \
XXX, XXX, XXX, XXX, XXX, XXX,                         XXX, XXX, XXX, XXX, XXX, XXX, \
XXX, K00, K01, K02, K03, K04,                         K05, K06, K07, K08, K09, XXX, \
XXX, K10, K11, K12, K13, K14,                         K15, K16, K17, K18, K19, XXX, \
XXX, K20, K21, K22, K23, K24,                         K25, K26, K27, K28, K29, XXX, \
          XXX, XXX,                                             XXX, XXX, \
                    K32, K33,                         K36, K37, \
                              K34, XXX,     XXX, K35, \
                              XXX, XXX,     XXX, XXX \
)
#+END_SRC


**** [[../../keyboards/handwired/dactyl_manuform/5x6/keymaps/manna-harbour_miryoku/keymap.c][keyboards/handwired/dactyl_manuform/5x6/keymaps/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/handwired/dactyl_manuform/5x6/keymaps/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** keebio/iris

Only the main 5x3 alphas and the bottom 3 thumb keys are used.

To build for this keyboard,

#+BEGIN_SRC sh :tangle no
make keebio/iris/rev4:manna-harbour_miryoku:flash
#+END_SRC


**** [[../../keyboards/keebio/iris/keymaps/manna-harbour_miryoku/config.h][keyboards/keebio/iris/keymaps/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/keebio/iris/keymaps/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku(\
     K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09,\
     K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19,\
     K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29,\
     N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39\
)\
LAYOUT(\
XXX, XXX, XXX, XXX, XXX, XXX,                XXX, XXX, XXX, XXX, XXX, XXX,\
XXX, K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09, XXX,\
XXX, K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19, XXX,\
XXX, K20, K21, K22, K23, K24, XXX,      XXX, K25, K26, K27, K28, K29, XXX,\
                    K32, K33, K34,      K35, K36, K37\
)
#+END_SRC


**** [[../../keyboards/keebio/iris/keymaps/manna-harbour_miryoku/keymap.c][keyboards/keebio/iris/keymaps/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/keebio/iris/keymaps/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** keyboardio/atreus

Only the main 5x3 alphas and the inner 3 thumb keys are used.

To build for this keyboard,

#+BEGIN_SRC sh :tangle no
make keyboardio/atreus:manna-harbour_miryoku:flash
#+END_SRC


**** [[../../keyboards/keyboardio/atreus/keymaps/manna-harbour_miryoku/config.h][keyboards/keyboardio/atreus/keymaps/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/keyboardio/atreus/keymaps/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku( \
K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09, \
K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19, \
K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29, \
N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39 \
) \
LAYOUT( \
K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09, \
K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19, \
K20, K21, K22, K23, K24, XXX,      XXX, K25, K26, K27, K28, K29, \
XXX, XXX, XXX, K32, K33, K34,      K35, K36, K37, XXX, XXX, XXX \
)
#+END_SRC


**** [[../../keyboards/keyboardio/atreus/keymaps/manna-harbour_miryoku/keymap.c][keyboards/keyboardio/atreus/keymaps/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/keyboardio/atreus/keymaps/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** kyria

Only the main 5x3 alphas and the middle 3 lower thumb keys are used.

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/mapping/miryoku-kle-mapping-kyria.png]]

An alternative subset mapping is also provided with the thumb keys shifted one
position in the direction of thumb extension.  To select this mapping, append
~MIRYOKU_MAPPING=EXTENDED_THUMBS~ to the ~make~ command line when building.

[[https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/mapping/miryoku-kle-mapping-kyria-extended_thumbs.png]]


To build for this keyboard,

#+BEGIN_SRC sh :tangle no
make kyria:manna-harbour_miryoku:flash
make kyria:manna-harbour_miryoku:flash MIRYOKU_MAPPING=EXTENDED_THUMBS # extended thumb position
#+END_SRC


**** [[../../keyboards/kyria/keymaps/manna-harbour_miryoku/config.h][keyboards/kyria/keymaps/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/kyria/keymaps/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#if defined MIRYOKU_MAPPING_EXTENDED_THUMBS
#define LAYOUT_miryoku( \
     K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,                          K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,                          K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,                          K35, K36, K37, N38, N39 \
) \
LAYOUT( \
XXX, K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09, XXX, \
XXX, K10, K11, K12, K13, K14,                          K15, K16, K17, K18, K19, XXX, \
XXX, K20, K21, K22, K23, K24, XXX, XXX,      XXX, XXX, K25, K26, K27, K28, K29, XXX, \
               XXX, XXX, K32, K33, K34,      K35, K36, K37, XXX, XXX \
)
#else
#define LAYOUT_miryoku( \
     K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,                          K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,                          K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,                          K35, K36, K37, N38, N39 \
) \
LAYOUT( \
XXX, K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09, XXX, \
XXX, K10, K11, K12, K13, K14,                          K15, K16, K17, K18, K19, XXX, \
XXX, K20, K21, K22, K23, K24, XXX, XXX,      XXX, XXX, K25, K26, K27, K28, K29, XXX, \
               XXX, K32, K33, K34, XXX,      XXX, K35, K36, K37, XXX \
)
#endif
#+END_SRC


**** [[../../keyboards/kyria/keymaps/manna-harbour_miryoku/keymap.c][keyboards/kyria/keymaps/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/kyria/keymaps/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** lily58

Only the main 5x3 alphas and the inner 3 thumb keys are used.

To build for this keyboard,

#+BEGIN_SRC sh :tangle no
make lily58:manna-harbour_miryoku:flash
#+END_SRC


**** [[../../keyboards/lily58/keymaps/manna-harbour_miryoku/config.h][keyboards/lily58/keymaps/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/lily58/keymaps/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku(\
     K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09,\
     K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19,\
     K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29,\
     N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39\
)\
LAYOUT(\
XXX, XXX, XXX, XXX, XXX, XXX,                XXX, XXX, XXX, XXX, XXX, XXX,\
XXX, K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09, XXX,\
XXX, K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19, XXX,\
XXX, K20, K21, K22, K23, K24, XXX,      XXX, K25, K26, K27, K28, K29, XXX,\
               XXX, K32, K33, K34,      K35, K36, K37, XXX\
)
#+END_SRC


**** [[../../keyboards/lily58/keymaps/manna-harbour_miryoku/keymap.c][keyboards/lily58/keymaps/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/lily58/keymaps/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** moonlander

The main 5x3 alphas are used as usual. The primary, secondary, and tertiary
thumb keys are the closest piano key, middle piano key, and the innermost key of
the partial bottom row, respectively.  The remaining keys are unused.

To build for this keyboard,

#+BEGIN_SRC sh :tangle no
make moonlander:manna-harbour_miryoku:flash
#+END_SRC


**** [[../../keyboards/moonlander/keymaps/manna-harbour_miryoku/config.h][keyboards/moonlander/keymaps/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/moonlander/keymaps/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku(\
     K00, K01, K02, K03, K04,               K05, K06, K07, K08, K09,\
     K10, K11, K12, K13, K14,               K15, K16, K17, K18, K19,\
     K20, K21, K22, K23, K24,               K25, K26, K27, K28, K29,\
     N30, N31, K32, K33, K34,               K35, K36, K37, N38, N39\
)\
LAYOUT_moonlander(\
XXX, XXX, XXX, XXX, XXX, XXX, XXX,     XXX, XXX, XXX, XXX, XXX, XXX, XXX,\
XXX, K00, K01, K02, K03, K04, XXX,     XXX, K05, K06, K07, K08, K09, XXX,\
XXX, K10, K11, K12, K13, K14, XXX,     XXX, K15, K16, K17, K18, K19, XXX,\
XXX, K20, K21, K22, K23, K24,               K25, K26, K27, K28, K29, XXX,\
XXX, XXX, XXX, XXX, K32,      XXX,     XXX,      K37, XXX, XXX, XXX, XXX,\
                    K33, K34, XXX,     XXX, K35, K36\
)
#+END_SRC


**** [[../../keyboards/moonlander/keymaps/manna-harbour_miryoku/keymap.c][keyboards/moonlander/keymaps/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/moonlander/keymaps/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** redox_w

Only the main 5x3 alphas and the main 3 thumb keys are used.

To build for this keyboard,

#+BEGIN_SRC sh :tangle no
make redox_w:manna-harbour_miryoku:flash
#+END_SRC


**** [[../../keyboards/redox_w/keymaps/manna-harbour_miryoku/config.h][keyboards/redox_w/keymaps/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/redox_w/keymaps/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku(\
     K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09,\
     K10, K11, K12, K13, K14,                          K15, K16, K17, K18, K19,\
     K20, K21, K22, K23, K24,                          K25, K26, K27, K28, K29,\
     N30, N31, K32, K33, K34,                          K35, K36, K37, N38, N39\
)\
LAYOUT(\
XXX, XXX, XXX, XXX, XXX, XXX,                          XXX, XXX, XXX, XXX, XXX, XXX,\
XXX, K00, K01, K02, K03, K04, XXX,                XXX, K05, K06, K07, K08, K09, XXX,\
XXX, K10, K11, K12, K13, K14, XXX,                XXX, K15, K16, K17, K18, K19, XXX,\
XXX, K20, K21, K22, K23, K24, XXX, XXX,      XXX, XXX, K25, K26, K27, K28, K29, XXX,\
XXX, XXX, XXX, XXX,    K32,   K33, K34,      K35, K36,    K37,   XXX, XXX, XXX, XXX\
)
#+END_SRC

#+RESULTS:


**** [[../../keyboards/redox_w/keymaps/manna-harbour_miryoku/keymap.c][keyboards/redox_w/keymaps/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/redox_w/keymaps/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** sofle

To build for this keyboard,

#+BEGIN_SRC sh :tangle no
make sofle:manna-harbour_miryoku:flash
#+END_SRC


**** [[../../keyboards/sofle/keymaps/manna-harbour_miryoku/config.h][keyboards/sofle/keymaps/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/sofle/keymaps/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku(\
     K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09,\
     K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19,\
     K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29,\
     N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39\
)\
LAYOUT(\
XXX, XXX, XXX, XXX, XXX, XXX,                XXX, XXX, XXX, XXX, XXX, XXX,\
XXX, K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09, XXX,\
XXX, K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19, XXX,\
XXX, K20, K21, K22, K23, K24, XXX,      XXX, K25, K26, K27, K28, K29, XXX,\
          XXX, XXX, K32, K33, K34,      K35, K36, K37, XXX, XXX\
)
#+END_SRC


**** [[../../keyboards/sofle/keymaps/manna-harbour_miryoku/keymap.c][keyboards/sofle/keymaps/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/sofle/keymaps/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


*** torn

To build for this keyboard,

#+BEGIN_SRC sh :tangle no
make torn:manna-harbour_miryoku:flash
#+END_SRC


**** [[../../keyboards/torn/keymaps/manna-harbour_miryoku/config.h][keyboards/torn/keymaps/manna-harbour_miryoku/config.h]]

Contains subset mapping.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/torn/keymaps/manna-harbour_miryoku/config.h
// <<header>>

<<license-qmk>>

#pragma once

#define LAYOUT_miryoku( \
       K00,   K01,   K02,   K03,   K04,          K05,   K06,   K07,   K08,   K09, \
       K10,   K11,   K12,   K13,   K14,          K15,   K16,   K17,   K18,   K19, \
       K20,   K21,   K22,   K23,   K24,          K25,   K26,   K27,   K28,   K29, \
       N30,   N31,   K32,   K33,   K34,          K35,   K36,   K37,   N38,   N39 \
) \
LAYOUT_split_3x6_4( \
KC_NO, K00,   K01,   K02,   K03,   K04,          K05,   K06,   K07,   K08,   K09,   KC_NO, \
KC_NO, K10,   K11,   K12,   K13,   K14,          K15,   K16,   K17,   K18,   K19,   KC_NO, \
KC_NO, K20,   K21,   K22,   K23,   K24,          K25,   K26,   K27,   K28,   K29,   KC_NO, \
              KC_NO, K32,   K33,   K34,          K35,   K36,   K37,   KC_NO \
)
#+END_SRC

#+RESULTS:


**** [[../../keyboards/torn/keymaps/manna-harbour_miryoku/keymap.c][keyboards/torn/keymaps/manna-harbour_miryoku/keymap.c]]

Required by the build system.

#+BEGIN_SRC C :main no :noweb yes :padline no :tangle ../../keyboards/torn/keymaps/manna-harbour_miryoku/keymap.c
// <<header>>

<<license-qmk>>
#+END_SRC


** Customisation

To add customisations to a keyboard or layout while importing the miryoku
keymap, copy ~config.h~ and ~keymap.c~ from the keyboard or layout's
~manna-harbour_miryoku/~ directory to a new directory, and create ~rules.mk~
containing ~USER_NAME := manna-harbour_miryoku~.  The miryoku keymap will be
imported and customisations can be added to those files as usual.  Keycodes can
be added to unused keys by editing ~LAYOUT_miryoku~ in ~config.h~.

For an unsupported keyboard or layout, do as above with a similar keyboard or
layout and modify ~LAYOUT_miryoku~ in ~config.h~ referring to the keyboard or
layout's ~LAYOUT~ macro.


*** Examples

To use any of the examples, create a new branch from the miryoku development
branch and follow the same steps as seen in the commit messages and code changes
in the examples, making the appropriate changes for your keyboard and desired
customisations.


**** Add Layers

- https://github.com/manna-harbour/qmk_firmware/commits/miryoku-examples-add-layers/keyboards/crkbd/keymaps/miryoku-examples-add-layers


* Experimental Features


** Bilateral Combinations

- [[https://github.com/manna-harbour/qmk_firmware/issues/29][Bilateral Combinations]]


** Retro Shift

- [[https://github.com/manna-harbour/qmk_firmware/issues/33][Retro Shift]]


* Documentation                                                  :noexport_1:


** QMK

- https://docs.qmk.fm/
- https://docs.qmk.fm/#/config_options
- https://docs.qmk.fm/#/feature_advanced_keycodes
- https://docs.qmk.fm/#/feature_auto_shift
- https://docs.qmk.fm/#/feature_layers
- https://docs.qmk.fm/#/feature_layouts
- https://docs.qmk.fm/#/feature_mouse_keys
- https://docs.qmk.fm/#/feature_userspace
- https://docs.qmk.fm/#/getting_started_introduction
- https://docs.qmk.fm/#/getting_started_make_guide
- https://docs.qmk.fm/#/keycodes
- https://docs.qmk.fm/#/mod_tap
- https://docs.qmk.fm/#/tap_hold


** Org Mode

- https://orgmode.org/
- https://orgmode.org/manual/Tables.html
- https://orgmode.org/manual/Working-with-Source-Code.html


* Contact

For feature requests or issues with code or documentation please
[[https://github.com/manna-harbour/qmk_firmware/issues/new][open an issue]].

For more general discussion please [[https://github.com/manna-harbour/manna-harbour/tree/main/contact][contact Manna Harbour]].

[[https://github.com/manna-harbour][https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/logos/manna-harbour-boa-32.png]]
