#include QMK_KEYBOARD_H
#include "keymap_italian.h"

//extern keymap_config_t keymap_config;
bool alt_tab_enabled;
uint32_t alt_tab_timer;

//Friendly Layer Names
enum gherkin_layers {
  _QWERTY,
  _ESC,
  _BSPC,
  _SHIFT,
  _NUMBER,
  _SYMBOL,
  _ACCENT
};

// custom keycodes
enum gherkin_keycodes {
  ALT_TAB = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_ortho_3x10(
    LGUI_T(KC_Q), KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,   KC_U,  KC_I,     KC_O,    RGUI_T(KC_P),
    LT(_BSPC, KC_A),   KC_S,  KC_D,  KC_F,  KC_G,  KC_H,   KC_J,  KC_K,     KC_L, LT(_ESC, KC_ENT),
    LT(_SHIFT, KC_Z),LCTL_T(KC_X), LALT_T(KC_C), LGUI_T(KC_V),  LT(_NUMBER, KC_BSPC),  LT(_ACCENT, KC_SPC), LGUI_T(KC_B), RALT_T(KC_N),  RCTL_T(KC_M),  RSFT_T(IT_COMM)
  ),
  [_ESC] = LAYOUT_ortho_3x10(
    KC_ESC,  _______, KC_MUTE, RGB_TOG, BL_TOGG, _______, _______, _______, _______, _______,
    KC_TAB,  ALT_TAB, KC_VOLU, RGB_MOD, BL_STEP, _______, _______, _______, _______, _______,
    _______, _______, KC_VOLD, _______, _______, _______, _______, _______, _______, _______
  ),
  [_BSPC] = LAYOUT_ortho_3x10(
    _______, _______, KC_MUTE, RGB_TOG, BL_TOGG, _______, _______, _______, _______, KC_BSPC,
    KC_TAB,  ALT_TAB, KC_VOLU, RGB_MOD, BL_STEP, _______, _______, _______, KC_UP,   _______,
    RESET,   _______, KC_VOLD, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT
  ),
  [_SHIFT] = LAYOUT_ortho_3x10(
      S(KC_Q),    S(KC_W), S(KC_E), S(KC_R), S(KC_T),    S(KC_Y),   S(KC_U), S(KC_I), S(KC_O), S(KC_P),
      S(KC_A),    S(KC_S), S(KC_D), S(KC_F), S(KC_G),    S(KC_H),   S(KC_J), S(KC_K), S(KC_L), S(KC_ENT),
      S(KC_Z),    S(KC_X), S(KC_C), S(KC_V), S(KC_BSPC), LT(_SYMBOL, S(KC_SPC)), S(KC_B), S(KC_N), S(KC_M), IT_DOT
  ),
  [_NUMBER] = LAYOUT_ortho_3x10(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    LGUI_T(KC_PPLS), KC_PMNS, KC_PSLS, KC_PAST, XXXXXXX, IT_PLUS, IT_MINS, IT_EQL,  IT_LBRC, IT_RBRC,
    LT(_SYMBOL, KC_7), KC_8,  KC_9,     KC_0,  KC_SPC,   _______,  IT_QST,  IT_LESS,  IT_APOS,   IT_SCLN
  ),
  [_SYMBOL] = LAYOUT_ortho_3x10(
    IT_EXLM, IT_AT,   IT_SHRP, IT_UNDS,  IT_PLUS,   IT_PIPE,  S(KC_HOME),  S(KC_UP),    S(KC_END),    _______,
    IT_DLR,  IT_PERC, IT_CRC,  IT_LCBR,  IT_RCBR,  IT_MORE, S(KC_LEFT),  S(KC_DOWN),  S(KC_RIGHT),  _______ ,
    IT_AMPR, IT_ASTR, IT_LPRN, IT_RPRN,  _______,   KC_SPC,  IT_SLSH,  IT_MORE,  IT_DQOT,   IT_COLN
  ),
  [_ACCENT] = LAYOUT_ortho_3x10(
    IT_EURO, XXXXXXX, IT_EACC, XXXXXXX, XXXXXXX, XXXXXXX, IT_UACC, IT_IACC,  IT_OACC, XXXXXXX,
    IT_AACC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, IT_SLSH, IT_MORE,  IT_DQOT, IT_COLN,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, IT_QST,  IT_LESS,  IT_APOS, IT_SCLN
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ALT_TAB:
      if (record->event.pressed) {
        alt_tab_enabled = true;
        register_code(KC_LGUI);
        tap_code(KC_TAB);
      }
      break;
    }
    return true;
}

void matrix_scan_user(void) {
  if (alt_tab_enabled && (get_highest_layer(layer_state)==_QWERTY)) {
    unregister_code(KC_LGUI);
    alt_tab_enabled=false;
   }
}
