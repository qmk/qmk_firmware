#include QMK_KEYBOARD_H
#include "twpair_on_jis.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum my_layers {
  _BASE,
  _NAGINATA,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------.             ,-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * `-------------+------+------+------+------+------+------+------+------+------+------+-------------'
 *               |  GUI |  Alt |Lower |Space | Ctrl |Enter |Space |Raise |  Alt |  GUI |
 *               `---------------------------------------------------------------------'
 */
[_BASE] = LAYOUT( \
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  KC_TAB,  KC_Y,    KC_R,    KC_O,    KC_U,    KC_COMM,                KC_DOT,  KC_BSPC, KC_L,    KC_F,    KC_P,    KC_QUOT, \
  KC_LSFT, KC_D,    KC_S,    KC_A,    KC_I,    KC_G,                   KC_J,    KC_E,    KC_H,    KC_T,    KC_K,    KC_SCLN, \
  KC_LCTL, KC_V,    KC_Z,    KC_X,    KC_M,    KC_C, KC_LBRC, KC_RBRC, KC_N,    KC_W,    KC_B,    KC_Q,    KC_SLSH, KC_RSFT , \
  KC_LGUI, KC_LALT,    LOWER,LSFT_T(KC_SPC), LSFT_T(KC_SPC),LSFT_T(KC_ENT),LSFT_T(KC_ENT), RAISE,   KC_MENU, KC_LWIN\
),

[_LOWER] = LAYOUT( \
  KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12, \
  KC_NO,   XXXXXXX, XXXXXXX, KC_COLN, KC_SCLN, XXXXXXX,                   KC_SLSH ,KC_7    ,KC_8    ,KC_9    ,KC_MINS, KC_NO,  \
  KC_NO,   XXXXXXX ,KC_LBRC, KC_LCBR, KC_LPRN, KC_LT  ,                   KC_ASTR ,KC_4    ,KC_5    ,KC_6    ,KC_PLUS, KC_NO,  \
  KC_NO,   XXXXXXX ,KC_RBRC, KC_RCBR, KC_RPRN, KC_GT  , _______, _______, KC_0    ,KC_1    ,KC_2    ,KC_3    ,KC_EQL , _______,\
                    _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______\
),

[_RAISE] = LAYOUT( \
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  \
  _______, KC_TILD ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,                   XXXXXXX ,KC_HOME ,KC_UP   ,KC_END  ,XXXXXXX ,KC_BSPC, \
  _______, KC_CIRC ,KC_AMPR ,KC_EXLM ,KC_QUES ,KC_JYEN ,                   XXXXXXX ,KC_LEFT ,KC_DOWN ,KC_RGHT ,XXXXXXX ,KC_BSLS, \
  _______, KC_PIPE ,KC_GRV  ,KC_QUOT ,KC_DQT  ,KC_UNDS ,_______, _______,  XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______, \
                     _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______\
),

[_ADJUST] =  LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,                   RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, KC_BSPC, \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM,                   AG_SWAP, _______, BL_TOGG, BL_STEP, _______, _______, \
  _______,  _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______\
),

[_NAGINATA] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, NG_Q,    NG_W,    NG_E,    NG_R,    NG_T,                      NG_Y,    NG_U,    NG_I,    NG_O,    NG_P,    _______, \
  _______, NG_A,    NG_S,    NG_D,    NG_F,    NG_G,                      NG_H,    NG_J,    NG_K,    NG_L,    NG_SCLN, _______, \
  _______, NG_Z,    NG_X,    NG_C,    NG_V,    NG_B,    _______, _______, NG_N,    NG_M,    NG_COMM, NG_DOT,  NG_SLSH, _______ , \
                 _______, _______,    _______, NG_SHFT, NG_SHFT, NG_SHFT2, NG_SHFT2,_______, _______, _______\
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void matrix_init_user(void) {
  // 薙刀式
  uint16_t ngonkeys[] = {KC_J, KC_E};
  uint16_t ngoffkeys[] = {KC_I, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  // set_naginata(_NAGINATA);
  // set_unicode_input_mode(UC_WINC);
  // set_unicode_input_mode(UC_LNX);
  // 薙刀式
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // 薙刀式
  if (!process_naginata(keycode, record))
    return false;
  // 薙刀式

  // typewriter pairing on jis keyboard
  if (!twpair_on_jis(keycode, record))
    return false;

  return true;
}
