/*
Copyright 2018 Jacob Jerrell <jacob.jerrell@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"
// #include "sendstring_workman.h" // removed this because I think it messed with macros... then I removed the macros

// Layers
#define _HWRKMN    0
#define _SWRKMN    1
#define _NUMPAD    2
#define _MOUSE     3
#define _TOOLS     4
#define _DIABLOII  5
#define _DIABLOIII 6

enum custom_keycodes {
  KC_EPRM = SAFE_RANGE,
  KC_SWRK,
  KC_HWRK,
  KC_VRSN,
  JJ_COPY,
  JJ_PASTE,
  JJ_ARRW,
  MC_LOCK,
};

// Space Cadet Hyper/Meh and [/]
#define HYP_LBK ALL_T(KC_LBRACKET)
#define MEH_RBK MEH_T(KC_RBRACKET)

#define XXXXXXX KC_NO

#define LAYOUT_ergodox_pretty_wrapper(...) LAYOUT_ergodox_pretty(__VA_ARGS__)

/* Pretty Layout
.---------------------------------------------.         .---------------------------------------------.
|   1   |  2  |  3  |  4  |  5  |  6  |   7   |         !   8   |  9  |  10 |  11 |  12 |  13 |   14  |
!-------+-----+-----+-----+-----+-------------!         !-------+-----+-----+-----+-----+-----+-------!
|   15  |  16 |  17 |  18 |  19 |  20 |   21  |         !   22  |  23 |  24 |  25 |  26 |  27 |   28  |
!-------+-----+-----+-----x-----x-----!       !         !       !-----x-----x-----+-----+-----+-------!
|   29  |  30 |  31 |  32 |  33 |  34 |-------!         !-------!  35 |  36 |  37 |  38 |  39 |   40  |
!-------+-----+-----+-----x-----x-----!       !         !       !-----x-----x-----+-----+-----+-------!
|   41  |  42 |  43 |  44 |  45 |  46 |   47  |         !   48  |  49 |  50 |  51 |  52 |  53 |   54  |
'-------+-----+-----+-----+-----+-------------'         '-------------+-----+-----+-----+-----+-------'
 |  55  |  56 |  57 |  58 |  59 | .---------------. .---------------. !  60 |  61 |  62 |  63 |   64 |
 '------------------------------' |   65  |   66  | !   67  |   68  | '------------------------------'
                          .-------+-------+-------! !-------+-------+-------.
                          !       !       |   69  | !   70  |       !       !
                          !       !       !-------! !-------!       !       !
                          |   71  |   72  |   73  | !   74  |   75  |   76  |
                          '-----------------------' '-----------------------'
*/

#define _____________________ERGODOX_TOP_LEFT__________________ KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, JJ_ARRW
#define _____________________ERGODOX_TOP_RIGHT_________________ KC_MINUS, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQUAL
#define _____________________ERGODOX_BOTTOM_LEFT_______________ TG(_MOUSE), TG(_NUMPAD), SH_MON, KC_UP,   KC_LEFT
#define _____________________ERGODOX_BOTTOM_RIGHT______________ KC_RIGHT,   KC_DOWN,     TO(_DIABLOII),    TO(_DIABLOIII), TT(_TOOLS)

//                                                  LEFT        |       RIGHT
#define _____________ERGODOX_THUMBS____________ KC_APP,KC_HOME,    KC_PGUP,KC_ESC,           \
                                                        KC_END,    KC_PGDOWN,                \
                                    KC_SPACE,KC_BSPACE,JJ_COPY,    JJ_PASTE,KC_TAB,KC_ENTER

// Software Driven Workman (basically HW QWERTY but I'm a purist)
/*
#define ______________SWORKMAN_L1______________       WK_Q,     WK_D,           WK_R,           WK_W,           WK_B
#define ______________SWORKMAN_L2______________       WK_A,     SFT_T(WK_S),    GUI_T(WK_H),    ALT_T(WK_T),    WK_G
#define ______________SWORKMAN_L3______________ CTL_T(WK_Z),    WK_X,           WK_M,           WK_C,           WK_V

#define ______________SWORKMAN_R1______________       WK_J,     WK_F,           WK_U,           WK_P,           WK_SCLN
#define ______________SWORKMAN_R2______________       WK_Y,     ALT_T(WK_N),    GUI_T(WK_E),    SFT_T(WK_O),    WK_I
#define ______________SWORKMAN_R3______________       WK_K,     WK_L,           KC_COMM,        KC_DOT,         CTL_T(KC_SLASH)
*/

#define ______________SWORKMAN_L1______________       KC_Q,     KC_W,           KC_E,           KC_R,           KC_T
#define ______________SWORKMAN_L2______________       KC_A,     SFT_T(KC_S),    GUI_T(KC_D),    ALT_T(KC_F),    KC_G
#define ______________SWORKMAN_L3______________ CTL_T(KC_Z),    KC_X,           KC_C,           KC_V,           KC_B

#define ______________SWORKMAN_R1______________       KC_Y,     KC_U,           KC_I,           KC_O,           KC_P
#define ______________SWORKMAN_R2______________       KC_H,     ALT_T(KC_J),    GUI_T(KC_K),    SFT_T(KC_L),    KC_SCLN
#define ______________SWORKMAN_R3______________       KC_N,     KC_M,           KC_COMM,        KC_DOT,         CTL_T(KC_SLASH)

// Hardware Driven Workman
#define ______________HWORKMAN_L1______________       KC_Q,     KC_D,           KC_R,           KC_W,           KC_B
#define ______________HWORKMAN_L2______________       KC_A,     SFT_T(KC_S),    GUI_T(KC_H),    ALT_T(KC_T),    KC_G
#define ______________HWORKMAN_L3______________ CTL_T(KC_Z),    KC_X,           KC_M,           KC_C,           KC_V

#define ______________HWORKMAN_R1______________       KC_J,     KC_F,           KC_U,           KC_P,           KC_SCLN
#define ______________HWORKMAN_R2______________       KC_Y,     ALT_T(KC_N),    GUI_T(KC_E),    SFT_T(KC_O),    KC_I
#define ______________HWORKMAN_R3______________       KC_K,     KC_L,           KC_COMM,        KC_DOT,         CTL_T(KC_SLASH)
