#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _RAISE 1

#define KC_CTES LCTL_T(KC_ESC)
#define KC_RAIS MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
                 KC_GESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_MINS, KC_EQL,KC_BSLS,KC_BSPC, KC_INS,
                 KC_TAB,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_LBRC,KC_RBRC,        KC_HASH,KC_PGUP,
                 KC_CTES,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,KC_QUOT,KC_HASH,         KC_ENT,KC_PGDN,
                 KC_LSFT,KC_BSLS,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,        KC_RSFT,  KC_UP, KC_END,
                 KC_RAIS,KC_LGUI,KC_LALT,         KC_SPC, KC_SPC, KC_SPC,                        KC_RALT,KC_RGUI,KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT
    ),
    [_RAISE] = LAYOUT(
                 KC_GRV,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11,KC_F12,KC_BSLS,KC_BSPC, KC_DEL,
                 KC_TAB,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,KC_PSCR,KC_LBRC,KC_RBRC,          QK_BOOT,KC_PGUP,
                 KC_CTES,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,KC_QUOT,  QK_BOOT,       KC_ENT,KC_PGDN,
                 KC_LSFT,KC_NUBS,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,        KC_RSFT,  KC_UP,KC_HOME,
                 KC_LCTL,KC_LGUI,KC_LALT,         KC_SPC, KC_SPC, KC_SPC,                        KC_RALT,KC_RGUI,KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT
                 ),
};

bool shift_pressed(void) {
  return get_mods() & MOD_MASK_SHIFT;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  static bool tilde_pressed = false;

  switch (keycode) {
  case KC_HASH:
    if (shift_pressed()) {
      if (record->event.pressed) {
        tilde_pressed = true;
        register_code(KC_GRV);
        return false;
      }
      else if (tilde_pressed) {
        unregister_code(KC_GRV);
        tilde_pressed = false;
        return false;
      }
    }
    return true;
  default:
    return true; // Process all other keycodes normally
  }
}
