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

/*
#define LAYOUT_atreus_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
     KC_ESC,  ________________NUMBER_LEFT________________,                       ________________NUMBER_RIGHT_______________, KC_MINS, \
     KC_TAB , K01,    K02,     K03,      K04,     K05,                           K06,     K07,     K08,     K09,     K0A,     KC_BSLS, \
     KC_C1R3, K11,    K12,     K13,      K14,     K15,                           K16,     K17,     K18,     K19,     K1A,     KC_QUOT, \
     OS_LSFT, CTL_T(K21), K22, K23,      K24,     K25,     OS_LALT,     OS_RGUI, K26,     K27,     K28,     K29,  CTL_T(K2A), OS_RSFT, \
                             LT(_LOWER,KC_GRV), KC_SPC,  KC_BSPC,         KC_DEL,  KC_ENT,  RAISE                                      \
  )
#define LAYOUT_iris_base_wrapper(...)       LAYOUT_iris_base(__VA_ARGS__)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_iris_base_wrapper(
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
  ),
*/
 
// can move to keymap.h
// modtaps
#define MT_LPRN GUI_T(KC_LPRN)
#define MT_Z MT(MOD_LSFT, KC_Z)
#define MT_ESC MT(MOD_LCTL, KC_ESC)
#define MT_TAB MT(MOD_LGUI, KC_TAB)
#define MT_EQL MT(MOD_RALT, KC_EQL)
#define MT_ENT MT(MOD_RCTL, KC_ENT)
#define MT_QUOT MT(MOD_RGUI, KC_QUOT)
#define MT_SLSH MT(MOD_RSFT, KC_SLSH)
#define MT_LBRC MT(MOD_LALT, KC_LBRC)
#define MT_RBRC MT(MOD_LSFT, KC_RBRC)
#define MT_MINS MT(MOD_RSFT, KC_MINS)
// layertaps
#define LT_A LT(_EDITOR, KC_A)
#define LT_ESC LT(_EDITOR, KC_ESC)
#define LT_TAB LT(_SECRET, KC_TAB)
#define LT_SCLN LT(_NUMBER, KC_SCLN)
#define LT_DOT LT(_F_KEYS, KC_DOT)
#define LT_BSPC LT(_NUMBER, KC_BSPC)
#define LT_SPC LT(_SYMBOL, KC_SPC)


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
// MOD/LAYER TAPS
// Mods are in the outside corners (commonly SHIFT, CTRL, GUI, ALT on a "normal" keyboard but encroaching alphas
// "Z" and "/ ?" are SHIFT when held. SHIFT is also accessed when fourth key in from other side on the bottom row is held.
// CTRL is either outer key on the bottom row; next inner keys are GUI, the third pair ALT.
// Layers are on the four inner keys and under each pinky
// "EDITOR" and "NUMBER" access keys are doubled (('A',left outer thumb),(left inner thumb,';')

// KEYMAP
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( /* Qwerty */
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    LT_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    LT_SCLN,
    MT_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, LT_DOT,  MT_SLSH,
    MT_ESC,  MT_TAB,  MT_LBRC, MT_RBRC, LT_BSPC, LT_ESC,  LT_TAB,  LT_SPC,  MT_MINS, MT_EQL,  LM_QUOT, MT_ENT
  ),
  [_EDITOR] = LAYOUT( /* LT_A, LT_ESC */
    KC_GRV,  _______, KC_END,  _______, KC_TAB,                    _______, _______, KC_INS,  _______, KC_PGUP,
    KC_HOME, _______, KC_DELT, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT, 
    _______, _______, _______, _______, _______,                   KC_PGDN, _______, _______, _______, KC_BSLS,
    _______, _______, _______, _______, _______, _______, KC_ENT,  _______, _______, _______, _______, _______
  ),
  [_NUMBER] = LAYOUT( /* LT_SCLN, LT_BSPC */
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  
    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      _______, KC_4,    KC_5,    KC_6,    _______,
    _______, _______, _______, _______, _______,                   _______, KC_1,    KC_2,    KC_3,    KC_BSLS,
    _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_0,    KC_0,    KC_DOT,  _______, _______
  ),
  [_SYMBOL] = LAYOUT( /* LT_SPC */
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                   _______, _______, _______, _______, KC_COLN, 
    _______, _______, _______, _______, _______,                   _______, _______, _______, _______, KC_BSLS, 
    _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______
  ),
  [_F_KEYS] = LAYOUT( /* LT_DOT */
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
        case LM_QUOT:   
            if (record->event.pressed) {
                key_timer = timer_read();
                layer_on(_NUMBER);
                register_mods(MOD_BIT(KC_RGUI));
            } else {
                unregister_mods(MOD_BIT(KC_RGUI));
                layer_off(_NUMBER);
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    register_code(KC_QUOT);
                    unregister_code(KC_QUOT);
                }
            }
            return false; break;
    }
    return true;
};
