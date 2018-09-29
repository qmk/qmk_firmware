#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layers {
  _MAIN
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT_ortho_4x4(
    KC_TAB,  KC_Q,    KC_W,    KC_E,
    KC_ESC,  KC_A,    KC_S,    KC_D,
    KC_LSFT, KC_Z,    KC_X,    KC_C,
    KC_F,    KC_LALT, KC_LCTL, KC_SPC
  ),
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case _MAIN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL << _MAIN);
      }
      break;
  }
  return MACRO_NONE;
};
