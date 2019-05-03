/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// Layer shorthand
enum layer {
  _QWERTY,
  _LOWER,
  _SUPER
};
#define QWERTY MO(_QWERTY)
#define LOWER MO(_LOWER)
#define SUPER MO(_SUPER)

//Tap Dance Declarations
enum {
  TD_F1 = 0
  ,TD_F5
};

enum custom_keycodes {
SEL = SAFE_RANGE
,UPD
,WALK
,MARON
,CLAP
,ADS
,AGREE
,AINT
,POPCRN
,SADMJ
,CTRL3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* 1uGrid
 * .-----------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | ]      | Y      | U      | I      | O      | P      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | S      | D      | F      | G      | HOME   | PG UP  | H      | J      | K      | L      | ;      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | END    | PG DN  | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | FN     | LALT   | SPACE  | SPACE  | SPACE  | SPACE  | SPACE  | SPACE  | RIGHT  | DOWN   | UP     | RIGHT  |
 * '-----------------------------------------------------------------------------------------------------------------------------'
 */

 [_QWERTY] = LAYOUT_ortho_5x14 (
  KC_ESC,  TD(TD_F1),KC_2,   KC_3,    KC_4,    TD(TD_F5),KC_HOME, KC_PGUP,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_END,   KC_PGDN,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
  KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_MINS,  KC_EQL,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT), \
  KC_LCTL, KC_LGUI, KC_LALT, SUPER, LOWER,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_LEFT, KC_RGHT, KC_DOWN, KC_UP, KC_RCTL  \
 ),

/* FUNCTION
 * .-----------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------------------------'
 */


 [_LOWER] = LAYOUT_ortho_5x14 (
  KC_GRAVE, KC_F1	, KC_F2, KC_F3, KC_F4, KC_F5, KC_F11, KC_F12, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_DEL, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, _______, _______, KC_UNDS, KC_PLUS, _______, _______, _______, \
  _______, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______, KC_MINS, KC_EQL, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END, KC_PGDN, KC_PGUP, _______
 ),
  [_SUPER] = LAYOUT_ortho_5x14 (
  RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, SEL, UPD, CTRL3, ADS, _______, _______, _______, _______, _______, CLAP, MARON, WALK, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, AGREE, AINT, POPCRN, SADMJ, _______, \
  RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_MSTP, KC_MPLY, _______
 )
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_F1]  = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_F1)
  ,[TD_F5]  = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_F5)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    if (record->event.pressed) {
        switch(keycode) {
            case SEL:
                SEND_STRING("SELECT TOP 1000 * FROM ");
                return false;
            case UPD:
                SEND_STRING("UPDATE "SS_TAP(X_ENTER)" SET "SS_TAP(X_ENTER)"WHERE "); // UPDATE STATEMENT
                return false;
            case WALK:
                SEND_STRING("https://i.imgur.com/mWQRAFU.gifv"SS_TAP(X_ENTER)); //walking into work
                return false;
            case MARON:
                SEND_STRING("https://i.imgur.com/7xweg.jpg"SS_TAP(X_ENTER)); //Maroney face
                return false;
            case CLAP:
                SEND_STRING("https://i.imgur.com/i6r5VDO.gifv"SS_TAP(X_ENTER)) ; // Clapping Intensifies
                return false;
            case ADS:
                 SEND_STRING(SS_DOWN(X_LCTRL)SS_TAP(X_C)SS_UP(X_LCTRL)SS_TAP(X_END)SS_TAP(X_ENTER)"SELECT TOP 1000 * FROM "SS_DOWN(X_LCTRL)SS_TAP(X_V)SS_UP(X_LCTRL)SS_TAP(X_END)SS_DOWN(X_LSHIFT)SS_TAP(X_HOME)SS_UP(X_LSHIFT)SS_TAP(X_F5)SS_TAP(X_BSPACE)SS_TAP(X_HOME)SS_TAP(X_BSPACE)); //SEL TOP 1K FOR ADS
                return false;
            case AGREE:
                SEND_STRING("https://i.imgur.com/EucIfYY.gifv"SS_TAP(X_ENTER)); // Agreement
                return false;
            case AINT:
                SEND_STRING("https://i.imgur.com/nTXnixm.jpg"SS_TAP(X_ENTER)); // Ain't nobody got time for that
                return false;
            case POPCRN:
                SEND_STRING("https://i.imgur.com/0hQyd5L.gifv"SS_TAP(X_ENTER)); // Popcorn
                return false;
            case SADMJ:
                SEND_STRING("https://i.imgur.com/YLyEJB7.jpg"SS_TAP(X_ENTER)); // Sad MJ
                return false;
            case CTRL3:
                SEND_STRING(SS_DOWN(X_LCTRL)SS_TAP(X_3)SS_UP(X_LCTRL)); // CTRL+3
                return false;

        }
    }
    return true;
};
