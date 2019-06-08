/* Copyright 2019 eswai
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
//#include"keymap_jp.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = NG_SAFE_RANGE,
  EUCALYN,
  MOVE,
  SYMBOL,
  NUMBER,
  CONTROL,
  RGBRST,
  EISU,
  KANA,
  EUCALYNM,
  EURO,
  SSCLN,
  SEQL,
};

// Layers
enum kepmap_layers {
  _EUCALYN,
  _EUCALYNM,
  _SHIFT,
// 薙刀式
  _NAGINATA,
  _NGEDITL,
  _NGEDITR,
// 薙刀式
  _NUMBER,
  _SYMBOL,
  _MOVE,
  _CONTROL,
};

#define _____   KC_TRNS
#define XXXXX   KC_NO
#define KFUNC   TD(FUNC)
#define SFTSPC  SFT_T(KC_SPC)
#define ALTENT  ALT_T(KC_ENT)
#define ALTSPC  ALT_T(KC_SPC)
#define ALTBS   ALT_T(KC_BSPC)
#define CMDSPC  CMD_T(KC_SPC)
#define CTLENT  CTL_T(KC_ENT)
#define CTLSPC  CTL_T(KC_SPC)
#define CMDENT  CMD_T(KC_ENT)
#define CTLBS   CTL_T(KC_BSPC)
#define LSHFT LM(_SHIFT,MOD_LSFT)
// 薙刀式
// 編集モードを追加する場合
#define KC(A) C(KC_##A)
#define KS(A) S(KC_##A)
#define KG(A) G(KC_##A)
#define KA(B) A(KC_##B)
// 薙刀式

// 薙刀式
enum combo_events {
  NAGINATA_ON_CMB,
  NAGINATA_OFF_CMB,
  LOGIN_CMB,
};

#if defined(EUCALYN) || defined(EUCALYNKAI)
const uint16_t PROGMEM ngon_combo[] = {KC_G, KC_T, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_I, KC_U, COMBO_END};
#else
const uint16_t PROGMEM ngon_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_F, KC_G, COMBO_END};
#endif
const uint16_t PROGMEM login_combo[] = {KC_Q, KC_W, KC_M, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [NAGINATA_ON_CMB] = COMBO_ACTION(ngon_combo),
  [NAGINATA_OFF_CMB] = COMBO_ACTION(ngoff_combo),
  [LOGIN_CMB] = COMBO_ACTION(login_combo),
};
// 薙刀式

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_EUCALYN] = LAYOUT( /* Base */
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
     KC_ESC,   KC_Q,   KC_W,   KC_M,   KC_R,KC_LEFT,  KG(S), KC_DEL,KC_RGHT,KC_BSPC,   KC_D,   KC_Y,   KC_P,KC_MINS, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
     KC_TAB,   KC_A,   KC_O,   KC_E,   KC_I,   KC_U,KC_LPRN,KC_RPRN,   KC_G,   KC_T,   KC_K,   KC_S,   KC_N,KC_PLUS, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_F,KC_COMM, KC_DOT,   KC_B,   KC_H,   KC_J,   KC_L,KC_SLSH,KC_COLN, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    KC_LCMD, NUMBER,KC_LALT,  KC_F2,   MOVE,  LSHFT, CTLSPC, CMDENT,  LSHFT, SYMBOL,   KC_0, KC_DOT,KC_QUOT,KC_RCMD  \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_SHIFT] = LAYOUT( /* Base */
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,KC_LCBR,KC_RCBR,  _____,  _____,  _____,  _____,  _____,   SEQL, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  SSCLN, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____  \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_NAGINATA] = LAYOUT(
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,   NG_Q,   NG_W,   NG_E,   NG_R,KC_LEFT,  _____,  _____,KC_RGHT,   NG_U,   NG_I,   NG_O,   NG_P,  _____, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,   NG_A,   NG_S,   NG_D,   NG_F,   NG_G,  _____,  _____,   NG_H,   NG_J,   NG_K,   NG_L,NG_SCLN,  _____, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,   NG_Z,   NG_X,   NG_C,   NG_V,   NG_B,  _____,  _____,   NG_N,   NG_M,NG_COMM, NG_DOT,NG_SLSH,  _____, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____, NGSHFT,  _____,  _____, NGSHFT,  _____,  _____,  _____,  _____,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_NGEDITL] = LAYOUT(
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,KG(DOWN),KG(UP),  XXXXX,  XXXXX,  CHR10,  _____,  _____,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  _____, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  KC(Y),  KC(S),KC_PGDN,KC_PGUP,  CHR20,  _____,  _____,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  _____, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  KC(Z),  KC(X),  KC(C),  KC(V),  CHR30,  _____,  _____,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  _____, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____, NGSHFT,  _____,  _____, NGSHFT,  _____,  _____,  _____,  _____,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_NGEDITR] = LAYOUT(
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  _____,  _____,KC_HOME,KG(DEL),  XXXXX, KC_DEL, KC_ESC,  _____, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  _____,  _____,  XXXXX,  KC_UP, KS(UP),    UP5,  KC_F7,  _____, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  _____,  _____, KC_END,KC_DOWN,KS(DOWN), DOWN5,  KC_F6,  _____, \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____, NGSHFT,  _____,  _____, NGSHFT,  _____,  _____,  _____,  _____,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_MOVE] = LAYOUT( \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  XXXXX,  XXXXX, KS(UP),  XXXXX,  XXXXX,  _____,  _____,  XXXXX,  KC(A),  KC_UP,  KC(E),   UP10,KC_PGUP,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,XXXXX,KS(LEFT),KS(DOWN),KS(RGHT), XXXXX,KC_LCBR,KC_RCBR,  XXXXX,KC_LEFT,KC_DOWN,KC_RGHT, DOWN10,KC_PGDN,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  _____,  _____,  XXXXX,KA(LEFT), XXXXX,KA(RGHT), XXXXX,  XXXXX,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  KANA,  _____,  _____,  _____,  _____,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_SYMBOL] = LAYOUT( \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//               !       @       #       $       %
      _____,KC_EXLM,  KC_AT,KC_HASH, KC_DLR,KC_PERC,  _____,  _____,  XXXXX,  XXXXX,KC_LCBR,KC_RCBR,  XXXXX,  _____,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//               ^       &       '       "       ~
      _____,KC_CIRC,KC_AMPR,KC_QUOT, KC_DQT,KC_TILD,KC_LBRC,KC_RBRC,  KC_LT,  KC_GT,KC_LPRN,KC_RPRN,  XXXXX,  _____,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//                       |       `       _       ¥
      _____,   EURO,KC_PIPE, KC_GRV,KC_UNDS,KC_PIPE,  _____,  _____,  XXXXX,  XXXXX,KC_LBRC,KC_RBRC,  XXXXX,  _____,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,   EISU,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_NUMBER] = LAYOUT( \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
//                                        $       %
      _____,  _____,  _____,  KC_UP, KC_DLR,KC_PERC,  _____,KC_BSPC,  _____,KC_SLSH,   KC_7,   KC_8,   KC_9,KC_MINS,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,KC_LEFT,KC_DOWN,KC_RGHT,KC_TILD,  _____,  _____,  _____,KC_ASTR,   KC_4,   KC_5,   KC_6,KC_PLUS,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,KC_PERC, KC_EQL,   KC_1,   KC_2,   KC_3, KC_ENT,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____, NUMBER,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,   KC_0, KC_DOT,KC_COMM,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

  [_CONTROL] = LAYOUT( \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    RGB_HUI,RGB_HUD,KC_WAKE,  XXXXX,  RESET,  XXXXX,KC_BRIU,RGB_TOG,KC_MYCM,  XXXXX,KC_WSCH,  XXXXX, KC_PWR,EUCALYN,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    RGB_SAI,RGB_SAD,  XXXXX,  XXXXX,EEP_RST,  XXXXX,KC_BRID,RGB_MOD,KC_MAIL,KC_WBAK,KC_WHOM,KC_WFWD,  XXXXX,EUCALYNM,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
    RGB_VAI,RGB_VAD,KC_SLEP,KC_CALC,  XXXXX,  XXXXX,RGBRST,RGB_RMOD,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,\
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
      _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____,  _____ \
// +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  ),

};

void update_led(void);

void update_led() {
  rgblight_set_effect_range(56, 15);

  if (!layer_state_is(_NUMBER) && !layer_state_is(_SYMBOL) && !layer_state_is(_MOVE) && !layer_state_is(_NUMBER)) {
    rgblight_sethsv_range(0, 0, 0, 0, 56);
  }
  if (naginata_state()) {
    rgblight_sethsv_at(150, 200, 255, 0);
    rgblight_sethsv_at(150, 200, 200, 17);
    rgblight_sethsv_at(150, 200, 200, 38);
    rgblight_sethsv_at(150, 200, 200, 20);
    rgblight_sethsv_at(150, 200, 200, 35);
    // rgblight_setrgb_range(10, 10, 10, 56, 71);
  } else {
    rgblight_sethsv_at(50, 200, 0, 0);
    rgblight_sethsv_at(150, 200, 0, 17);
    rgblight_sethsv_at(150, 200, 0, 38);
  }
  if (layer_state_is(_NUMBER)) {
    rgblight_sethsv_at(240, 200, 255, 0);
    rgblight_sethsv_at(150, 200, 200, 4);
    rgblight_sethsv_range(150, 200, 200, 40, 43);
    rgblight_sethsv_range(150, 200, 200, 45, 51);
    rgblight_sethsv_at(150, 200, 200, 9);
    rgblight_sethsv_at(150, 200, 200, 14);
    rgblight_sethsv_at(150, 200, 200, 15);
    rgblight_sethsv_at(150, 200, 200, 17);
  }
  if (layer_state_is(_SYMBOL)) {
    // rgblight_sethsv_at(240, 100, 200, 19);
    rgblight_sethsv_range(240, 200, 200, 40, 43);
    rgblight_sethsv_range(240, 200, 200, 45, 51);
  }
  if (layer_state_is(_MOVE)) {
    // rgblight_sethsv_at(100, 100, 200, 36);
    rgblight_sethsv_at(100, 200, 200, 38);
    rgblight_sethsv_at(100, 200, 200, 40);
    rgblight_sethsv_at(100, 200, 200, 41);
    rgblight_sethsv_at(100, 200, 200, 46);
  }
}


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case NUMBER:
      if (record->event.pressed) {
        layer_invert(_NUMBER);
      }
      update_led();
      return false;
      break;
    case RGBRST:
      if (record->event.pressed) {
        eeconfig_update_rgblight_default();
        rgblight_enable();
      }
      update_led();
      return false;
      break;
    case CONTROL:
      if (record->event.pressed) {
        layer_on(_CONTROL);
      } else {
        layer_off(_CONTROL);
      }
      update_led();
      return false;
      break;
    case SYMBOL:
      if (record->event.pressed) {
        layer_on(_SYMBOL);
        update_tri_layer(_SYMBOL, _MOVE, _CONTROL);
      } else {
        layer_off(_SYMBOL);
        update_tri_layer(_SYMBOL, _MOVE, _CONTROL);
      }
      update_led();
      return false;
      break;
    case MOVE:
      if (record->event.pressed) {
        layer_on(_MOVE);
        update_tri_layer(_SYMBOL, _MOVE, _CONTROL);
      } else {
        layer_off(_MOVE);
        update_tri_layer(_SYMBOL, _MOVE, _CONTROL);
      }
      update_led();
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        naginata_on();
      }
      update_led();
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        naginata_off();
      }
      update_led();
      return false;
      break;
    case EUCALYN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_EUCALYN);
      }
      return false;
      break;
    case EUCALYNM:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_EUCALYNM);
      }
      return false;
      break;
    case EURO:
      if (record->event.pressed) {
        send_string("(e)");
        return false;
      }
      break;
    case SSCLN:
      if (record->event.pressed) {
        unregister_code(KC_LSFT);
        tap_code(KC_SCLN);
        return false;
      }
      break;
    case SEQL:
      if (record->event.pressed) {
        unregister_code(KC_LSFT);
        tap_code(KC_EQL);
        return false;
      }
      break;
    }

  // 薙刀式
  bool a = true;
  if (naginata_state()) {
    naginata_mode(keycode, record);
    a = process_naginata(keycode, record);
    update_led();
  }
  #ifdef NAGINATA_EDIT_MODE
    bool b = process_naginata_edit(keycode, record);
    return a & b;
  #else
    return a;
  #endif
  // 薙刀式

  return true;
}

// 薙刀式
// IME ONのcombo
void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case NAGINATA_ON_CMB:
      if (pressed) {
        naginata_on();
        update_led();
      }
      break;
    case NAGINATA_OFF_CMB:
      if (pressed) {
        naginata_off();
        update_led();
      }
      break;
    case LOGIN_CMB:
      if (pressed && !naginata_state()) {
        register_code (KC_LCTRL);
        register_code (KC_LALT);
        register_code (KC_DEL);
        unregister_code (KC_DEL);
        unregister_code (KC_LALT);
        unregister_code (KC_LCTRL);
      }
      break;
  }
}
// 薙刀式

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
