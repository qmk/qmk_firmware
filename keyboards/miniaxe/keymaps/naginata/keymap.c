/* Copyright 2018 ENDO Katsuhiro <ka2hiro@curlybracket.co.jp>
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
// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

// Defines the keycodes used by our macros in process_record_user
enum keymap_layers {
  _QWERTY,
// 薙刀式
  _NAGINATA, // 薙刀式入力レイヤー
  _NGEDITL, // 薙刀式編集レイヤー
  _NGEDITR, // 薙刀式編集レイヤー
// 薙刀式
  _LOWER,
  _RAISE,
  _ADJUST,
};

// 薙刀式
enum combo_events {
  NAGINATA_ON_CMB,
};

const uint16_t PROGMEM ngon_combo[] = {KC_H, KC_J, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [NAGINATA_ON_CMB] = COMBO_ACTION(ngon_combo),
};

// IME ONのcombo
void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case NAGINATA_ON_CMB:
      if (pressed && !naginata_state()) {
        naginata_on();
      }
      break;
  }
}
// 薙刀式

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define SFTSPC  LSFT_T(KC_SPC)
// 薙刀式
// 編集モードを追加する場合
#define MC(A) C(KC_##A)
#define MS(A) S(KC_##A)
#define MG(A) G(KC_##A)
// 薙刀式


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   /  |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               | GUI  | LOWER|Ctrl/Esc|          |Spc/Sft| RAISE|Alt/BkSp |
 *               `--------------------'           `--------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
                    KC_LGUI, LOWER,   SFTSPC,       SFTSPC,  RAISE,   MT(MOD_LALT, KC_BSPC)  \
),

// 薙刀式
[_NAGINATA] = LAYOUT( \
  NG_Q,    NG_W,    NG_E,    NG_R,    KC_LEFT,      KC_RGHT, NG_U,    NG_I,    NG_O,    NG_P,    \
  NG_A,    NG_S,    NG_D,    NG_F,    NG_G,         NG_H,    NG_J,    NG_K,    NG_L,    NG_SCLN, \
  NG_Z,    NG_X,    NG_C,    NG_V,    NG_B,         NG_N,    NG_M,    NG_COMM, NG_DOT,  NG_SLSH, \
                    KC_LGUI, LOWER,   NGSHFT,       NGSHFT,  RAISE,    MT(MOD_LALT, KC_BSPC)  \
),

[_NGEDITL] = LAYOUT( \
  MG(DOWN),MG(UP),   KC_NO,   KC_NO,   CHR10,        KC_NO,    KC_NO,   KC_NO,   KC_NO,  KC_NO, \
  MC(Y),   MC(S),    KC_PGDN, KC_PGUP, CHR20,        KC_NO,    KC_NO,   KC_NO,   KC_NO,  KC_NO, \
  MC(Z),   MC(X),    MC(C),   MC(V),   CHR30,        KC_NO,    KC_NO,   KC_NO,   KC_NO,  KC_NO, \
                    _______, _______, _______,      _______,  _______, _______\
),

[_NGEDITL] = LAYOUT( \
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_HOME,  MG(DEL), KC_NO,   KC_DEL, KC_ESC, \
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,    KC_UP,   MS(UP),  UP5,    KC_F7, \
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_END,   KC_DOWN, MS(DOWN),DOWN5,  KC_F6, \
                    _______, _______, _______,      _______,  _______, _______\
),
// 薙刀式

/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   (  |   )  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab |   _  |   +  |  |   |  ~   |           |   :  |   "  |   >  |   {  |   }  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Caps|   -  |   =  |  \   |  `   |           |   ;  |   '  |   <  |   [  |   ]  |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               |      | LOWER|      |           |  Esc | RAISE|      |
 *               `--------------------'           `--------------------'
 */
[_RAISE] = LAYOUT( \
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, \
  KC_TAB,  KC_UNDS, KC_PLUS, KC_PIPE, KC_TILD,      KC_COLN, KC_DQUO, KC_GT,   KC_LCBR, KC_RCBR, \
  KC_CAPS, KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,       KC_SCLN, KC_QUOT, KC_LT,   KC_LBRC, KC_RBRC, \
                    _______, _______, _______,      _______,  _______, _______\
),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab |      |      |      |      |           | Left | Down |  Up  | Right| Enter|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Ctrl|   `  |  GUI |  Alt | Del  |           | BkSp | PgUp | PgDn |   \  |   '  |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               |      | LOWER|      |           |      | RAISE|      |
 *               `--------------------'           `--------------------'
 */
[_LOWER] = LAYOUT( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  KC_TAB,  _______, _______, _______, _______,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT, \
  KC_LCTL, KC_GRV,  KC_LGUI, KC_LALT, KC_DEL,      KC_BSPC, KC_PGUP, KC_PGDN, KC_BSLS, KC_QUOT, \
                    _______, _______, _______,      _______, _______, _______                    \
),


/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |   F6 |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |  F12 |      |      |      |           |      |      |      |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Reset|      |      |      |      |           | Prev | Next | Vol- | Vol+ | Play |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               |      | LOWER|      |           |      | RAISE|      |
 *               `--------------------'           `--------------------'
 */
[_ADJUST] =  LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, \
  KC_F11,  KC_F12,  _______, _______, _______,      _______, _______, _______, _______, _______, \
  RESET,   _______, _______, _______, _______,      KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, \
                    _______, _______, _______,      _______,  _______, _______                   \
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        // persistant_default_layer_set(1UL<<_QWERTY);
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }

  // 薙刀式
  bool a = true;
  if (naginata_state()) {
    naginata_mode(keycode, record);
    a = process_naginata(keycode, record);
  }
  #ifdef NAGINATA_EDIT_MODE
    bool b = process_naginata_edit(keycode, record);
    return a & b;
  #else
    return a;
  #endif
  return true;
  // 薙刀式
}

void matrix_init_user(void) {
  // 薙刀式
  set_naginata(_NAGINATA);
  #ifdef NAGINATA_EDIT_MODE
  set_naginata_edit(_NGEDITL, _NGEDITR);
  #endif
  // 薙刀式
}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {
}
