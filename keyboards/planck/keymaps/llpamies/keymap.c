#include QMK_KEYBOARD_H

enum planck_layers {
  _COLEMAK,
  _SYMBOL,
  _NAVIGATION,
  _ADJUST
};

enum custom_keycodes {
  MACRO_0 = SAFE_RANGE,
  MACRO_1,
  MACRO_2,
};

#define CTRL_ESC LGUI_T(KC_ESCAPE)
#define SYMB_BSPC LT(_SYMBOL, KC_BSPACE)
#define NAV_SPC LT(_NAVIGATION, KC_SPACE)
#define ADJUST MO(_ADJUST)
#define UNIQ(X) RALT(RCTL(RGUI(RSFT(X))))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = LAYOUT_planck_grid(
  KC_TAB,    KC_Q,        KC_W,    KC_F,          KC_P,      KC_B,      KC_J,     KC_L,    KC_U,           KC_Y,    KC_SCOLON, KC_BSLASH,
  CTRL_ESC,  KC_A,        KC_R,    KC_S,          KC_T,      KC_G,      KC_M,     KC_N,    KC_E,           KC_I,    KC_O,      RGUI_T(KC_ENTER),
  KC_LSHIFT, KC_Z,        KC_X,    KC_C,          KC_D,      KC_V,      KC_K,     KC_H,    KC_COMMA,       KC_DOT,  KC_SLASH,  RSFT_T(KC_QUOTE),
  KC_LCTRL,  KC_CAPSLOCK, KC_LALT, UNIQ(KC_LEFT), SYMB_BSPC, KC_BSPACE, KC_SPACE, NAV_SPC, UNIQ(KC_RIGHT), KC_COLN, _______,   _______
),

[_SYMBOL] = LAYOUT_planck_grid(
  KC_TILD,  KC_EXLM, KC_AT,   KC_HASH,     KC_DLR,      KC_PERC, KC_CIRC,   KC_AMPR, KC_ASTR,  KC_LPRN, KC_RPRN,  KC_PIPE,
  KC_GRAVE, KC_1,    KC_2,    KC_3,        KC_4,        KC_5,    KC_6,      KC_7,    KC_8,     KC_9,    KC_0,     KC_BSLASH,
  _______,  KC_LCBR, KC_RCBR, KC_LBRACKET, KC_RBRACKET, KC_COLN, KC_SCOLON, KC_UNDS, KC_MINUS, KC_PLUS, KC_EQUAL, _______,
  _______,  _______, _______, _______,     _______,     _______, _______,   _______, _______,  _______, _______,  _______
),

[_NAVIGATION] = LAYOUT_planck_grid(
  _______, MACRO_0, MACRO_1, _______, _______, _______, LCTL(KC_H), LCTL(KC_J), LCTL(KC_K), LCTL(KC_L), _______, _______,
  _______, _______, _______, _______, _______, _______, KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   _______, _______,
  _______, _______, MACRO_2, _______, _______, _______, KC_HOME,    KC_PGDOWN,  KC_PGUP,    KC_END,     _______, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______,    _______,    _______,    _______, _______
),

[_ADJUST] = LAYOUT_planck_grid(
  _______, _______, DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, RESET,
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______,  _______, _______, _______,
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _SYMBOL, _NAVIGATION, _ADJUST);
}

// Programming symbols.
const uint16_t PROGMEM combo_paren_open[] = {KC_T, KC_R, COMBO_END};
const uint16_t PROGMEM combo_paren_close[] = {KC_N, KC_I, COMBO_END};
const uint16_t PROGMEM combo_brack_open[] = {KC_S, KC_R, COMBO_END};
const uint16_t PROGMEM combo_brack_close[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM combo_brace_open[] = {KC_T, KC_A, COMBO_END};
const uint16_t PROGMEM combo_brace_close[] = {KC_N, KC_O, COMBO_END};

// Hard to reach letters.
const uint16_t PROGMEM combo_letter_g[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM combo_letter_m[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM combo_letter_b[] = {KC_P, KC_F, COMBO_END};
const uint16_t PROGMEM combo_letter_j[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM combo_letter_v[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM combo_letter_k[] = {KC_H, KC_COMMA, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  // Programming symbols.
  COMBO(combo_paren_open, KC_RPRN),
  COMBO(combo_paren_close, KC_LPRN),
  COMBO(combo_brack_open, KC_RBRACKET),
  COMBO(combo_brack_close, KC_LBRACKET),
  COMBO(combo_brace_open, KC_RCBR),
  COMBO(combo_brace_close, KC_LCBR),
  // Hard to reach letters.
  COMBO(combo_letter_g, KC_G),
  COMBO(combo_letter_m, KC_M),
  COMBO(combo_letter_b, KC_B),
  COMBO(combo_letter_j, KC_J),
  COMBO(combo_letter_v, KC_V),
  COMBO(combo_letter_k, KC_K)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MACRO_0:
      if (record->event.pressed) {
        SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_TAP(X_Q) SS_DELAY(100) SS_TAP(X_ENTER));
      }
      break;
    case MACRO_1:
      if (record->event.pressed) {
        SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_TAP(X_W) SS_DELAY(100) SS_TAP(X_ENTER));
      }
      break;
    case MACRO_2:
      if (record->event.pressed) {
        SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_TAP(X_X) SS_DELAY(100) SS_TAP(X_ENTER));
      }
      break;
  }
  return true;
}
