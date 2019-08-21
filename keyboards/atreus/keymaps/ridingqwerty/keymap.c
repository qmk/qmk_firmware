/* Copyright 2019 George Koenig
 *
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
#include "ridingqwerty.h"

/*                                                         Atreus      
        ┏━━━━━━━━┯━━━━━━━━┯━━━━━━━━┯━━━━━━━━┯━━━━━━━━┓                 ┏━━━━━━━━┯━━━━━━━━┯━━━━━━━━┯━━━━━━━━┯━━━━━━━━┓
        ┃   Q    │   W    │   E    │   R    │   T    ┃                 ┃   Y    │   U    │   I    │   O    │   P    ┃
        ┠────────┼────────┼────────┼────────┼────────┨                 ┠────────┼────────┼────────┼────────┼────────┨
       /┃  ¶ A   │   S    │   D    │   F    │   G    ┃                 ┃   H    │   J    │   K    │   L    │  🔢 ;  ┃
        ┠────────┼────────┼────────┼────────┼────────┞━━━━━━━━┳━━━━━━━━┞────────┼────────┼────────┼────────┼────────┨
       /┃  ⇧ Z   │   X    │   C    │   V    │   B    │        ┃        │   N    │   M    │   ,    │  𝔽 .   │  ⇧ /   ┃
        ┠────────┼────────┼────────┼────────┼────────┤  ¶ ⎋   ┃  ❦ ⇥   ├────────┼────────┼────────┼────────┼────────┨
        ┃  ⎈ ⎋   │  ⌘ ⇥   │  ⎇ [   │  ⇧ ]   │ 🔢 ⌫   │        ┃        │  ★ ␣   │  ⇧ -   │  ⎇ =   │  ⌘ '   │  ⎈ ↵   ┃
        ┗━━━━━━━━┷━━━━━━━━┷━━━━━━━━┷━━━━━━━━┷━━━━━━━━┷━━━━━━━━┻━━━━━━━━┷━━━━━━━━┷━━━━━━━━┷━━━━━━━━┷━━━━━━━━┷━━━━━━━━┛
                    MODS                   //              LAYERS              //                  MODS           //
*/

#ifdef LAYOUT
#undef LAYOUT
#define LAYOUT( \
    K00,   K01,   K02,   K03,   K04,                 K40,   K41,   K42,   K43,   K44, \
    K10,   K11,   K12,   K13,   K14,                 K50,   K51,   K52,   K53,   K54, \
    K20,   K21,   K22,   K23,   K24,                 K60,   K61,   K62,   K63,   K64, \
    K30,   K31,   K32,   K33,   K34,   K35,   K70,   K71,   K72,   K73,   K74,   K75  \
) { \
  { K00, K01, K02, K03, K04, KC_NO }, \
  { K10, K11, K12, K13, K14, KC_NO }, \
  { K20, K21, K22, K23, K24, KC_NO }, \
  { K30, K31, K32, K33, K34, K35   }, \
  { K44, K43, K42, K41, K40, KC_NO }, \
  { K54, K53, K52, K51, K50, KC_NO }, \
  { K64, K63, K62, K61, K60, KC_NO }, \
  { K75, K74, K73, K72, K71, K70   }  \
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( /* Qwerty */
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    ED_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    NM_SCLN,
    LS_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, FK_DOT,  RS_SLSH,
    LC_ESC,  LG_TAB,  LA_LBRC, LS_RBRC, NM_BSPC, ED_ESC,  SC_TAB,  SM_SPC,  RS_MINS, RA_EQL,  RG_QUOT, RC_ENT
  ),
  [_EDITOR] = LAYOUT( /* ED_A, ED_ESC */
    KC_GRV,  _______, KC_END,  _______, KC_TAB,                    _______, _______, KC_INS,  _______, KC_PGUP,
    KC_HOME, _______, KC_DELT, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT, 
    _______, _______, _______, _______, _______,                   KC_PGDN, _______, _______, _______, KC_BSLS,
    _______, _______, _______, _______, _______, _______, KC_ENT,  _______, _______, _______, _______, _______
  ),
  [_NUMBER] = LAYOUT( /* NM_SCLN, NM_BSPC */
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  
    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      _______, KC_4,    KC_5,    KC_6,    _______,
    _______, _______, _______, _______, _______,                   _______, KC_1,    KC_2,    KC_3,    KC_BSLS,
    _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_0,    KC_0,    KC_DOT,  _______, _______
  ),
  [_SYMBOL] = LAYOUT( /* SM_SPC */
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                   _______, _______, _______, _______, KC_COLN, 
    _______, _______, _______, _______, _______,                   _______, _______, _______, _______, KC_BSLS, 
    _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______
  ),
  [_F_KEYS] = LAYOUT( /* FK_DOT */
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  
    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                    _______, _______, _______, _______, KC_F11,
    KC_F11,  KC_F12,  _______, _______, _______,                   _______, _______, _______, _______, KC_F12,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [_SECRET] = LAYOUT( /* shhhh... */
    RESET,   _______, _______, RUSTY,   FUEL,                      KC_F13,  _______, _______, _______, _______,
    AR1ST,   SYSNOC,  _______, _______, _______,                   _______, _______, _______, OS_LAB,  _______,
    CDLOCAL, _______, C0RE,    VAXIS,   _______,                   _______, MUNKY,   _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [_FINAL] = LAYOUT( /* . */
    _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};

// custom tap/hold keys
uint16_t key_timer;
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case RG_QUOT:   
            if (record->event.pressed) {
                key_timer = timer_read();
                layer_on(_NUMBER);
                register_mods(MOD_BIT(KC_RGUI));
            } else {
                unregister_mods(MOD_BIT(KC_RGUI));
                layer_off(_NUMBER);
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    tap_code(KC_QUOT);
                }
            }
            return false; break;
    }
    return true;
};
