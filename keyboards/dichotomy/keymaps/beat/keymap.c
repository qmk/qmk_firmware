#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MOUSE 8
#define _ADJUST 16

enum dichotomy_keycodes
{
  MS_BTN1 = SAFE_RANGE,
  MS_BTN2,
  MS_BTN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( /* Base layout, nearly qwerty but with modifications because it's not a full keyboard. Obviously. */
  KC_ESCAPE,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_TAB,      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
  KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TT(_MOUSE),
                                 KC_LCTL, KC_LALT, KC_LGUI,    KC_RGUI, KC_RALT, KC_RCTL,
               MS_BTN3, SFT_T(KC_ESCAPE), KC_DEL,  KC_SPC,     KC_SPC,  MO(_RAISE), TT(_LOWER),   MS_BTN3
  ),

  [_RAISE] = LAYOUT( /* Shifted layout, small changes (because angle brackets have been moved to thumb cluster buttons) */
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, _______, KC_VOLD, KC_VOLU, KC_MPLY, KC_MNXT,        KC_MUTE, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC,  _______,
  _______, _______, KC_GRV,  _______, _______, KC_MPRV,        _______, _______, _______, KC_BSLS, KC_QUOT, _______,
                             _______, _______, _______,        _______, _______, _______,
                    _______, _______, KC_LABK, _______,        _______, KC_RABK, _______, _______
  ),

  [_LOWER] = LAYOUT( /* Number layout, basically the main function layer */
  _______, KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, _______, KC_VOLD,  KC_VOLU, KC_MPLY, KC_MNXT,       KC_MUTE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
  _______, _______, KC_TILD,  _______, _______, KC_MPRV,       _______, _______, _______, KC_PIPE, KC_DQT,  _______,
                              _______, _______, _______,       _______, _______, _______,
                     _______, _______, _______, _______,       _______, _______, _______, _______
  ),

  [_ADJUST] = LAYOUT( /* Shifted number/function layout, for per-key control.  Only active when shift is held, and number is toggled or held */
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,          KC_PSLS, KC_P7,   KC_P8,   KC_P9, KC_PMNS, _______,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,         KC_PAST, KC_P4,   KC_P5,   KC_P6, KC_PPLS, _______,
  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,         KC_PCMM, KC_P1,   KC_P2,   KC_P3, KC_PEQL, _______,
                             _______, _______, _______,        _______, KC_P0,   KC_PDOT,
                    _______, _______, _______, _______,        _______, _______, _______, _______
  ),

  [_MOUSE] = LAYOUT( /* Mouse layer, including buttons for clicking. */
  _______, _______, _______, _______, _______, _______,        KC_VOLU, KC_HOME, KC_PGUP, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,        _______, MS_BTN1, MS_BTN2, MS_BTN3, _______, _______,
  _______, _______, _______, _______, _______, _______,        KC_VOLD, KC_END,  KC_PGDN, _______, _______, _______,
                             _______, _______, _______,        _______, KC_UP,   _______,
                    _______, _______, _______, _______,        KC_LEFT, KC_DOWN, KC_RGHT, _______
  )
};

uint32_t layer_state_set_user(uint32_t state) {
  //uprintf("%X layer_state_set_user\n", state);
  red_led(state & (1<<(_LOWER)));
  grn_led(state & (1<<(_RAISE)));
  blu_led(state & (1<<(_MOUSE)));
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#define SetBitMask(variable, mask, on) if (on) variable |= mask; else variable &= ~mask

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  report_mouse_t currentReport;
	switch (keycode) {
		//mouse buttons, for 1-3, to update the mouse report:
		//MOUSE_BTN1-3 are consts defined in report.h
		case MS_BTN1:
			currentReport = pointing_device_get_report();
			SetBitMask(currentReport.buttons, MOUSE_BTN1, record->event.pressed);
			pointing_device_set_report(currentReport);
			return false;
		case MS_BTN2:
			currentReport = pointing_device_get_report();
			SetBitMask(currentReport.buttons, MOUSE_BTN2, record->event.pressed);
			pointing_device_set_report(currentReport);
			return false;
		case MS_BTN3:
			currentReport = pointing_device_get_report();
			SetBitMask(currentReport.buttons, MOUSE_BTN3, record->event.pressed);
			pointing_device_set_report(currentReport);
			return false;
	}
	return true;
}
