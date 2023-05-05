#include QMK_KEYBOARD_H

enum layers {
  _BASE,
  LAYER_LENGTH
};

enum combos {
  COMBO_SPACE,
  COMBO_BACKSP,
  COMBO_ENTER,
  COMBO_TAB,
  COMBO_ESC,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM combo_space[]      = { KC_N, KC_M, COMBO_END };
const uint16_t PROGMEM combo_backspace[]  = { KC_O, KC_P, COMBO_END };
const uint16_t PROGMEM combo_enter[]      = { KC_L, KC_QUOT, COMBO_END };
const uint16_t PROGMEM combo_tab[]        = { KC_A, KC_S, COMBO_END };
const uint16_t PROGMEM combo_esc[]        = { KC_Q, KC_W, COMBO_END };

combo_t key_combos[] = {
  [COMBO_SPACE]   = COMBO(combo_space, KC_SPC),
  [COMBO_BACKSP]  = COMBO(combo_backspace, KC_BSPC),
  [COMBO_ENTER]   = COMBO(combo_enter, KC_ENT),
  [COMBO_TAB]     = COMBO(combo_tab, KC_TAB),
  [COMBO_ESC]     = COMBO(combo_esc, KC_ESC)
};

enum tapdances {
  TD_QESC,
  TAPDANCE_LENGTH
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_QESC]   = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
};

const key_override_t **key_overrides = (const key_override_t *[]) {
    NULL
};

#define QESC  TD(TD_QESC)
#define BSFT  LSFT_T(KC_B)
#define VCTL  LCTL_T(KC_V)
#define CGUI  LGUI_T(KC_C)
#define XALT  LALT_T(KC_X)

#define ______ KC_NO
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,               KC_Y,   KC_U,   KC_I,       KC_O,   KC_P,    \
        KC_A,   KC_S,   KC_D,   KC_F,   KC_G,               KC_H,   KC_J,   KC_K,       KC_L,   KC_QUOT,    \
        KC_Z,   XALT,   CGUI,   VCTL,   BSFT,   KC_SPC,     KC_N,   KC_M,   KC_COMM,    KC_DOT, KC_SLSH
    ),
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] = { ENCODER_CCW_CW(KC_DOWN, KC_UP) },
};