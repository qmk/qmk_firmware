#include QMK_KEYBOARD_H

enum layers {
  _QWERTY,
  _RAISE,
  _LOWER,
};

#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define TGRAISE TG(_RAISE)
#define RALT_QU RALT_T(KC_QUOT)

static bool is_ctl_pressed;
static bool is_tab_pressed;
static bool is_bspc_pressed;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_ESC, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,RALT_QU,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_ENT,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_LCTL,KC_LGUI,KC_LALT,KC_DEL, LOWER,  KC_SPC, KC_SPC, RAISE,  KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
), 

[_RAISE] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
    _______,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   _______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_MINS,KC_EQL, KC_LBRC,KC_RBRC,KC_BSLS,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_GRV, _______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,_______,_______,KC_HOME,KC_PGDN,KC_PGUP,KC_END
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
),

[_LOWER] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
    _______,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,KC_VOLD,KC_MUTE,KC_VOLU,DM_REC1,DM_REC2,DM_RSTP,KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,KC_MPRV,KC_MPLY,KC_MNXT,DM_PLY1,DM_PLY2,KC_CAPS,KC_TILD,KC_WH_D,KC_BTN1,KC_BTN2,KC_WH_U,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,TGRAISE,_______,KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
),

};

layer_state_t layer_state_set_user(layer_state_t state) {
  #ifdef JOTANCK_LEDS
  writePin(JOTANCK_LED2, (get_highest_layer(state) == _RAISE));
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
  writePin(JOTANCK_LED1, led_state.caps_lock);
  #endif
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LCTL:
      is_ctl_pressed = record->event.pressed;
      break;
    case KC_TAB:
      is_tab_pressed = record->event.pressed;
      break;
    case KC_BSPC:
      is_bspc_pressed = record->event.pressed;
      break;
  };
  return true;
}

void matrix_scan_user(void) {
  if (is_ctl_pressed && is_tab_pressed && is_bspc_pressed) {
    reset_keyboard();
  }
}
