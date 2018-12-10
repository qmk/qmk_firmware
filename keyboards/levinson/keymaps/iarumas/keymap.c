#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#include "neo2-keys-on-quertz-de-latin1.h"
#include "neo2-basic-layout.h"
#include "keymap_steno.h"

#define TAPPING_TOGGLE 3
#define SPC_CTRL LT(_N2_CTRL,KC_SPC)

enum my_keycodes{
  _N2_LETS = 0,
  _QUERTZ,
  _PLOVER,
  /* L02 */
  _N2_SYMB,
  _N2_CTRL,
  /*  L05 -> N2_GREEK */
  /*  L06 -> N2_MATH */
  _N2_FUN,
  _LIGHT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \
[_N2_LETS] = LAYOUT_ortho_4x12( 
  TT(_LIGHT),   KC_X,    KC_V,    KC_L,   KC_C,         KC_W,   KC_K,    KC_H,        KC_G,     KC_F,    KC_Q,    N_SS,
  MO(_N2_SYMB), KC_U,    KC_I,    KC_A,   KC_E,         KC_O,   KC_S,    KC_N,        KC_R,     KC_T,    KC_D,    LT(_N2_SYMB,N_Y),
  KC_LSHIFT,    N_UE,    N_OE,    N_AE,   KC_P,         N_Z,    KC_B,    KC_M,        KC_COMM,  KC_DOT,  KC_J,    KC_RSHIFT,
  KC_LCTRL,     KC_LGUI, KC_LALT, XXXXXXX,MO(_N2_FUN), SPC_CTRL,SPC_CTRL, MO(_N2_FUN),XXXXXXX,  KC_RALT, KC_LGUI, KC_RCTRL
),

[_N2_SYMB] = LAYOUT_ortho_4x12( 
   _______,  N_DOTS,  N_USC,   N_LSQBR, N_RSQBR, N_CIRC,  N_EXKL,  N_LT,    N_GT,    N_EQ,    N_AMP,  _______,
   _______,  N_BSLS,  N_SLSH,  N_LCUBR, N_MINS, N_COLN,   N_QUES,  N_LPARN, N_RPARN, N_MINS,  N_COLN, N_AT,
   _______,  N_HASH,  N_DLR,   N_PIPE,  N_TILD,  N_GRAVE, N_PLUS,  N_PERC,  N_QUOT,  N_SING,  N_SEMI, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_N2_CTRL] = LAYOUT_ortho_4x12( 
   _______, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,   KC_PGDN, KC_KP_SLASH,    KC_7,   KC_8,     KC_9,     N_MINS,     _______,
   _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,  KC_KP_ASTERISK, KC_4,   KC_5,     KC_6,     N_PLUS,     _______,
   _______, KC_ESC,  KC_TAB,  KC_INS,  KC_ENTER, N_UNDO,  KC_KP_ENTER,    KC_1,   KC_2,     KC_3,     KC_DOT,     _______,
   _______, _______, _______, _______, _______, _______,  _______,        KC_0, _______, _______,  _______,         _______

),

[_N2_FUN] = LAYOUT_ortho_4x12( 
   _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   DF(_QUERTZ),   KC_MAIL, KC_MSEL, KC_MY_COMPUTER, KC_CALCULATOR, N_PASTE, _______,
   _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   DF(_N2_LETS),  KC_MPRV, KC_MPLY, KC_MNXT,        KC_MSTP,       N_COPY,  _______,
   _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  DF(_PLOVER),   KC_PSCR, KC_SLCK, KC_PAUS,        KC_NLCK,       N_CUT,   _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______,         _______,      _______, _______
),

[_QUERTZ] = LAYOUT_ortho_4x12(
   _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Z,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
   _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    N_OE,    _______,
   _______, KC_Y,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  N_MINS,  _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  FN  |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |  PWR | RES1 | RES2 |
 * `-----------------------------------------------------------------------------------'
 */

[_PLOVER] = LAYOUT_ortho_4x12(
  STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC,
  STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
  XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
  DF(_N2_LETS), XXXXXXX, XXXXXXX, STN_A,   STN_O,   XXXXXXX, XXXXXXX, STN_E,   STN_U,   STN_PWR, STN_RE1, STN_RE2
),

/*
 *[_PLOVER] = LAYOUT_ortho_4x12(
 *    _______,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
 *    _______, STN_S1,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
 *    _______, STN_S2,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
 *    DF(_N2_LETS), _______, _______, KC_C,    KC_V,    _______, _______, KC_N,    KC_M,    _______, _______, _______
 *),
 */

[_LIGHT] = LAYOUT_ortho_4x12(
   _______, RGB_TOG,          RGB_HUI,    RGB_SAI,    RGB_VAI,    KC_T,    KC_Z,    KC_U,    KC_I,    KC_O,    BL_TOGG,    _______,
   _______, RGB_MODE_FORWARD, RGB_HUD,    RGB_SAD,    RGB_VAD,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    BL_STEP,    _______,
   _______, KC_Y,             KC_X,       KC_C,       KC_V,       KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  BL_BRTG,    _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
};

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case _N2_LETS:
      autoshift_enable();
      rgblight_setrgb(0x00, 0x00, 0xFF);
      break;
    case _QUERTZ: 
      autoshift_disable();
      rgblight_setrgb(0x00, 0xA0, 0xFF);
      break;
    case _PLOVER: 
      autoshift_disable();
      rgblight_setrgb(0x00, 0x00, 0xFF);
      break;
  }
  return state;
}
