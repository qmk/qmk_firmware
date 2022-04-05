#include QMK_KEYBOARD_H
//#include "g/keymap_combo.h"

// NICOLA親指シフト
#include "nicola.h"

NGKEYS nicola_keys;
// NICOLA親指シフト

enum keymap_layers {
  _QWERTY = 0,
// NICOLA親指シフト
  _NICOLA, // NICOLA親指シフト入力レイヤー
// NICOLA親指シフト
  _FUNC,
// for left control
  _LCTL,
  _MOUSE
};

enum custom_keycodes {
// NICOLA親指シフト
  KC_QWERTY = NG_SAFE_RANGE, // SAFE_RANGE を NG_SAFE_RANGE に変更してください
// NICOLA親指シフト
  KC_EISU,
  KC_KANA2
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define _____ KC_TRNS
#define XXXXX KC_NO

#define KC_MOUSE TG(_MOUSE)
#define KC_NICOLA TG(_NICOLA)

#define LC_A LCTL(KC_A)
#define LC_B LCTL(KC_B)
#define LC_C LCTL(KC_C)
#define LC_D LCTL(KC_D)
#define LC_E LCTL(KC_E)
#define LC_F LCTL(KC_F)
#define LC_G LCTL(KC_G)
#define LC_H LCTL(KC_H)
#define LC_I LCTL(KC_I)
#define LC_J LCTL(KC_J)
#define LC_K LCTL(KC_K)
#define LC_L LCTL(KC_L)
#define LC_M LCTL(KC_M)
#define LC_N LCTL(KC_N)
#define LC_O LCTL(KC_O)
#define LC_P LCTL(KC_P)
#define LC_Q LCTL(KC_Q)
#define LC_R LCTL(KC_R)
#define LC_S LCTL(KC_S)
#define LC_T LCTL(KC_T)
#define LC_U LCTL(KC_U)
#define LC_V LCTL(KC_V)
#define LC_W LCTL(KC_W)
#define LC_X LCTL(KC_X)
#define LC_Y LCTL(KC_Y)
#define LC_Z LCTL(KC_Z)
#define LCOP LCTL(KC_LALT)
#define LCFN LCTL(KC_LGUI)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_JP(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_JYEN, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
        LT(_LCTL,KC_KANA2), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RO, KC_UP, KC_RSFT,
        MO(_FUNC), KC_GRV, KC_LALT, KC_LGUI, KC_EISU, KC_SPC, KC_KANA2, KC_MOUSE, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    // NICOLA親指シフト デフォルトレイヤーに関係なくQWERTYで
    [_NICOLA] = LAYOUT_JP(
          KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_JYEN, KC_BSPC,
          KC_TAB, NG_Q, NG_W, NG_E, NG_R, NG_T, NG_Y, NG_U, NG_I, NG_O, NG_P,KC_LBRC,KC_RBRC,
          LT(_LCTL,KC_EISU), NG_A, NG_S, NG_D, NG_F, NG_G, NG_H, NG_J, NG_K, NG_L,NG_SCLN,KC_QUOT,KC_BSLS,KC_ENT,
          KC_LSFT, NG_Z, NG_X, NG_C, NG_V, NG_B, NG_N, NG_M,NG_COMM,NG_DOT,NG_SLSH,KC_RO,KC_UP,KC_RSFT,
          MO(_FUNC),KC_GRV,KC_LALT,KC_LGUI,NG_SHFTL,NG_SHFTR,KC_EISU,KC_RGUI,KC_RALT,MO(1),KC_LEFT,KC_DOWN,KC_RGHT
    ),
    // NICOLA親指シフト

    [_FUNC] = LAYOUT_JP(
        KC_POWER, KC_BRMD, KC_BRMU, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP, _______,
        KC_LCTL, KC_VOLD, KC_VOLU, KC_MUTE, KC_PWR, _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, _______, KC_PENT,
        _______, _______, _______, _______, _______, _______, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, _______, _______, _______,
        MO(_FUNC), _______, _______, _______, KC_EISU,KC_SPC, _______, _______, _______, _______, KC_DEL, _______, _______
    ),
    [_LCTL] = LAYOUT_JP(
        _______,_______,_______,_______,_______,_______,_______  ,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,   LC_Q,   LC_W,   LC_E,   LC_R,   LC_T,    LC_Y ,   LC_U,   LC_I,   LC_O,   LC_P,_______,_______,
        _______,   LC_A,   LC_S,   LC_D,   LC_F,   LC_G,KC_BSPACE,   LC_J,   LC_K,  LC_L,_______,_______,_______,_______,
        _______,   LC_Z,   LC_X,   LC_C,   LC_V,   LC_B,   LC_N  ,KC_ENT ,_______,_______,_______,_______,_______,_______,
        _______,_______,   LCOP,   LCFN,_______,_______,KC_KANA2,_______ ,_______,_______,_______,_______,_______
    ),
//  // mouse IJKL
//     [_MOUSE] = LAYOUT_JP(
//         _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
//         _______,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,KC_WH_L,KC_WH_D,KC_MS_U,KC_WH_U,KC_WH_R,  XXXXX,  XXXXX,
//         _______,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,KC_MS_L,KC_MS_D,KC_MS_R,KC_BTN1,  XXXXX,  XXXXX,  XXXXX,
//         _______,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,KC_BTN2,KC_BTN1,   XXXXX,  XXXXX,  XXXXX, XXXXX,  _______,  XXXXX,
//         MO(_FUNC),XXXXX,  XXXXX,  XXXXX,  XXXXX,KC_BTN1,KC_EISU,KC_MOUSE, XXXXX,  XXXXX, _______,KC_DOWN, _______
//   ),

// // MOSE HJKL
    [_MOUSE] = LAYOUT_JP(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,KC_WH_L,KC_WH_D,KC_WH_U,KC_WH_R,  XXXXX,  XXXXX,  XXXXX,
        _______,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,KC_BTN1,  XXXXX,  XXXXX,  XXXXX,
        _______,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  XXXXX,KC_BTN2,KC_BTN1,   XXXXX,  XXXXX,  XXXXX, XXXXX,  _______,  XXXXX,
        MO(_FUNC),XXXXX,  XXXXX,  XXXXX,  XXXXX,KC_BTN1,KC_EISU,KC_MOUSE, XXXXX,  XXXXX, _______,KC_DOWN, _______
  ),





};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
  // NICOLA親指シフト
  set_nicola(_NICOLA);
  // NICOLA親指シフト
}

// result of process_record_user
#define PROCESS_OVERRIDE_BEHAVIOR  (false)
#define PROCESS_USUAL_BEHAVIOR   (true)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef OLED_ENABLE
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  #endif

//  static uint16_t mem_keycode;
//  uint16_t prev_keycode = mem_keycode;
//  bool is_tapped = ((!record->event.pressed) && (keycode == prev_keycode));
//  mem_keycode = keycode;

  switch (keycode) {
    case LT(_LCTL,KC_KANA2):
      if (record->tap.count && record->event.pressed){
        //   tap_code(KC_KANA2);
          nicola_on();
          return false;
      }
      break;
    case LT(_LCTL,KC_EISU):
      if (record->tap.count && record->event.pressed){
        //   tap_code(KC_EISU);
          nicola_off();
          return false;
      }
      break;
    case KC_QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case KC_EISU:
      if (record->event.pressed) {
        // layer_off(_MOUSE);
        // NICOLA親指シフト
        nicola_off();
        // NICOLA親指シフト
      }
      return false;
      break;
    case KC_KANA2:
      if (record->event.pressed) {

        //     unregister_code(KC_LCTL);
        //     layer_off(_MOUSE);
        //     nicola_on();
        // }else{
            // layer_off(_MOUSE);
            // NICOLA親指シフト
            nicola_on();
            // NICOLA親指シフト
        // }
      }
      return false;
      break;
//    case NG_SHFTR:
//      if(record->event.pressed){
//      }else{
//         if(is_tapped){
//             tap_code(KC_SPC);//space key
//         }
//      }
//      return PROCESS_OVERRIDE_BEHAVIOR;
//      break;
    default:{
      break;
    }
  }
  // NICOLA親指シフト
  bool a = true;
  if (nicola_state()) {
    nicola_mode(keycode, record);
    a = process_nicola(keycode, record);
  }
  if (a == false) return false;
  // NICOLA親指シフト

  return PROCESS_USUAL_BEHAVIOR;
}
