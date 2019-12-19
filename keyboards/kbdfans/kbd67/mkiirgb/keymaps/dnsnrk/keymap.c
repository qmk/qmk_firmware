#include QMK_KEYBOARD_H

#define RC_ENT RCTL_T(KC_ENT)
#define LC_CPS LCTL_T(KC_CAPS)
#define KC_VDN KC__VOLDOWN
#define KC_VUP KC__VOLUP

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_LAYER0] = LAYOUT_65_ansi_blocker( /* Base */
				     KC_ESC,     KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   KC_GRV,
				     KC_TAB,     KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLASH, KC_PGUP,
				     LC_CPS,     KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,  KC_QUOT,           RC_ENT,    KC_PGDN,
				     KC_LSFT,    KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT,           KC_UP,       MO(2),
				     KC_LCTL, KC_LGUI,  KC_LALT,                KC_SPC,                 KC_RALT,           MO(1),    KC_LEFT,           KC_DOWN,    KC_RIGHT),
  [_LAYER1] = LAYOUT_65_ansi_blocker( /* FN, RGB */
				     KC_GRV,     KC_F1,    KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL, KC_POWER,
				     KC_TRNS,  RGB_TOG,    KC_UP, RGB_MOD, RGB_RMOD, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS,   KC_UP, _______,  KC_INS,  KC_HOME,
				     _______,  KC_LEFT,  KC_DOWN,   KC_UP,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_RGHT,          _______,   KC_END,
				     KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_SAD, RGB_SAI, KC_DOWN,          _______, RGB_VAI,  _______,
				     KC_TRNS,  KC_TRNS,  KC_TRNS,                    KC_TRNS,                   KC_TRNS,          KC_TRNS,          RGB_HUD, RGB_VAD,  RGB_HUI),
  [_LAYER2] = LAYOUT_65_ansi_blocker( /* Media, DFU */
				     _______,  KC_BRMD, KC_BRMU, _______, _______, _______, _______, KC_MRWD, KC_MPLY, KC_MFFD, KC__MUTE,  KC_VDN,  KC_VUP, KC_EJCT, _______,
				     _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
				     _______,  _______, _______,   RESET, _______, _______, _______, _______, _______, _______,  _______, _______,          _______, _______,
				     _______,  _______, _______, _______, _______, _______, AG_NORM, AG_SWAP, _______, _______,  _______,          _______, _______, _______,
				     _______,  _______, _______,                   _______,                   _______,           _______,          _______, _______, _______)

};
void matrix_init_user(void) {
}

void matrix_scan_user(void) {
  //user matrix
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	  return true;
}

void keyboard_post_init_user() {
}

void rgb_matrix_indicators_user(void) {
  if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
    rgb_matrix_set_color(30, 0xFF, 0x00, 0x00);
  }
  // Layer2 indicator
  rgb_matrix_set_color(57, 0x00, 0x90, 0x90);
  // Layer1 indicator
  rgb_matrix_set_color(63, 0x90, 0x00, 0x90);
}
