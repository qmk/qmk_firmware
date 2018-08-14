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

// Layers
enum layers {
  _SWRKMN = 0,
  _HWRKMN,
  _LOWER,
  _RAISE,
  _ADJUST,
  _DIABLO
};



enum custom_keycodes {
  KC_EPRM = SAFE_RANGE,
  KC_SWRK,
  KC_HWRK,
  KC_VRSN,
  JJ_COPY,
  JJ_PASTE,
  JJ_ARRW,
  MC_LOCK,
  KC_DIABLO_CLEAR,
  KC_NMPD
//  UC_FLIP
};

// Space Cadet Hyper/Meh and [/]
#define HYP_LBK ALL_T(KC_LBRACKET)
#define MEH_RBK MEH_T(KC_RBRACKET)

#define KC_LWSP LT(_LOWER, KC_SPACE)
#define KC_RSEN LT(_RAISE, KC_ENTER)
#define KC_ADJS TT(_ADJUST)

#define XXXXXXX KC_NO
#define _______ KC_TRNS

#ifdef TAP_DANCE_ENABLE
enum {
  TD_D3_1 = 0,
  TD_D3_2,
  TD_D3_3,
  TD_D3_4
};
#endif // TAP_DANCE_ENABLE

// Custom Keycodes for Diablo 3 layer
// But since TD() doesn't work when tap dance is disabled
// We use custom codes here, so we can substitute the right stuff
#ifdef TAP_DANCE_ENABLE
#define KC_D3_1 TD(TD_D3_1)
#define KC_D3_2 TD(TD_D3_2)
#define KC_D3_3 TD(TD_D3_3)
#define KC_D3_4 TD(TD_D3_4)
#else // TAP_DANCE_ENABLE
#define KC_D3_1 KC_1
#define KC_D3_2 KC_2
#define KC_D3_3 KC_3
#define KC_D3_4 KC_4
#endif // TAP_DANCE_ENABLE

//define diablo macro timer variables
extern uint16_t diablo_timer[4];
extern uint8_t diablo_times[];
extern uint8_t diablo_key_time[4];


void run_diablo_macro_check(void);


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

#define ______________________NUMBER_LEFT________________________       KC_1,     KC_2,           KC_3,           KC_4,           KC_5
#define ______________________NUMBER_RIGHT_______________________       KC_6,     KC_7,           KC_8,           KC_9,           KC_0

#define ______________________SPECIAL_LEFT_______________________       KC_EXLM,  KC_AT,          KC_HASH,        KC_DLR,         KC_PERC
#define ______________________SPECIAL_RIGHT______________________       KC_CIRC,  KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN

#define _______________________FUNC_LEFT_________________________       KC_F1,    KC_F2,          KC_F3,          KC_F4,          KC_F5
#define _______________________FUNC_RIGHT________________________       KC_F6,    KC_F7,          KC_F8,          KC_F9,          KC_F10

#define _________________________________________________________       KC_TRNS,  KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS
#define XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       KC_NO,    KC_NO,          KC_NO,          KC_NO,          KC_NO

#define _______________________SWORKMAN_L1_______________________       KC_Q,     KC_W,           KC_E,           KC_R,           KC_T
#define _______________________SWORKMAN_L2_______________________       KC_A,     SFT_T(KC_S),    GUI_T(KC_D),    ALT_T(KC_F),    KC_G
#define _______________________SWORKMAN_L3_______________________ CTL_T(KC_Z),    KC_X,           KC_C,           KC_V,           KC_B

#define _______________________SWORKMAN_R1_______________________       KC_Y,     KC_U,           KC_I,           KC_O,           KC_P
#define _______________________SWORKMAN_R2_______________________       KC_H,     ALT_T(KC_J),    GUI_T(KC_K),    SFT_T(KC_L),    KC_SCLN
#define _______________________SWORKMAN_R3_______________________       KC_N,     KC_M,           KC_COMM,        KC_DOT,         CTL_T(KC_SLASH)

// Hardware Driven Workman
#define _______________________HWORKMAN_L1_______________________       KC_Q,     KC_D,           KC_R,           KC_W,           KC_B
#define _______________________HWORKMAN_L2_______________________       KC_A,     SFT_T(KC_S),    GUI_T(KC_H),    ALT_T(KC_T),    KC_G
#define _______________________HWORKMAN_L3_______________________ CTL_T(KC_Z),    KC_X,           KC_M,           KC_C,           KC_V

#define _______________________HWORKMAN_R1_______________________       KC_J,     KC_F,           KC_U,           KC_P,           KC_SCLN
#define _______________________HWORKMAN_R2_______________________       KC_Y,     ALT_T(KC_N),    GUI_T(KC_E),    SFT_T(KC_O),    KC_I
#define _______________________HWORKMAN_R3_______________________       KC_K,     KC_L,           KC_COMM,        KC_DOT,         CTL_T(KC_SLASH)

#define ___________________ERGODOX_BOTTOM_LEFT___________________    TT(_DIABLO), TT(_ADJUST),    XXXXXXX,        KC_UP,          KC_LEFT
#define ___________________ERGODOX_BOTTOM_RIGHT__________________    KC_RIGHT,    KC_DOWN,        TT(_RAISE),     TT(_LOWER),     TT(_ADJUST)

//                                                                    LEFT        |       RIGHT
#define ______________________ERGODOX_THUMBS_____________________ KC_APP,KC_HOME,    KC_PGUP,KC_ESC,           \
                                                                          KC_END,    KC_PGDOWN,                \
                                                       KC_LWSP,KC_BSPACE,JJ_COPY,    JJ_PASTE,KC_TAB,KC_RSEN
