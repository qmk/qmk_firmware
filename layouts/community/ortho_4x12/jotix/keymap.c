#include QMK_KEYBOARD_H

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
};

#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define SHRAISE LM(_RAISE, MOD_LSFT)

static bool is_ctl_pressed;
static bool is_esc_pressed;
static bool is_bspc_pressed;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
    KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_ENT,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_UP,  KC_SLSH,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_LCTL,KC_LGUI,KC_LALT,KC_RALT,LOWER,  KC_SPC, KC_SPC, RAISE,  SHRAISE,KC_LEFT,KC_DOWN,KC_RGHT
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
), 

[_LOWER] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,KC_F11, KC_F12, KC_INS, KC_HOME,KC_PGUP,_______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,KC_DEL, KC_END, KC_PGDN,_______,_______,_______,KC_BTN1,KC_MS_U,KC_BTN2,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_MS_L,KC_MS_D,KC_MS_R
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
),

[_RAISE] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
    KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_DEL,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_CAPS,_______,_______,_______,_______,_______,KC_LBRC,KC_RBRC,KC_BSLS,KC_QUOT,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,KC_MINS,KC_EQL, _______,_______,KC_VOLU,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_BSPC,KC_VOLD,KC_MUTE
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
),

};

uint32_t layer_state_set_user(uint32_t state) {
  #ifdef JOTANCK_LEDS
  if (biton32(state) == _RAISE) {
    writePinHigh(JOTANCK_LED2);
  } else {
    writePinLow(JOTANCK_LED2);
  }
  #endif
  return state;
}

bool led_update_user(led_t led_state) {

  // NumLock allways on
  if (!led_state.num_lock) {
    tap_code(KC_NUMLOCK);
  }

  #ifdef JOTANCK_LEDS
  // CapsLock led
  if (led_state.caps_lock) {
    writePinHigh(JOTANCK_LED1);
  } else {
    writePinLow(JOTANCK_LED1);
  }
  #endif
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LCTL:
      is_ctl_pressed = record->event.pressed;
      break;
    case KC_ESC:
      is_esc_pressed = record->event.pressed;
      break;
    case KC_BSPC:
      is_bspc_pressed = record->event.pressed;
      break;
  };
  return true;
}

void matrix_scan_user(void) {
  if (is_ctl_pressed && is_esc_pressed && is_bspc_pressed) {
    reset_keyboard();
  }
}
